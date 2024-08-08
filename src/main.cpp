#include "application.h"
#include "applog.h"

int main() {
    bool success = false;
    try {
        success = Application::Instance()->Setup();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 1;
    }

    if (success) {
        Application::Instance()->Run();
    }
    return 0;
}
