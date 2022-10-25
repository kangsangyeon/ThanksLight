#include "GameEngine/GameFramework/GameWorld.h"

#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/Component/ComponentBase.h"
#include "GameEngine/GameFramework/Scene.h"

namespace TL_GameEngine
{
    void GameWorld::ReserveLoadScene(Scene* _scene)
    {
        m_LoadSceneReserved = _scene;
    }

    void GameWorld::Tick()
    {
        if (m_LoadSceneReserved != nullptr)
        {
            if (m_ActiveScene != nullptr)
                m_ActiveScene->OnEndScene();

            m_ActiveScene = m_LoadSceneReserved;
            m_LoadSceneReserved = nullptr;
        }

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

    void GameWorld::ProceedDestroy()
    {
        // 삭제가 예약된 컴포넌트들을 삭제합니다.
        for (const auto _component : m_WaitingForDestroyComponents)
        {
            DestroyImmediate(_component, false);
        }


        // 삭제가 예약된 게임 오브젝트들을 삭제합니다.
        for (const auto _gameObject : m_WaitingForDestroyGameObjects)
        {
            DestroyImmediate(_gameObject, false);
        }


        m_WaitingForDestroyComponents.clear();
        m_WaitingForDestroyGameObjects.clear();
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

    void GameWorld::AddGameObject(Scene* _scene, GameObject* _gameObject)
    {
        if (std::ranges::find(m_GameObjects, _gameObject) != m_GameObjects.end())
            return;

        m_GameObjects.push_back(_gameObject);

        _gameObject->SetScene(_scene);
    }

    void GameWorld::AddComponent(Scene* _scene, ComponentBase* _component)
    {
        assert(std::ranges::find(m_Components, _component) == m_Components.end());
        assert(std::ranges::find(m_WaitingForStartComponents, _component) == m_WaitingForStartComponents.end());

        GameWorld::Instance.m_WaitingForStartComponents.push_back(_component);
        m_Components.push_back(_component);
    }

    void GameWorld::ReserveDestroy(GameObject* _gameObject)
    {
        m_WaitingForDestroyGameObjects.push_back(_gameObject);
    }

    void GameWorld::ReserveDestroy(ComponentBase* _component)
    {
        m_WaitingForDestroyComponents.push_back(_component);
    }

    void GameWorld::DestroyImmediate(GameObject* _gameObject, bool _deleteFromReserveQueue)
    {
        if (_deleteFromReserveQueue == true)
        {
            if (const auto _iter = std::ranges::find(m_WaitingForDestroyGameObjects, _gameObject);
                _iter != m_WaitingForDestroyGameObjects.end())
            {
                m_WaitingForDestroyGameObjects.erase(_iter);
            }
        }


        if (const auto _iter = std::ranges::find(m_GameObjects, _gameObject);
            _iter != m_GameObjects.end())
        {
            m_GameObjects.erase(_iter);
        }

        // 게임 오브젝트의 하위에 있는 모든 자식들을 재귀적으로 삭제합니다.
        for (const auto _child : _gameObject->GetChilds())
            DestroyImmediate(_child);

        // 게임 오브젝트의 모든 컴포넌트를 삭제합니다.
        for (const auto _component : _gameObject->GetAllComponents())
            DestroyImmediate(_component);


        // 부모로부터 떼어냅니다.
        _gameObject->SetParent(nullptr);


        delete _gameObject;
    }

    void GameWorld::DestroyImmediate(ComponentBase* _component, bool _deleteFromReserveQueue)
    {
        if (_deleteFromReserveQueue == true)
        {
            if (const auto _iter = std::ranges::find(m_WaitingForDestroyComponents, _component);
                _iter != m_WaitingForDestroyComponents.end())
            {
                m_WaitingForDestroyComponents.erase(_iter);
            }
        }


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

        delete _component;
    }
}
