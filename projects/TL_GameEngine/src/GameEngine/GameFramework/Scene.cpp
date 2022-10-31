#include "GameEngine/GameFramework/Scene.h"

#include <cassert>

#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/GameWorld.h"
#include "GameEngine/GameFramework/Component/ComponentBase.h"

namespace TL_GameEngine
{
    Scene::Scene(const tstring& _name) :
        Object(TEXT("Scene")),
        m_RootGameObjects(0)
    {
        m_Name = _name;
    }

    void Scene::AddRootGameObject(GameObject* _gameObject)
    {
        assert(std::ranges::find(m_RootGameObjects, _gameObject) == m_RootGameObjects.end());

        m_RootGameObjects.push_back(_gameObject);
    }

    void Scene::AddComponent(ComponentBase* _component)
    {
        assert(std::ranges::find(m_Components, _component) == m_Components.end());

        m_Components.insert(_component);
    }

    void Scene::RemoveRootGameObject(GameObject* _gameObject)
    {
        const auto _iter = std::ranges::find(m_RootGameObjects, _gameObject);
        assert(_iter != m_RootGameObjects.end());

        m_RootGameObjects.erase(_iter);
    }

    void Scene::RemoveComponent(ComponentBase* _component)
    {
        const auto _iter = std::ranges::find(m_Components, _component);
        assert(_iter != m_Components.end());

        m_Components.erase(_iter);
    }
}
