#include "GameClient/TestGameApplication.h"

TL_GameEngine::Application* CreateApplication()
{
    return new TestGameApplication();
}

void ReleaseApplication(TL_GameEngine::Application* _app)
{
    delete _app;
}
