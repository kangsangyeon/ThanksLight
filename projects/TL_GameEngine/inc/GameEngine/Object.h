#pragma once

#include "Common/Common_type.h"
#include "Common/StringHelper.h"
#include "GameEngine/Internal/UUIDGenerator.h"

namespace TL_GameEngine
{
    class Object
    {
    public:
        Object(const tstring& _typeName);

        Object(const tstring& _typeName, const tstring& _uuid);

        Object(const tstring& _typeName, const tstring& _uuid, const tstring& _name);

        tstring m_Name;

        tstring m_UUID;

        tstring m_TypeName;

        [[nodiscard]] tstring GetName() const { return m_Name; }

        [[nodiscard]] tstring GetUUID() const { return m_UUID; }

        [[nodiscard]] tstring GetTypeName() const { return m_TypeName; }

        void SetName(const tstring& _name) { m_Name = _name; }

        void SetUUID(const tstring& _uuid) { m_UUID = _uuid; }
    };

    inline Object::Object(const tstring& _typeName) :
        Object(_typeName, UUIDGenerator::Generate()) { }

    inline Object::Object(const tstring& _typeName, const tstring& _uuid) :
        Object(_typeName, _uuid, StringHelper::Format(TEXT("%s {%s}"), _typeName, _uuid)) { }

    inline Object::Object(const tstring& _typeName, const tstring& _uuid, const tstring& _name) :
        m_TypeName(_typeName),
        m_UUID(_uuid),
        m_Name(_name) { }
}
