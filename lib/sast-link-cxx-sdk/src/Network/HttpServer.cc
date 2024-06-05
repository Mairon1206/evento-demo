#include <Network/HttpServer.h>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/message_generator.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/version.hpp>
#include <boost/system/system_error.hpp>
#include <boost/url/parse_path.hpp>
#include <cassert>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

using tcp_stream = typename beast::tcp_stream::rebind_executor<
    net::use_awaitable_t<>::executor_with_default<net::any_io_executor>>::other;

void HttpServer::route(const std::string &path, Callback &&callback) {
  assert(path.starts_with('/'));
  _route_map[path] = std::move(callback);
}

net::awaitable<void> HttpServer::listen(const std::string &host,
                                        std::uint16_t port) {
  auto endpoint = tcp::endpoint(net::ip::make_address(host), port);
  auto acceptor = net::use_awaitable_t<net::any_io_executor>::as_default_on(
      tcp::acceptor(co_await net::this_coro::executor));
  acceptor.open(endpoint.protocol());

  acceptor.set_option(net::socket_base::reuse_address(true));

  acceptor.bind(endpoint);

  acceptor.listen(net::socket_base::max_listen_connections);

  for (;;)
    net::co_spawn(acceptor.get_executor(),
                  do_session(tcp_stream(co_await acceptor.async_accept())),
                  [](std::exception_ptr e) {
                    if (e)
                      try {
                        std::rethrow_exception(e);
                      } catch (std::exception &e) {
                        std::cerr << "Exception: " << e.what() << std::endl;
                      }
                  });
}

net::awaitable<void> HttpServer::do_session(tcp_stream stream) {
  beast::flat_buffer buffer;

  try {
    using namespace std::chrono_literals;
    stream.expires_after(10s);

    http::request<http::string_body> request;
    co_await http::async_read(stream, buffer, request);

    // Handle request
    auto target = request.target();
    auto end_pos = target.find_first_of('?');
    auto rpath = target.substr(0, end_pos);

    if (auto it = _route_map.find(rpath); it != _route_map.end()) {
      auto res = it->second(request);
      res.keep_alive(request.keep_alive());
      res.prepare_payload();
      co_await http::async_write(stream, res, net::use_awaitable);
    } else {
      http::response<http::string_body> res{http::status::not_found,
                                            request.version()};
      res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set(http::field::content_type, "text/plain");
      res.keep_alive(request.keep_alive());
      res.body() = "The resource was not found.";
      res.prepare_payload();
      co_await http::async_write(stream, res, net::use_awaitable);
    }

    stream.socket().shutdown(tcp::socket::shutdown_send);
    co_await stop();
  } catch (boost::system::system_error &se) {
    if (se.code() != http::error::end_of_stream)
      throw;
  }
}

net::awaitable<void> HttpServer::stop() {
  _route_map.clear();
  auto acceptor = net::use_awaitable_t<net::any_io_executor>::as_default_on(
      tcp::acceptor(co_await net::this_coro::executor));
  acceptor.close();
}
