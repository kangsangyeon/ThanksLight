#include "GameEngine/GameFramework/Scene.h"

#include <cassert>

#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/GameWorld.h"
#include "GameEngine/GameFramework/Component/ComponentBase.h"

namespace TL_GameEngine
{
    Scene::Scene(const tstring& _name) :
        Object(TEXT("Scene")),
        m_GameObjects(0) { }

    Scene::~Scene()
    {
        for (const auto _gameObject : m_GameObjects)
            delete _gameObject;

        for (const auto _component : m_Components)
            delete _component;
    }

    void Scene::OnAddGameObject(GameObject* _gameObject)
    {
        GameWorld::Instance.AddGameObject(this, _gameObject);
    }

    void Scene::OnAddComponent(ComponentBase* _component)
    {
        GameWorld::Instance.AddComponent(this, _component);
    }

    void Scene::OnEndScene()
    {
        while (m_GameObjects.empty() == false)
        {
            // 씬 내의 모든 게임 오브젝트를 파괴합니다.

            const auto _iter = m_GameObjects.begin();
            GameWorld::Instance.DestroyImmediate(*_iter);
        }
    }
}
