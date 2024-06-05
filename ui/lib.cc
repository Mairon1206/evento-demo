#include <MainWindow.h>
#include <ui/ui.h>

EVENTO_LIBRARY_API void init_app() {
    auto main_window = MainWindow::create();
    main_window->run();
}