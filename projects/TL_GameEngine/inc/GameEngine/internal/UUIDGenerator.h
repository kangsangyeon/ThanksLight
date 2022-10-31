#pragma once

#include "GameEngine/internal/dll.h"

#include "Common/Common_type.h"

namespace TL_GameEngine
{
    class GAME_ENGINE_API UUIDGenerator
    {
    public:
        static tstring Generate();
    };
}
