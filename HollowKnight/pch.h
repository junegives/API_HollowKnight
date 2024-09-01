#pragma once

// ������ ���̺귯��
#include <Windows.h>

// C++ ǥ�� ���̺귯��
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

// ����� ���� ��� ����
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