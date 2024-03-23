// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include "commdlg.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
COLORREF dColors[10];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

#define IDC_COMBOBOX 1000
#define IDC_TEXT 1001
#define IDC_HOTKEY 1002
#define IDC_CHECKBOX 1003
#define IDC_COLORBUTTON 1004
#define IDC_REPLACEBUTTON 1005

#define WC_COMBOBOXCAL L"ComboBox"
#define WC_TEXTCAL L"Static"
#define WC_HOTKEYCAL L"msctls_hotkey32"
#define WC_CHECKBOXCAL L"Button"
#define WC_BUTTON L"Button"


//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной


   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   HWND hWndComboBox = CreateWindowEx(0, WC_COMBOBOXCAL, L"ПУСТО", WS_CHILD | WS_VISIBLE | WS_BORDER| CBS_DROPDOWN,
       50, 50, 100, 100, hWnd, (HMENU)IDC_COMBOBOX, GetModuleHandle(NULL), NULL);
   if (!hWndComboBox)
   {
       return FALSE;
   }
   SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Элемент 1");
   SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Элемент 2");

   HWND hWndText = CreateWindowEx(0, WC_TEXTCAL, L"Static Text", WS_CHILD | WS_VISIBLE | WS_BORDER , 50, 100, 150, 30, hWnd, (HMENU)IDC_TEXT, GetModuleHandle(NULL), NULL);
   if (!hWndText)
   {
       return FALSE;
   }

   HWND hWndHotKey = CreateWindowEx(0, WC_HOTKEYCAL, L"HotKey", WS_CHILD | WS_VISIBLE | WS_BORDER , 50, 150, 100, 30, hWnd, (HMENU)IDC_HOTKEY, GetModuleHandle(NULL), NULL);
   if (!hWndHotKey)
   {
       return FALSE;
   }

   HWND hWndCheckBox = CreateWindowEx(0, WC_CHECKBOXCAL, L"Interesting CheckBox", WS_CHILD | WS_VISIBLE | WS_BORDER|BS_AUTOCHECKBOX , 50, 200, 170, 20, hWnd, (HMENU)IDC_CHECKBOX, GetModuleHandle(NULL), NULL);
   if (!hWndCheckBox)
   {
       return FALSE;
   }
   HWND hWndColor = CreateWindowEx(0, WC_BUTTON, L"Select Color", WS_CHILD | WS_VISIBLE | WS_BORDER , 50, 250, 100, 20, hWnd, (HMENU)IDC_COLORBUTTON, GetModuleHandle(NULL), NULL);
   if (!hWndColor)
   {
       return FALSE;
   }
   HWND hWndReplace = CreateWindowEx(0, WC_BUTTON, L"Replace", WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 300, 100, 20, hWnd, (HMENU)IDC_REPLACEBUTTON, GetModuleHandle(NULL), NULL);
   if (!hWndReplace)
   {
       return FALSE;
   }
   if (!hWnd)
   {
      return FALSE;
   } 

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
 CHOOSECOLOR chcol = { sizeof(CHOOSECOLOR) };

 FINDREPLACE fr;
 TCHAR szFindWhat[80] = TEXT("");
 TCHAR szReplaceWith[80] = TEXT("");


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case IDC_COLORBUTTON:
                
                chcol.Flags = CC_RGBINIT | CC_FULLOPEN;
                chcol.hInstance = NULL;
                chcol.hwndOwner = hWnd;
                chcol.lCustData = 0L;
                chcol.lpCustColors = dColors;
                chcol.lpTemplateName = NULL;
                chcol.lpfnHook = NULL;
                chcol.lStructSize = sizeof(chcol);
                chcol.rgbResult = (255, 255, 255);
                if (ChooseColor(&chcol) != FALSE) {

                }
                break;

            case IDC_REPLACEBUTTON:

                ZeroMemory(&fr, sizeof(fr));
                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;
                fr.wFindWhatLen = sizeof(szFindWhat);
                fr.wReplaceWithLen = sizeof(szReplaceWith);
                fr.Flags = FR_DOWN;
                fr.lpstrFindWhat = szFindWhat;
                fr.lpstrReplaceWith = szReplaceWith;
                if (ReplaceText(&fr) != FALSE) {

                }
                
                break;

           


            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CHAR:
        MessageBox(hWnd, L"Get WM_CHAR", L"WM_CHAR Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_KEYUP:
        MessageBox(hWnd, L"Get WM_KEYUP", L"WM_KEYUP Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_MOUSEWHEEL:
        MessageBox(hWnd, L"Get WM_MOUSEWHEEL", L"WM_MOUSEWHEEL Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_MOVING:
        MessageBox(hWnd, L"Get WM_MOVING", L"WM_MOVING Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_RBUTTONDBLCLK:
        MessageBox(hWnd, L"Get WM_RBUTTONDBLCLK", L"WM_RBUTTONDBLCLK Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_RBUTTONDOWN:
        MessageBox(hWnd, L"Get WM_RBUTTONDOWN", L"WM_RBUTTONDOWN Message", MB_OK | MB_ICONASTERISK);
        break;

    case WM_RBUTTONUP:
        MessageBox(hWnd, L"Get WM_RBUTTONUP", L"WM_RBUTTONUP Message", MB_OK | MB_ICONASTERISK);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
