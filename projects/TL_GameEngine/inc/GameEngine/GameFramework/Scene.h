#pragma once

#include "Common.h"
#include "GameEngine/Object.h"

namespace TL_GameEngine
{
    class GameObject;
    class ComponentBase;
    class Camera;

    class Scene final :
        Object
    {
        friend class GameWorld;
        friend class GameObject;
        friend class ComponentBase;

    public:
        Scene(const tstring& _name);

        ~Scene();


    private:

        /**
         * @brief (이 메소드는 GameWorld을 통해서만 호출됩니다.) <br>
         * 씬이 종료될 때 호출됩니다.
        */
        void OnEndScene();

        /**
         * @brief (이 메소드는 GameObject의 생성자를 통해서만 호출됩니다.) <br>
         * 이 씬에 GameObject를 추가할 때 호출됩니다.
         * 게임 월드에 GameObject를 등록합니다.
        */
        void OnAddGameObject(GameObject* _gameObject);

        /**
         * @brief (이 메소드는 Component의 생성자를 통해서만 호출됩니다.) <br>
         * 이 씬에 Component를 추가할 때 호출됩니다.
         * 게임 월드에 Component를 등록합니다.
        */
        void OnAddComponent(ComponentBase* _component);

    private:
        std::vector<GameObject*> m_GameObjects;
        
        std::unordered_set<ComponentBase*> m_Components;

    public:
        inline std::vector<GameObject*> GetAllGameObjects() const { return m_GameObjects; }

        inline std::unordered_set<ComponentBase*> GetAllComponents() const { return m_Components; }
    };
}
