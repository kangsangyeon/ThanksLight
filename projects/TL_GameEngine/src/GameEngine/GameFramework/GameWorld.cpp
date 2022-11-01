#include "GameEngine/GameFramework/GameWorld.h"

#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/Component/ComponentBase.h"
#include "GameEngine/GameFramework/Scene.h"

namespace TL_GameEngine
{
    DEFINE_SINGLETON_CLASS(
        GameWorld,
        {},
        {}
    )

    void GameWorld::ReserveLoadScene(Scene* _scene)
    {
        m_LoadSceneReserved = _scene;
    }

    void GameWorld::Tick()
    {
        ProceedLoadScene();

        ProceedDestroy();

        ProceedOnStart();

        for (const auto _component : m_Components)
            _component->PreTick();

        for (const auto _component : m_Components)
            _component->Tick();

        for (const auto _component : m_Components)
            _component->PostTick();
    }

    void GameWorld::Render()
    {
        for (const auto& _renderable : m_RenderableComponents)
            _renderable->Render();
    }

    void GameWorld::ReserveDestroy(GameObject* _gameObject)
    {
        m_WaitingForDestroyGameObjects.push_back(_gameObject);
    }

    void GameWorld::ReserveDestroy(ComponentBase* _component)
    {
        m_WaitingForDestroyComponents.push_back(_component);
    }

    void GameWorld::ProceedDestroy()
    {
        // 삭제가 예약된 컴포넌트들을 삭제합니다.
        for (const auto _component : m_WaitingForDestroyComponents)
        {
            DestroyImmediate(_component);
        }


        // 삭제가 예약된 게임 오브젝트들을 삭제합니다.
        for (const auto _gameObject : m_WaitingForDestroyGameObjects)
        {
            DestroyImmediate(_gameObject);
        }


        m_WaitingForDestroyComponents.clear();
        m_WaitingForDestroyGameObjects.clear();
    }

    void GameWorld::DestroyImmediate(GameObject* _gameObject)
    {
        if (_gameObject->GetParent() != nullptr)
        {
            // 부모를 가지고 있다면, 
            // 부모로부터 떼어냅니다.
            _gameObject->GetParent()->RemoveChild(_gameObject);
            _gameObject->m_Parent = nullptr;
        }
        else
        {
            if (const auto _iter = std::ranges::find(m_RootGameObjects, _gameObject);
                _iter != m_RootGameObjects.end())
            {
                m_RootGameObjects.erase(_iter);
            }

            _gameObject->GetScene()->RemoveRootGameObject(_gameObject);
        }

        // 게임 오브젝트의 하위에 있는 모든 자식들을 재귀적으로 삭제합니다.
        for (const auto _child : _gameObject->GetChilds())
            DestroyImmediate(_child);

        // 게임 오브젝트의 모든 컴포넌트를 삭제합니다.
        for (const auto _component : _gameObject->GetAllComponents())
            DestroyImmediate(_component);

        delete _gameObject;
    }

    void GameWorld::DestroyImmediate(ComponentBase* _component)
    {
        // 월드에 더 이상 해당 컴포넌트가 존재하지 않습니다.

        if (const auto _iter = std::ranges::find(m_WaitingForStartComponents, _component);
            _iter != m_WaitingForStartComponents.end())
        {
            m_WaitingForStartComponents.erase(_iter);
        }

        if (const auto _iter = std::ranges::find(m_Components, _component);
            _iter != m_Components.end())
        {
            m_Components.erase(_iter);
        }

        // 씬에는 더 이상 해당 컴포넌트가 존재하지 않습니다.
        _component->GetGameObject()->GetScene()->RemoveComponent(_component);

        delete _component;
    }

    void GameWorld::ProceedOnStart()
    {
        for (auto _iter = m_WaitingForStartComponents.begin();
             _iter != m_WaitingForStartComponents.end();
             ++_iter)
        {
            (*_iter)->OnStart();
        }

        m_WaitingForStartComponents.clear();
    }

    void GameWorld::ProceedLoadScene()
    {
        assert(m_LoadSceneReserved != m_ActiveScene);

        if (m_LoadSceneReserved != nullptr)
        {
            if (m_ActiveScene != nullptr)
            {
                // 열려있던 기존 씬이 존재한다면,
                // 씬을 전환하기 전에 기존 씬의 모든 오브젝트를 파괴합니다.
                std::ranges::for_each(m_ActiveScene->GetAllRootGameObjects(), [](auto _go) { _go->ReserveDestroy(); });
                ProceedDestroy();

                delete m_ActiveScene;
            }

            m_ActiveScene = m_LoadSceneReserved;
            m_LoadSceneReserved = nullptr;
        }
    }

    void GameWorld::AddRootGameObject(GameObject* _gameObject)
    {
        // 이미 월드상에 루트로 존재하는 오브젝트의 추가에 대한 요청은 잘못된 요청입니다.
        assert(std::ranges::find(m_RootGameObjects, _gameObject) == m_RootGameObjects.end());

        m_RootGameObjects.push_back(_gameObject);
    }

    void GameWorld::RemoveRootGameObject(GameObject* _gameObject)
    {
        const auto _iter = std::ranges::find(m_RootGameObjects, _gameObject);
        assert(_iter != m_RootGameObjects.end());

        m_RootGameObjects.erase(_iter);
    }

    void GameWorld::AddComponent(ComponentBase* _component)
    {
        assert(std::ranges::find(m_Components, _component) == m_Components.end());
        assert(std::ranges::find(m_WaitingForStartComponents, _component) == m_WaitingForStartComponents.end());

        m_WaitingForStartComponents.push_back(_component);
        m_Components.push_back(_component);
        _component->GetGameObject()->GetScene()->AddComponent(_component);
    }

    void GameWorld::RemoveComponent(ComponentBase* _component)
    {
        const auto _iter = std::ranges::find(m_Components, _component);
        assert(_iter != m_Components.end());

        m_Components.erase(_iter);
        _component->GetGameObject()->GetScene()->RemoveComponent(_component);
    }
}
