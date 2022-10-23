﻿#include "GameEngine/GameFramework/Component/ComponentBase.h"

#include "GameEngine/GameFramework/GameObject.h"

namespace TL_GameEngine
{
    ComponentBase::ComponentBase(GameObject* _gameObject, tstring _typeName) :
        m_GameObject(_gameObject),
        m_bEnable(true),
        m_Ticked(false) { }

    void ComponentBase::PreTick()
    {
        m_Ticked = false;
    }

    void ComponentBase::PostTick() { }

    void ComponentBase::TryTick()
    {
        if (m_bEnable == false)
            return;

        if (m_Ticked == true)
            return;

        Tick();
    }

    void ComponentBase::Tick()
    {
        m_Ticked = true;
    }

    void ComponentBase::OnStart() { }

    void ComponentBase::OnChangeEnable(bool _newEnable) { }
}
