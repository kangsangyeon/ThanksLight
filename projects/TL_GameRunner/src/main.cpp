#include "Common_pch.h"
#include "GameEngine/Application.h"
#include "GameClient/TestGameApplication.h"

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

//namespace TL_GameEngine
//{
//    class Application;
//}

int APIENTRY _tWinMain(_In_ HINSTANCE _hInstance,
                       _In_opt_ HINSTANCE _hPrevInstance,
                       _In_ LPTSTR _lpCmdLine,
                       _In_ int _nCmdShow
)
{
    UNREFERENCED_PARAMETER(_hPrevInstance);
    UNREFERENCED_PARAMETER(_lpCmdLine);

    // {
    //     HMODULE _hDLL = LoadLibrary(TEXT("./GameClient.dll"));
    //     assert(_hDLL != nullptr);
    //
    //     using PROC_CREATE_APPLICATION = TL_GameEngine::Application* (*)();
    //     using PROC_RELEASE_APPLICATION = void (*)(TL_GameEngine::Application*);
    //
    //     auto _proc_CreateApplication = (PROC_CREATE_APPLICATION)GetProcAddress(_hDLL, "CreateApplication");
    //     auto _proc_ReleaseApplication = (PROC_RELEASE_APPLICATION)GetProcAddress(_hDLL, "ReleaseApplication");
    //     assert(_proc_CreateApplication != nullptr);
    //     assert(_proc_ReleaseApplication != nullptr);
    //
    //     auto _app = _proc_CreateApplication();
    //     {
    //         if (_app->Start() == true)
    //             return -1;
    //
    //         while (_app->Tick() == false) {}
    //
    //         _app->End();
    //     }
    //     _proc_ReleaseApplication(_app);
    // }

    auto _app = new TestGameApplication();
    {
        if (_app->Start() == true)
            return -1;

        while (_app->Tick() == false) {}

        _app->End();
    }
    delete _app;

    return 0;
}
