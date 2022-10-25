#pragma once

#include "Scene.h"
#include "Common/Common_type.h"
#include "Common/SingletonInstance.h"

namespace TL_GameEngine
{
    class Scene;
    class GameObject;
    class ComponentBase;
    class IRenderableComponent;

    class GameWorld
    {
        DECLARE_SINGLETON_CLASS(GameWorld)
        friend class Scene;

    public:
        void ReserveLoadScene(Scene* _scene);
        
        // void ReserveLoadScene(const tstring& _sceneName);

        void Tick();

        void Render();

        /**
         * \brief 오브젝트 삭제를 예약합니다.
         * 게임 오브젝트를 삭제할 때, 반드시 GameObject 객체를 직접 delete하지 않고 이 함수를 대신 사용해야 합니다.
         */
        void ReserveDestroy(GameObject* _gameObject);

        /**
         * \brief 컴포넌트 삭제를 예약합니다.
         * 컴포넌트를 삭제할 때, 반드시 Component 객체를 직접 delete하지 않고 이 함수를 대신 사용해야 합니다.
         */
        void ReserveDestroy(ComponentBase* _component);

        void DestroyImmediate(GameObject* _gameObject, bool _deleteFromReserveQueue = true);

        void DestroyImmediate(ComponentBase* _component, bool _deleteFromReserveQueue = true);

    private:
        void ProceedDestroy();

        void ProceedOnStart();

        void AddGameObject(Scene* _scene, GameObject* _gameObject);

        void AddComponent(Scene* _scene, ComponentBase* _component);

    private:
        std::vector<GameObject*> m_GameObjects;

        std::vector<GameObject*> m_WaitingForDestroyGameObjects;

        std::vector<ComponentBase*> m_WaitingForDestroyComponents;

        std::vector<ComponentBase*> m_WaitingForStartComponents;

        std::vector<ComponentBase*> m_Components;

        std::vector<IRenderableComponent*> m_RenderableComponents;

        Scene* m_ActiveScene;

        Scene* m_LoadSceneReserved;

        Camera* m_MainCamera;

        // /*
        //  * 아래는 디버깅용 변수들입니다.
        //  */
        //
        // std::unordered_map<Scene*, GameObject*> m_GameObjectsInScene;
        //
        // std::unordered_map<Scene*, ComponentBase*> m_ComponentsInScene;

    public:
        static Scene* GetActiveScene() { return Instance.m_ActiveScene; }
    };
}
