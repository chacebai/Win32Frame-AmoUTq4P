// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

// #include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <windowsx.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Enabling Visual Styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// micro define
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDM_COPY                201
#define IDM_PASTE               202
#define IDM_CUT                 203

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif



