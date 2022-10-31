#pragma once

namespace TL_GameEngine
{
    class Application;
}

/* If we are we on Windows, we want a single define for it.*/
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
#define _WIN32
#endif /* _WIN32 */

#if defined(GAME_CLIENT_BUILD_DLL)
    /* We are building Hashing as a Win32 DLL */
    #define GAME_CLIENT_API __declspec(dllexport)
#else
    /* We are calling Hashing as a Win32 DLL */
    #define GAME_CLIENT_API __declspec(dllimport)
#endif

extern "C"
{
GAME_CLIENT_API TL_GameEngine::Application* CreateApplication();

GAME_CLIENT_API void ReleaseApplication(TL_GameEngine::Application* _app);
}
