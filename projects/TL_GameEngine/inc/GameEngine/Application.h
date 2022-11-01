#pragma once

#include "GameEngine/internal/dll.h"

#include "Common.h"
#include "GameFramework/GameWorld.h"

namespace TL_GameEngine
{
    class GAME_ENGINE_API Application
    {
    public:
        Application();

        virtual ~Application();

        bool Start();

        void End();

        bool Tick();

        virtual void OnApplicationStart();

        virtual void OnApplicationTick();

        virtual void OnApplicationEnd();

    private:
        GameWorld* m_GameWorld;

        bool m_bExitFlag;
        bool m_bAlreadyExit;
    };
}
