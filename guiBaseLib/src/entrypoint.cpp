#include "guiBase/entrypoint.h"

namespace guiBase {
    int appMain(int argc, char** argv) {
        while (gRunning) {
            guiBase::App* app = guiBase::CreateApp(argc, argv);
            app->run();
            delete app;
        }

        return 0;
    }
}// namespace guiBase

#if WIN32

#include <Windows.h>

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow) {
    UNUSED(hInst);
    UNUSED(hInstPrev);
    UNUSED(cmdline);
    UNUSED(cmdshow);
    return guiBase::appMain(__argc, __argv);
}

#endif

int main(int argc, char** argv) {
    return guiBase::appMain(argc, argv);
}
