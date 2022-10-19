#pragma once

#include "Common/internal/dll.h"

#include <basetsd.h>

/*
 * Char and String
 */
#include <tchar.h>
#include <xstring>

using tchar = TCHAR;

#if defined(UNICODE)
using tstring = std::wstring;
#else
using tstring = std::string;
#endif
