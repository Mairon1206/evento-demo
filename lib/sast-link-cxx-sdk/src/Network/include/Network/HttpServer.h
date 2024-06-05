#pragma once

#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core/string_type.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/fields.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/message_generator.hpp>
#include <boost/beast/http/string_body.hpp>
#include <cstdint>
#include <functional>
#include <map>
#include <string>

class HttpServer {
  using tcp = boost::asio::ip::tcp;
  using tcp_stream = typename boost::beast::tcp_stream::rebind_executor<
      boost::asio::use_awaitable_t<>::executor_with_default<
          boost::asio::any_io_executor>>::other;
  using Callback = std::function<
      boost::beast::http::response<boost::beast::http::string_body>(
          boost::beast::http::request<boost::beast::http::string_body>)>;

public:
  void route(const std::string &path, Callback &&callback);
  boost::asio::awaitable<void> listen(const std::string &host,
                                      std::uint16_t port);
  boost::asio::awaitable<void> stop();

private:
  boost::asio::awaitable<void> do_session(tcp_stream stream);

  std::map<std::string, Callback> _route_map;
};