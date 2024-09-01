#pragma once

// 윈도우 라이브러리
#include <Windows.h>

// C++ 표준 라이브러리
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <memory>
#include <functional>
#include <cmath>
#include <bitset>
#include <tchar.h>

#include <vfw.h>
#pragma comment(lib, "vfw32.lib")

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#pragma comment(lib,"msimg32.lib")

#include <io.h>
#include <iostream>

// 사용자 정의 헤더 파일
#include "Defines.h"
#include "Enums.h"
#include "Types.h"
#include "Geometry.h"

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace std;