#pragma once

#include "GameEngine/GameFramework/Component/ComponentBase.h"

namespace TL_GameEngine
{
    class Transform : public ComponentBase
    {
    public:
        Transform(class GameObject* _gameObject, tstring _typeName = TEXT("Transform"));
    //
    //     void UpdateWorldMatrix(const Matrix& _parentTM);
    //
    // private:
    //     /**
    //      * \brief 로컬 변환 행렬입니다.
    //      */
    //     Matrix m_LocalTM;
    //
    //     /**
    //      * \brief 월드 변환 행렬입니다.
    //      */
    //     Matrix m_WorldTM;
    //
    //     /**
    //      * \brief 가장 마지막으로 월드 변환 행렬이 계산된 이후
    //      * 값이 한 번이라도 수정되어서 변경될 필요가 있는지에 대한 판별값입니다.
    //      * 이 변수는 행렬 계산을 최소한으로 줄이기 위해 사용됩니다.
    //      */
    //     bool m_bWorldTMShouldUpdate;
    //
    // public:
    //     void SetLocalPosition(const Vector3& _newPosition);
    //
    //     void SetLocalRotation(const Quaternion& _newRotation);
    //
    //     void SetLocalScale(const Vector3& _newScale);
    //
    //     void SetWorldPosition(const Vector3& _newPosition);
    //
    //     void SetWorldRotation(const Quaternion& _newRotation);
    //
    //     void SetWorldScale(const Vector3& _newScale);
    //
    //     inline Vector3 GetLocalPosition()
    //     {
    //         Vector3 _scale;
    //         Quaternion _rotation;
    //         Vector3 _position;
    //
    //         Matrix _localTM = GetLocalTM();
    //         _localTM.Decompose(_scale, _rotation, _position);
    //
    //         return _position;
    //     }
    //
    //     inline Quaternion GetLocalRotation()
    //     {
    //         Vector3 _scale;
    //         Quaternion _rotation;
    //         Vector3 _position;
    //
    //         Matrix _localTM = GetLocalTM();
    //         _localTM.Decompose(_scale, _rotation, _position);
    //
    //         return _rotation;
    //     }
    //
    //     inline Vector3 GetLocalScale()
    //     {
    //         Vector3 _scale;
    //         Quaternion _rotation;
    //         Vector3 _position;
    //
    //         Matrix _localTM = GetLocalTM();
    //         _localTM.Decompose(_scale, _rotation, _position);
    //
    //         return _scale;
    //     }
    //
    //     Vector3 GetWorldPosition();
    //
    //     Quaternion GetWorldRotation();
    //
    //     Vector3 GetWorldScale();
    //
    //     void SetLocalTM(const Matrix& _localTM);
    //
    //     void SetWorldTM(const Matrix& _worldTM);
    //
    //     Matrix GetLocalTM() const;
    //
    //     Matrix GetWorldTM();
    //
    //     Vector3 GetRightDirection();
    //
    //     Vector3 GetUpDirection();
    //
    //     Vector3 GetForwardDirection();
    //
    // private:
    //     void TryUpdateWorldTM();
    //
    //     void MarkWorldTMDirt();
    //
    // private:
    //     static constexpr float RAD_TO_DEG = 57.295779513f;
    //
    //     static constexpr float DEG_TO_RAD = 0.01745329252f;
    };
}
