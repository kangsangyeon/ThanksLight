#pragma once

#include "Common/StringHelper.h"
#include "uuid.h"

namespace TL_GameEngine
{
    class UUIDGenerator
    {
    public:
        inline static tstring Generate()
        {
            std::random_device rd;
            auto seed_data = std::array<int, std::mt19937::state_size>{};
            std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
            std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
            std::mt19937 generator(seq);
            uuids::uuid_random_generator gen{ generator };

            const uuids::uuid id = gen();
            return StringHelper::ToTString(
                reinterpret_cast<char*>(const_cast<std::byte*>(id.as_bytes().data()))
            );
        }
    };
}
