#include "GameEngine/GameFramework/GameObject.h"

#include "GameEngine/GameFramework/GameWorld.h"
#include "GameEngine/GameFramework/Component/ComponentBase.h"
#include "GameEngine/GameFramework/Component/Transform.h"
#include "GameEngine/GameFramework/Scene.h"

namespace TL_GameEngine
{
    GameObject::GameObject(Scene* _scene, const tstring& _typeName) :
        Object(_typeName),
        m_Scene(_scene),
        m_bEnable(true),
        m_Parent(nullptr),
        m_Childs(0),
        m_Components(0),
        m_Transform(Transform(this))
    {
        GameWorld::Instance.AddGameObjectAsRoot(this);
    }  

    void GameObject::ReserveDestroy()
    {
        GameWorld::Instance.ReserveDestroy(this);
    }

    void GameObject::SetScene(Scene* _scene)
    {
        if (m_Scene == _scene)
            return;

        if (GetParent() == nullptr)
        {
            // 원래 포함되어 있던 씬에서 루트 오브젝트였던 경우,
            // 원래 씬의 루트 오브젝트 목록에서 제외합니다.

            m_Scene->RemoveRootGameObject(this);
        }
        else
        {
            // 루트 오브젝트가 아니였던 경우,
            // 부모와 떼어냅니다.

            SetParent(nullptr);
        }

        m_Scene = _scene;

        for (auto& _child : GetChilds())
        {
            // 자식을 가진 게임 오브젝트를 이동시키는 경우,
            // 자식 오브젝트들 모두 전환 대상이 되는 씬에 포함시킵니다.

            _child->SetScene(_scene);
        }
    }

    void GameObject::SetParent(GameObject* _parent)
    {
        if (m_Parent == _parent)
            return;

        // 만약 기존의 부모가 있다면,
        // 기존의 부모로부터 분리합니다.
        if (m_Parent != nullptr)
            m_Parent->RemoveChild(this);

        m_Parent = _parent;

        if(_parent == nullptr)
        {
            // 새로 지정한 부모가 nullptr인 경우,
            // 루트 게임 오브젝트임을 월드에 알립니다.
            GameWorld::Instance.AddGameObjectAsRoot(this);
        }
        else
        {
            // 새로 지정한 부모가 nullptr가 아닌 경우
            // 부모에게도 이 게임 오브젝트를 자식으로 추가합니다.
            _parent->AddChild(this);
        }
    }

    void GameObject::AddChild(GameObject* _newChild)
    {
        // 이미 자식으로 포함되어 있다면, 추가하지 않습니다.
        if (std::ranges::find(m_Childs, _newChild) != m_Childs.end())
            return;

        if(_newChild->GetParent() != nullptr)
        {
            // 이미 다른 오브젝트의 자식으로 포함되어 있던 오브젝트라면,
            // 그 부모로부터 떼어냅니다.
            _newChild->SetParent(nullptr);
        }

        m_Childs.push_back(_newChild);

        // 새로운 자식이 원래 다른 씬에 있던 경우, 소속된 씬 정보도 갱신합니다.
        _newChild->SetScene(m_Scene);

        _newChild->SetParent(this);
    }

    void GameObject::RemoveChild(GameObject* _child)
    {
        if (const auto _iter = std::ranges::find(m_Childs, _child);
            _iter != m_Childs.end())
        {
            m_Childs.erase(_iter);

            _child->SetParent(nullptr);
        }
    }

    std::vector<ComponentBase*> GameObject::GetAllComponents()
    {
        return m_Components;
    }

    GameObject* GameObject::GetChild(const tstring& _name) const
    {
        for (const auto& _child : m_Childs)
        {
            if (_child->GetName() == _name)
                return _child;
        }

        return nullptr;
    }
}
