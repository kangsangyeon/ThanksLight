#pragma once

#include "Common_typedef.h"

class DebugHelper
{
    template <typename ... Args>
    static void PrintDebugString(const tstring& _format, Args ... _args);

    template <typename ... Args>
    static void PrintDebugString(const TCHAR* _format, Args ... _args);
};

#include "DebugHelper.inl"
