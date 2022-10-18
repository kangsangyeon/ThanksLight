#include "Common.h"
#include "../../TL_GameEngine/inc/Application.h"

#if defined(DEBUG) | defined(_DEBUG)

    #if defined(DEBUG_ENABLE_VLD)

        #include <vld.h>

        #if defined(_WIN64)
            #pragma comment(lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win64\\vld.lib")
        #elif
            #pragma comment(lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
        #endif

    #endif

#endif

namespace TL_GameEngine
{
    class Application;
}

int APIENTRY _tWinMain(_In_ HINSTANCE _hInstance,
                       _In_opt_ HINSTANCE _hPrevInstance,
                       _In_ LPTSTR _lpCmdLine,
                       _In_ int _nCmdShow)
{
    UNREFERENCED_PARAMETER(_hPrevInstance);
    UNREFERENCED_PARAMETER(_lpCmdLine);

    TL_GameEngine::Application* _app = new TL_GameEngine::Application();

    if (_app->Initialize() == false)
        return -1;

    _app->Run();
    delete _app;

    return 0;
}
