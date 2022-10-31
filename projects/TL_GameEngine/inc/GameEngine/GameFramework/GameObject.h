#pragma once

#include "GameEngine/internal/dll.h"

#include <Windows.h>
#include <cassert>

#include "Common/Common_type.h"
#include "GameEngine/Object.h"
#include "GameEngine/GameFramework/Component/Transform.h"

namespace TL_GameEngine
{
    class ComponentBase;
    class ColliderBase;
    class Scene;

    class GAME_ENGINE_API GameObject final :
        public Object
    {
    public:
        GameObject(Scene* _scene, const tstring& _typeName = TEXT("GameObject"));

        ~GameObject() = default;

        void ReserveDestroy();

        void SetScene(Scene* _scene);

        void SetParent(GameObject* _parent);

        void AddChild(GameObject* _newChild);

        void RemoveChild(GameObject* _child);

        /// <summary>
        /// 게임 컴포넌트가 가지고 있는 컴포넌트 중에서 입력받은 타입과 일치하거나 이 타입의 서브타입의 컴포넌트가 있는 경우
        ///	해당 컴포넌트를 반환합니다.
        ///	만약 해당하는 컴포넌트가 없다면 nullptr을 반환합니다.
        /// </summary>
        template <class TComponent>
        TComponent* GetComponent();

        template <class TComponent>
        TComponent* AddComponent();

        template <class TComponent>
        void RemoveComponent();

        template <class TComponent>
        void RemoveComponent(TComponent* _component);

        std::vector<ComponentBase*> GetAllComponents();

    private:
        bool m_bEnable;

        Scene* m_Scene;

        GameObject* m_Parent;

        std::vector<GameObject*> m_Childs;

        std::vector<ComponentBase*> m_Components;

    public:
        // tstring GetName() const;

        inline bool GetEnable() const { return m_bEnable; }

        inline class Scene* GetScene() const { return m_Scene; }

        inline GameObject* GetParent() const { return m_Parent; }

        inline std::vector<GameObject*> GetChilds() const { return m_Childs; }

        inline GameObject* GetChild(size_t _index) const { return m_Childs[_index]; }

        GameObject* GetChild(const tstring& _name) const;

        inline void SetEnable(bool _value) { m_bEnable = _value; }

        /*
         * 게임 오브젝트가 기본으로 가지고 있는 멤버 컴포넌트를 정의합니다.
         * 컴포넌트 타입의 멤버를 선언하고 GetComponent와 AddComponent 템플릿 특수화 멤버 메소드를 정의합니다.
         */
#define __DEFINE_GAME_OBJECT_GET_EMBEDDED_COMPONENT__(TComponent, ComponentMemberName) \
        private: \
            TComponent ComponentMemberName; \
        public: \
        template <> \
        TComponent* GetComponent<class TComponent>(){ return &this->ComponentMemberName; } \
        template <> \
        TComponent* AddComponent<class TComponent>() { assert(true); return nullptr; }

        __DEFINE_GAME_OBJECT_GET_EMBEDDED_COMPONENT__(Transform, m_Transform)
    };
}

#include "GameEngine/GameFramework/GameObject.inl"
