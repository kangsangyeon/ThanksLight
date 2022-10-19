﻿#pragma once

#include "Common_typedef.h"

class COMMON_API DebugHelper
{
    /**
     * @brief 형식화된 문자열을 debug console에 출력합니다.
    */
    template <typename ... Args>
    static void PrintDebugString(const tstring& _format, Args ... _args);

    /**
     * @brief 형식화된 문자열을 debug console에 출력합니다.
    */
    template <typename ... Args>
    static void PrintDebugString(const TCHAR* _format, Args ... _args);
};

#include "DebugHelper.inl"
