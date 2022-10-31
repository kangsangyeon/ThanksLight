#pragma once

#include "GameObject.h"

#include "GameEngine/GameFramework/GameWorld.h"

namespace TL_GameEngine
{
    template <class TComponent>
    TComponent* GameObject::GetComponent()
    {
        for (auto _component : m_Components)
        {
            TComponent* _castedComponent = dynamic_cast<TComponent*>(_component);
        
            if (_castedComponent != nullptr)
                return _castedComponent;
        }

        return nullptr;
    }

    template <class TComponent>
    TComponent* GameObject::AddComponent()
    {
        static_assert(std::is_base_of<ComponentBase, TComponent>::value, "TComponent must inherit from ComponentBase");
        
        TComponent* _newComponent = new TComponent(this);
        
        // 생성한 컴포넌트를 scene에 등록합니다.
        GameWorld::Instance.AddComponent(_newComponent);
        
        m_Components.push_back(_newComponent);
        return _newComponent;
    }

    template <class TComponent>
    void GameObject::RemoveComponent()
    {
        for (auto _iter = m_Components.begin();
             _iter != m_Components.end(); ++_iter)
        {
            if (const auto _castedComponent = dynamic_cast<TComponent*>(*_iter);
                _castedComponent != nullptr)
            {
                m_Components.erase(_castedComponent);

                // 컴포넌트를 world에서 삭제합니다.
                GameWorld::Instance.ReserveDestroy(_castedComponent);

                return;
            }
        }
    }

    template <class TComponent>
    void GameObject::RemoveComponent(TComponent* _component)
    {
        const auto _iter = std::ranges::find(m_Components, _component);
        if (_iter == m_Components.end())
            return;
        
        m_Components.erase(_iter);
        
        // 컴포넌트를 world에서 삭제합니다.
        GameWorld::Instance.ReserveDestroy(_component);
    }
}
