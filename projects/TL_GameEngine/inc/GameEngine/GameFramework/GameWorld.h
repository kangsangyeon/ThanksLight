#pragma once

#include "GameEngine/internal/dll.h"

#include "Scene.h"
#include "Common/Common_type.h"
#include "Common/SingletonInstance.h"

namespace TL_GameEngine
{
    class Scene;
    class GameObject;
    class ComponentBase;
    class IRenderableComponent;

    class GAME_ENGINE_API GameWorld final
    {
        DECLARE_SINGLETON_CLASS(GameWorld)
        friend class Scene;
        friend class GameObject;
        friend class ComponentBase;

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

    private:
        /**
         * @brief 파괴가 예약된 오브젝트들의 파괴를 수행합니다.
         */
        void ProceedDestroy();

        void DestroyImmediate(GameObject* _gameObject);

        void DestroyImmediate(ComponentBase* _component);

        /**
         * @breif 지난 프레임에 추가된 컴포넌트들의 Start를 수행합니다.
         */
        void ProceedOnStart();

        void ProceedLoadScene();

    private:
        /* Callbacks */

        /**
         * @brief (이 메소드는 Scene과 GameObject에서만 호출됩니다.)
         * 이 GameObject가 루트 오브젝트임을 표시합니다.
         * @param _scene 게임 오브젝트가 새로이 포함될 대상 씬입니다.
         * @param _gameObject 대상 게임 오브젝트입니다.
        */
        void AddGameObjectAsRoot(GameObject* _gameObject);

        /**
         * @brief (이 메소드는 Scene과 GameObject에서만 호출됩니다.)
         * 이 Component가 작동되기 위해 월드에 등록합니다.
         * @param _scene 컴포넌트가 새로이 포함될 대상 씬입니다.
         * @param _gameObject 대상 컴포넌트입니다.
        */
        void AddComponent(ComponentBase* _component);

    private:
        std::vector<GameObject*> m_RootGameObjects;

        std::vector<GameObject*> m_WaitingForDestroyGameObjects;

        std::vector<ComponentBase*> m_WaitingForDestroyComponents;

        std::vector<ComponentBase*> m_WaitingForStartComponents;

        std::vector<ComponentBase*> m_Components;

        std::vector<IRenderableComponent*> m_RenderableComponents;

        Scene* m_ActiveScene;

        Scene* m_LoadSceneReserved;

        Camera* m_MainCamera;

    public:
        static Scene* GetActiveScene() { return Instance.m_ActiveScene; }

        const auto& GetRootGameObjects() { return m_RootGameObjects; }

        const auto& GetComponents() { return m_Components; }
    };
}
