#pragma once

#include "GameEngine/internal/dll.h"

#include "Common.h"

namespace TL_GameEngine
{
    class GAME_ENGINE_API Application
    {
    public:
        bool Initialize();

        void Run();
    };
}
