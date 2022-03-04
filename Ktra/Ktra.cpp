// Ktra.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Ktra.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    QLSV(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KTRA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KTRA));

    MSG msg;

    // Main message loop:
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KTRA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KTRA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_QLSV:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, QLSV);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
INT_PTR  QLSV(HWND hWnd, UINT uint, WPARAM wParam, LPARAM lParam)
{
    static TCHAR hoten[30], phantu[30];
    static int len, index, count ;
    switch (uint)
    {
    case WM_CLOSE:
        EndDialog(hWnd, TRUE);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case btnThoat:
            if (MessageBox(NULL, TEXT("Bạn có muốn thoát không?"), TEXT("TB"), MB_YESNO | MB_ICONQUESTION) == IDYES)
                EndDialog(hWnd, TRUE);
            break;
        case btnThem:
            len = GetWindowText(GetDlgItem(hWnd, txt_HT), hoten, 30);
            if (len == 0) {
                MessageBox(NULL, TEXT("Bạn chưa nhập họ và tên."), TEXT("Thông báo"), MB_OK);
                SetFocus(GetDlgItem(hWnd, txt_HT));
            }
            else {
                SendMessage(GetDlgItem(hWnd, lstDS), LB_INSERTSTRING, -1, (LPARAM)hoten);
                SetWindowText(GetDlgItem(hWnd, txt_HT), TEXT(""));
                SetFocus(GetDlgItem(hWnd, txt_HT));
            }
            break;
        case lstDS:
            index = SendMessage(GetDlgItem(hWnd, lstDS), LB_GETCURSEL, 0, 0);
            SendMessage(GetDlgItem(hWnd, lstDS), LB_GETTEXT, index, (LPARAM)phantu);
            SetWindowText(GetDlgItem(hWnd, txt_HT), phantu);
            break;
        case btnSua:
            len = GetWindowText(GetDlgItem(hWnd, txt_HT), hoten, 30);
            if (len == 0) {
                MessageBox(NULL, TEXT("Họ và tên trống."), TEXT("Thông báo"), MB_OK);
                SetFocus(GetDlgItem(hWnd, txt_HT));
            }
            else {
                index = SendMessage(GetDlgItem(hWnd, lstDS), LB_GETCURSEL, 0, 0);
                SendMessage(GetDlgItem(hWnd, lstDS), LB_DELETESTRING, index, 0);
                SendMessage(GetDlgItem(hWnd, lstDS), LB_INSERTSTRING, index, (LPARAM)hoten);
                SetWindowText(GetDlgItem(hWnd, txt_HT), TEXT(""));
                SetFocus(GetDlgItem(hWnd, txt_HT));
            }
            break;
        case btnXoa:
            index = SendMessage(GetDlgItem(hWnd, lstDS), LB_GETCURSEL, 0, 0);
            if (index < 0)
                MessageBox(NULL, TEXT("Bạn chưa chọn phần tử nào"), TEXT("Thông báo"), MB_OK);
            else {
                if(MessageBox(NULL, TEXT("Bạn có chắc chắn muốn xoá?"), TEXT("Thông báo"), MB_YESNO)== IDYES)
                    SendMessage(GetDlgItem(hWnd, lstDS), LB_DELETESTRING, index, 0);
                SetWindowText(GetDlgItem(hWnd, txt_HT), TEXT(""));
            }
            break;
        case btnTK:
            len = GetWindowText(GetDlgItem(hWnd, txt_HT), hoten, 30);
            if (len == 0)
                MessageBox(NULL, TEXT("Ban chua nhap ten tim kiem"), TEXT("Thong bao"), MB_OK);
            else
            {
                int i;
                count = SendMessage(GetDlgItem(hWnd, lstDS), LB_GETCOUNT, 0, 0);
                for ( i = 0; i < SendMessage(GetDlgItem(hWnd, lstDS), LB_GETCOUNT, 0, 0); i++)
                {
                    SendMessage(GetDlgItem(hWnd, lstDS), LB_GETTEXT, i, (LPARAM)phantu);
                    if (_tccmp(phantu, hoten) == 0) {
                        SendMessage(GetDlgItem(hWnd, lstDS), LB_SETCURSEL, i, 0);                     
                        break;
                    }
                   
                }
                if (i == count)
                {
                    SendMessage(GetDlgItem(hWnd, lstDS), LB_SETCURSEL, -1, 0);
                    MessageBox(NULL, TEXT("Khong co phan tu"), TEXT("Thong bao"), MB_OK);
                }
                

            }
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }

    return (INT_PTR)FALSE;
}
