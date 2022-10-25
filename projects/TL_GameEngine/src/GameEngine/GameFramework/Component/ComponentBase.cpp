#include "GameEngine/GameFramework/Component/ComponentBase.h"

#include "GameEngine/GameFramework/GameObject.h"
#include "GameEngine/GameFramework/Scene.h"

namespace TL_GameEngine
{
    ComponentBase::ComponentBase(GameObject* _gameObject, const tstring& _typeName) :
        Object(_typeName),
        m_GameObject(_gameObject),
        m_bEnable(true),
        m_Ticked(false)
    {
        _gameObject->GetScene()->OnAddComponent(this);
    }

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
