#include "GameEngine/Application.h"

namespace TL_GameEngine
{
    Application::Application() {}

    Application::~Application()
    {
        if (m_bAlreadyExit == false)
            End();
    }

    bool Application::Start()
    {
        m_GameWorld = &GameWorld::Instance;
        m_bExitFlag = false;

        OnApplicationStart();

        return false;
    }

    void Application::End()
    {
        m_bExitFlag = true;
        m_bAlreadyExit = true;

        OnApplicationEnd();
    }

    bool Application::Tick()
    {
        GameWorld::Instance.Tick();

        OnApplicationTick();

        return m_bExitFlag;
    }

    void Application::OnApplicationStart() {}

    void Application::OnApplicationTick() {}

    void Application::OnApplicationEnd() {}
}
