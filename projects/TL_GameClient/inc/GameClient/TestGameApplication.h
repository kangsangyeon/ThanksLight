#pragma once

#include "GameEngine/Application.h"

namespace TL_GameEngine
{
    class Scene;
    class GameObject;
}

class TestGameApplication :
    public TL_GameEngine::Application
{
public:
    void OnApplicationStart() override;

    void OnApplicationTick() override;

    void OnApplicationEnd() override;

private:
    TL_GameEngine::Scene* _scene;
    TL_GameEngine::GameObject* _gameObject1;
};
