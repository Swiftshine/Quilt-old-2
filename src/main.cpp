#include "application.h"

int main(int argc, char* argv[]) {
    if (!Application::Instance()->Setup()) {
        AppLog::Error("Failed to setup application.");
        return 1;
    } 
    Application::Instance()->Run();
    AppLog::Print("Quilt has successfully terminated.");
    return 0;
}
