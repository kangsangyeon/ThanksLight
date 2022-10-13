#pragma once

#include "Common_typedef.h"

#include <vector>

class StringHelper
{
public:
    template <typename ... Args>
    static tstring Format(const tstring& _format, Args ... _args);

    template <typename ... Args>
    static tstring Format(const TCHAR* _format, Args ... _args);

    static std::vector<tstring> Split(const tstring& _str, const tstring& _token);

    static std::wstring StringToWString(const char* _string);

    static std::wstring StringToWString(const std::string& _string);

    static std::string WStringToString(const wchar_t* _string);

    static std::string WStringToString(const std::wstring& _string);

    static std::wstring ToWString(const std::string& _string)
    {
        return StringToWString(_string);
    }

    static std::wstring ToWString(const std::wstring& _string)
    {
        return _string;
    }

    static std::wstring ToWString(const char* _string)
    {
        return StringToWString(_string);
    }

    static std::wstring ToWString(const wchar_t* _string)
    {
        return std::wstring(_string);
    }

    static std::string ToString(const std::wstring& _string)
    {
        return WStringToString(_string);
    }

    static std::string ToString(const std::string& _string)
    {
        return _string;
    }

    static std::string ToString(const wchar_t* _string)
    {
        return WStringToString(_string);
    }

    static std::string ToString(const char* _string)
    {
        return std::string{_string};
    }

    static tstring ToTString(const std::string& _string)
    {
#if defined (_UNICODE)
        return StringToWString(_string);
#else
		return _string;
#endif
    }

    static tstring ToTString(const std::wstring& _string)
    {
#if defined (_UNICODE)
        return _string;
#else
		return WStringToString(_string);
#endif
    }

    static tstring ToTString(const char* _string)
    {
#if defined( _UNICODE )
        return StringToWString(_string);
#else
		return std::string{ _string };
#endif
    }

    static tstring ToTString(const wchar_t* _string)
    {
#if defined( _UNICODE )
        return std::wstring{_string};
#else
		return WStringToString(_string);
#endif
    }
};

#include "StringHelper.inl"
