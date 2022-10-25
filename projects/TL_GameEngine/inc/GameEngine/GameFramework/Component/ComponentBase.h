#pragma once

#include "Common.h"
#include "GameEngine/Object.h"

namespace TL_GameEngine
{
    class GameObject;

    class IRenderableComponent abstract
    {
    public:
        virtual void Render() const abstract;
    };

    class ComponentBase abstract :
        Object
    {
    public:
        ComponentBase(GameObject* _gameObject, const tstring& _typeName);

        virtual ~ComponentBase() = default;

        virtual void PreTick();

        virtual void PostTick();

        virtual void TryTick();

        virtual void Tick();

        virtual void OnStart();

        virtual void OnChangeEnable(bool _newEnable);

    protected:
        GameObject* m_GameObject;

        /// <summary>
        /// 컴포넌트의 활성화 여부입니다.
        ///	비활성화된 컴포넌트는 Tick이 호출되지 않습니다.
        /// </summary>
        bool m_bEnable;

        /// <summary>
        /// 이번 프레임에 Tick이 실행되었는지에 대한 여부입니다.
        ///	매 프레임의 처리를 하기 전에 OnPreTick()이 호출되어 이 플래그를 false로 초기화해줍니다.
        /// </summary>
        bool m_Ticked;

    public:
        inline GameObject* GetGameObject() const { return m_GameObject; }
        
        inline void SetEnable(bool _value)
        {
            if (_value == m_bEnable)
                return;

            m_bEnable = _value;
            OnChangeEnable(_value);
        }
    };
}
