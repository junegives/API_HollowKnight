// HollowKnight.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HollowKnight.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND      g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

/*
* wWinMain()
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    srand(unsigned(time(NULL)));
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow)) { return FALSE; }

    CMainGame MainGame;
    MainGame.Initialize(g_hWnd);

    MSG msg{};
    uint64 prevTick = 0;

    // 기본 메시지 루프입니다.
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            uint64 curTick = ::GetTickCount64();
            if (curTick - prevTick >= 10)
            {
                MainGame.Update();
                MainGame.LateUpdate();
                MainGame.Render();
                prevTick = curTick;
            }
        }
    }

    MainGame.Release();
    return (int) msg.wParam;
}

/*
* MyRegisterClass()
* 창 클래스를 등록합니다.
*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"HollowKnight";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return ::RegisterClassExW(&wcex);
}

/*
* InitInstance(HINSTANCE, int)
* 인스턴스 핸들을 저장하고 주 창을 만듭니다.
* 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시합니다.
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   // 인스턴스 핸들을 전역 변수에 저장합니다.
   hInst = hInstance;

   RECT rect{ 0, 0, 1920, 1080 };
   ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   HWND hWindow = CreateWindowW(L"HollowKnight",
       L"HollowKnight",
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT,
       0,
       rect.right - rect.left,
       rect.bottom - rect.top,
       nullptr,
       nullptr,
       hInstance,
       nullptr);

   if (!hWindow) { return FALSE; }

   // 윈도우 핸들을 전역 변수에 저장합니다.
   g_hWnd = hWindow;
   ::ShowWindow(hWindow, nCmdShow);
   ::UpdateWindow(hWindow);

   return TRUE;
}

/*
* WndProc(HWND, UINT, WPARAM, LPARAM)
* 주 창의 메시지를 처리합니다.
* 
* WM_COMMAND: 애플리케이션 메뉴를 처리합니다.
* WM_PAINT  : 주 창을 그립니다.
* WM_DESTROY: 종료 메시지를 게시하고 반환합니다.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_EXIT:
                ::DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = ::BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            ::EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
