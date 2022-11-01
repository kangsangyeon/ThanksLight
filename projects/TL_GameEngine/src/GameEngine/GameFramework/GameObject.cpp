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
        GameWorld::Instance.AddRootGameObject(this);
        _scene->AddRootGameObject(this);
    }

    void GameObject::ReserveDestroy()
    {
        GameWorld::Instance.ReserveDestroy(this);
    }

    void GameObject::SetScene(Scene* _scene)
    {
        if (m_Scene == _scene)
            return;

        if (GetParent() != nullptr)
        {
            // 루트 오브젝트가 아니였던 경우,
            // 부모와 떼어냅니다.
            m_Parent->RemoveChild(this);
            m_Parent = nullptr;

            SetSceneRecursive(_scene);

            // 이제 이동 대상 씬에서 루트 오브젝트가 되므로
            // 루트 오브젝트 목록에 추가합니다.
            GameWorld::Instance.AddRootGameObject(this);
            _scene->AddRootGameObject(this);
        }
        else
        {
            // 원래 포함되어 있던 씬에서 루트 오브젝트였던 경우,
            // 원래 씬의 루트 오브젝트 목록에서 제외합니다.
            m_Scene->RemoveRootGameObject(this);

            SetSceneRecursive(_scene);

            // 월드의 루트 오브젝트 목록에는 이미 추가되어 있기 때문에
            // 아무 처리도 하지 않습니다.
        }
    }

    void GameObject::SetParent(GameObject* _parent)
    {
        // 기존의 부모와 같다면, 아무 처리도 하지 않습니다.
        if (m_Parent == _parent)
            return;

        if (m_Parent != nullptr)
        {
            // 만약 기존의 부모가 있다면,
            // 기존의 부모로부터 분리합니다.
            m_Parent->RemoveChild(this);
        }

        if (_parent == nullptr)
        {
            // 새로 지정한 부모가 nullptr인 경우,
            // 루트 게임 오브젝트임을 월드와 씬에 알립니다.
            GameWorld::Instance.AddRootGameObject(this);
            m_Scene->AddRootGameObject(this);
        }
        else
        {
            if (m_Parent == nullptr)
            {
                // 새로 지정한 부모가 nullptr이 아니며, 기존에 루트 오브젝트였던 경우,
                // 루트 오브젝트 목록에서 제외합니다.
                GameWorld::Instance.RemoveRootGameObject(this);
                m_Scene->RemoveRootGameObject(this);
            }

            // 새로 지정한 부모가 nullptr가 아닌 경우
            // 부모에게도 이 게임 오브젝트를 자식으로 추가합니다.
            _parent->AddChild(this);
        }

        m_Parent = _parent;
    }

    std::vector<ComponentBase*> GameObject::GetAllComponents()
    {
        return m_Components;
    }

    void GameObject::AddChild(GameObject* _newChild)
    {
        const auto _iter = std::ranges::find(m_Childs, _newChild);
        assert(_iter == m_Childs.end());
        m_Childs.push_back(_newChild);
    }

    void GameObject::RemoveChild(GameObject* _child)
    {
        const auto _iter = std::ranges::find(m_Childs, _child);
        assert(_iter != m_Childs.end());
        m_Childs.erase(_iter);
    }

    void GameObject::SetSceneRecursive(Scene* _scene)
    {
        m_Scene = _scene;

        for (auto& _child : GetChilds())
        {
            // 자식을 가진 게임 오브젝트를 이동시키는 경우,
            // 자식 오브젝트들 모두 전환 대상이 되는 씬에 포함시킵니다.

            _child->SetSceneRecursive(_scene);
        }
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
