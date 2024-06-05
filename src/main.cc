#include <thread>
#include <ui/ui.h>
#include <Network/network.h>

int main() {
    std::thread t{init_asio_loop};
    init_app();
    t.join();
}