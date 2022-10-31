#include "GameClient/TestGameApplication.h"

#include "GameClient/SayHelloComponent.h"
#include "GameEngine/GameFramework/GameWorld.h"
#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/Scene.h"

using namespace TL_GameEngine;

void TestGameApplication::OnApplicationStart()
{
    Application::OnApplicationStart();

    _scene = new Scene(TEXT("MainScene"));
    _gameObject1 = new GameObject(_scene);
    _gameObject1->SetName(TEXT("GameObject 1"));
    const auto _helloComponent = _gameObject1->AddComponent<SayHelloComponent>();
    GameWorld::GetInstance()->ReserveLoadScene(_scene);

    assert(_scene->GetName() == TEXT("MainScene"));
    assert(std::ranges::find(_scene->GetAllGameObjects(), _gameObject1) != _scene->GetAllGameObjects().end());
    assert(_gameObject1->GetName() == TEXT("GameObject 1"));
    assert(_gameObject1->GetComponent<SayHelloComponent>() == _helloComponent);
    assert(GameWorld::GetInstance()->GetRootGameObjects().size() == 1);
    assert(GameWorld::GetInstance()->GetComponents().size() == 1);
}

void TestGameApplication::OnApplicationTick()
{
    Application::OnApplicationTick();

    if (_gameObject1 != nullptr)
    {
        _gameObject1->ReserveDestroy();
        _gameObject1 = nullptr;
    }
    else
    {
        assert(std::ranges::find(_scene->GetAllGameObjects(), _gameObject1) == _scene->GetAllGameObjects().end());
        assert(GameWorld::GetInstance()->GetRootGameObjects().size() == 0);
        assert(GameWorld::GetInstance()->GetComponents().size() == 0);
    }
}

void TestGameApplication::OnApplicationEnd()
{
    Application::OnApplicationEnd();
}
