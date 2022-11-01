#include "GameEngine/GameFramework/Component/Transform.h"

#include "GameEngine/GameFramework/GameObject.h"

using namespace TL_GameEngine;

Transform::Transform(GameObject* _gameObject, const tstring& _typeName) :
    ComponentBase(_gameObject, _typeName)
    // m_LocalTM(Matrix::Identity),
    // m_WorldTM(Matrix::Identity),
    // m_bWorldTMShouldUpdate(false)
{
}

// void Transform::UpdateWorldMatrix(const Matrix& _parentTM)
// {
//     m_WorldTM = GetLocalTM() * _parentTM;
//
//     m_bWorldTMShouldUpdate = false;
// }
//
// void Transform::SetLocalPosition(const Vector3& _newPosition)
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetLocalTM().Decompose(_scale, _rotation, _position);
//
//     SetLocalTM(
//         Matrix::CreateScale(_scale)
//         * Matrix::CreateFromQuaternion(_rotation)
//         * Matrix::CreateTranslation(_newPosition)
//     );
// }
//
// void Transform::SetLocalRotation(const Quaternion& _newRotation)
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetLocalTM().Decompose(_scale, _rotation, _position);
//
//     SetLocalTM(
//         Matrix::CreateScale(_scale)
//         * Matrix::CreateFromQuaternion(_newRotation)
//         * Matrix::CreateTranslation(_position)
//     );
// }
//
// void Transform::SetLocalScale(const Vector3& _newScale)
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetLocalTM().Decompose(_scale, _rotation, _position);
//
//     SetLocalTM(
//         Matrix::CreateScale(_newScale)
//         * Matrix::CreateFromQuaternion(_rotation)
//         * Matrix::CreateTranslation(_position)
//     );
// }
//
// void Transform::SetWorldPosition(const Vector3& _newPosition)
// {
//     const auto _parent = GetGameObject()->GetParent();
//     if (_parent == nullptr)
//     {
//         SetLocalPosition(_newPosition);
//     }
//     else
//     {
//         // TODO
//
//         const auto _parentWorldTMInvert = GetGameObject()->GetParent()->GetComponent<Transform>()->GetWorldTM().Invert();
//         auto _newLocalTM = GetWorldTM() * _parentWorldTMInvert;
//
//         Vector3 _scale;
//         Quaternion _rotation;
//         Vector3 _position;
//         _newLocalTM.Decompose(_scale, _rotation, _position);
//
//         _newLocalTM = Matrix::CreateScale(_scale) * Matrix::CreateFromQuaternion(_rotation) * Matrix::CreateTranslation(_newPosition);
//         SetLocalTM(_newLocalTM);
//     }
// }
//
// void Transform::SetWorldRotation(const Quaternion& _newRotation)
// {
//     const auto _parent = GetGameObject()->GetParent();
//     if (_parent == nullptr)
//     {
//         SetLocalRotation(_newRotation);
//     }
//     else
//     {
//         // TODO
//
//         const auto _parentWorldTMInvert = GetGameObject()->GetParent()->GetComponent<Transform>()->GetWorldTM().Invert();
//         auto _newLocalTM = GetWorldTM() * _parentWorldTMInvert;
//
//         Vector3 _scale;
//         Quaternion _rotation;
//         Vector3 _position;
//         _newLocalTM.Decompose(_scale, _rotation, _position);
//
//         _newLocalTM = Matrix::CreateScale(_scale) * Matrix::CreateFromQuaternion(_newRotation) * Matrix::CreateTranslation(_position);
//         SetLocalTM(_newLocalTM);
//     }
// }
//
// void Transform::SetWorldScale(const Vector3& _newScale)
// {
//     const auto _parent = GetGameObject()->GetParent();
//     if (_parent == nullptr)
//     {
//         SetLocalScale(_newScale);
//     }
//     else
//     {
//         // TODO
//
//         const auto _parentWorldTMInvert = GetGameObject()->GetParent()->GetComponent<Transform>()->GetWorldTM().Invert();
//         auto _newLocalTM = GetWorldTM() * _parentWorldTMInvert;
//
//         Vector3 _scale;
//         Quaternion _rotation;
//         Vector3 _position;
//         _newLocalTM.Decompose(_scale, _rotation, _position);
//
//         _newLocalTM = Matrix::CreateScale(_newScale) * Matrix::CreateFromQuaternion(_rotation) * Matrix::CreateTranslation(_position);
//         SetLocalTM(_newLocalTM);
//     }
// }
//
// Vector3 Transform::GetWorldPosition()
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetWorldTM().Decompose(_scale, _rotation, _position);
//
//     return _position;
// }
//
// Quaternion Transform::GetWorldRotation()
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetWorldTM().Decompose(_scale, _rotation, _position);
//
//     return _rotation;
// }
//
// Vector3 Transform::GetWorldScale()
// {
//     Vector3 _scale;
//     Quaternion _rotation;
//     Vector3 _position;
//     GetWorldTM().Decompose(_scale, _rotation, _position);
//
//     return _scale;
// }
//
// void Transform::SetLocalTM(const Matrix& _localTM)
// {
//     m_LocalTM = _localTM;
//     MarkWorldTMDirt();
// }
//
// void Transform::SetWorldTM(const Matrix& _worldTM)
// {
//     m_WorldTM = _worldTM;
//     MarkWorldTMDirt();
// }
//
// Matrix Transform::GetLocalTM() const
// {
//     return m_LocalTM;
// }
//
// Matrix Transform::GetWorldTM()
// {
//     TryUpdateWorldTM();
//
//     return m_WorldTM;
// }
//
// Vector3 Transform::GetRightDirection()
// {
//     return GetWorldRotation().ToEuler().Right;
// }
//
// Vector3 Transform::GetUpDirection()
// {
//     return GetWorldRotation().ToEuler().Up;
// }
//
// Vector3 Transform::GetForwardDirection()
// {
//     return GetWorldRotation().ToEuler().Forward;
// }
//
// void Transform::TryUpdateWorldTM()
// {
//     if (m_bWorldTMShouldUpdate == true)
//     {
//         // 부모의 WorldMatrix를 가져와 새로고칩니다.
//         if (m_GameObject->GetParent() == nullptr)
//             UpdateWorldMatrix(Matrix::Identity);
//         else
//             UpdateWorldMatrix(m_GameObject->GetParent()->GetComponent<Transform>()->GetWorldTM());
//     }
// }
//
// void Transform::MarkWorldTMDirt()
// {
//     this->m_bWorldTMShouldUpdate = true;
//
//     // 이 게임 오브젝트의 하위 자식 오브젝트들의 TM도 모두 바뀌었기 때문에
//     // MarkWorldTMDirt를 전파합니다.
//     const auto& _childs = m_GameObject->GetChilds();
//     for (auto _child : _childs)
//         _child->GetComponent<Transform>()->MarkWorldTMDirt();
// }
