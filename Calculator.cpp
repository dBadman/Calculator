// Calculator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Calculator.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR   szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR   szWindowClass[MAX_LOADSTRING];            // The main window class name
WCHAR   FirstArg[MAX_LOADSTRING];                 // First argument of math
float    firstNum;
WCHAR   SecondArg[MAX_LOADSTRING];                // Second Argument of math
float    secondNum;
WCHAR   OutputText[MAX_LOADSTRING];               // The Output Text of the Formula
float    outputNum;
std::wstringstream   result;   // Result of math
WCHAR   operation[MAX_LOADSTRING];                               // Math operation

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND                hwndEditBox1;
HWND                hwndEditBox2;
void                AddControls(HWND);

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
    LoadStringW(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATOR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULATOR);
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
    case WM_CREATE:
    {
        AddControls(hWnd);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            // When a button is clicked we enter this case below
            case BN_CLICKED:
                // If the "1" button was clicked then we go into the first case
                case IDC_BUTTON1:
                    // This case concatenates the digit "1" into the OutputText string that will be displayed in hwndEditBox1
                    wcscat_s(OutputText, L"1");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON2:
                    wcscat_s(OutputText, L"2");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON3:
                    wcscat_s(OutputText, L"3");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON4:
                    wcscat_s(OutputText, L"4");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON5:
                    wcscat_s(OutputText, L"5");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON6:
                    wcscat_s(OutputText, L"6");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON7:
                    wcscat_s(OutputText, L"7");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON8:
                    wcscat_s(OutputText, L"8");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_BUTTON9:
                    wcscat_s(OutputText, L"9");
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                // When the "+" button is presses
                case IDC_PLUS:
                    // We copy all the concatenated numbers into the string FirstArg
                    wcsncpy_s(FirstArg, OutputText, MAX_LOADSTRING);
                    // Save that number as a int as well, 
                    firstNum = wcstol(FirstArg, NULL, 10);
                    // Set a future compare string to "add" for future maths
                    wcsncpy_s(operation, L"add", MAX_LOADSTRING);
                    // Concatenate the "+" symbol for display purposes
                    wcscat_s(FirstArg, L" + ");
                    // Clear the output text to prepare it for a second argument of numbers
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    // Display the First Arg + " + " and the cleared output box
                    // Ready for a second argument 
                    // Currently there is no protection or logic for hitting this twice in a row or creating a 3rd argument
                    // It is assumed that you will enter a second argument then hit ENTER
                    SetWindowTextW(hwndEditBox1, OutputText);
                    SetWindowTextW(hwndEditBox2, FirstArg);
                    break;
                case IDC_MINUS:
                    wcsncpy_s(FirstArg, OutputText, MAX_LOADSTRING);
                    firstNum = wcstol(FirstArg, NULL, 10);
                    wcsncpy_s(operation, L"subtract", MAX_LOADSTRING);
                    wcscat_s(FirstArg, L" - ");
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    SetWindowTextW(hwndEditBox1, OutputText);
                    SetWindowTextW(hwndEditBox2, FirstArg);
                    break;
                case IDC_DIVIDE:
                    wcsncpy_s(FirstArg, OutputText, MAX_LOADSTRING);
                    firstNum = wcstol(FirstArg, NULL, 10);
                    wcsncpy_s(operation, L"divide", MAX_LOADSTRING);
                    wcscat_s(FirstArg, L" / ");
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    SetWindowTextW(hwndEditBox1, OutputText);
                    SetWindowTextW(hwndEditBox2, FirstArg);
                    break;
                case IDC_MULTIPLY:
                    wcsncpy_s(FirstArg, OutputText, MAX_LOADSTRING);
                    firstNum = wcstol(FirstArg, NULL, 10);
                    wcsncpy_s(operation, L"multiply", MAX_LOADSTRING);
                    wcscat_s(FirstArg, L" * ");
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    SetWindowTextW(hwndEditBox1, OutputText);
                    SetWindowTextW(hwndEditBox2, FirstArg);
                    break;
                case IDC_CLEAR:
                    // Clears the output window, but if a FirstArg is set, it doesn't cear it
                    firstNum = wcstol(FirstArg, NULL, 10);
                    wcsncpy_s(OutputText,L"",MAX_LOADSTRING);
                    SetWindowTextW(hwndEditBox1, OutputText);
                    break;
                case IDC_CLEARALL:
                    // Clears output window and FirstArg window
                    // Doesn't actually overwrite and clear FirstArg, just the display text
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    SetWindowTextW(hwndEditBox1, OutputText);
                    SetWindowTextW(hwndEditBox2, OutputText);
                    break;
                case IDC_ENTER:
                    // We copy all the concatenated numbers into the string Second Arg
                    wcsncpy_s(SecondArg,OutputText, MAX_LOADSTRING);
                    // Clears OutputText
                    wcsncpy_s(OutputText, L"", MAX_LOADSTRING);
                    // Save SecondArg as a int as well 
                    secondNum = wcstol(SecondArg, NULL, 10);
                    // Concatenates First Arg (which contains the operator +,-,/,*) and SecondArg
                    wcscat_s(FirstArg, SecondArg);
                    // Shows the concatenated string in the upper "holding" display box
                    SetWindowTextW(hwndEditBox2, FirstArg);
                    // Does maths depending on the operator string set when operator button clicked
                    if (!lstrcmpW(operation, L"add"))
                    {
                        outputNum = firstNum + secondNum;
                    }
                    else if (!lstrcmpW(operation, L"subtract"))
                    {
                        outputNum = firstNum - secondNum;
                    }
                    else if (!lstrcmpW(operation, L"divide"))
                    {
                        outputNum = firstNum / secondNum;
                    }
                    else if (!lstrcmpW(operation, L"multiply"))
                    {
                        outputNum = firstNum * secondNum;
                    }
                    // Converts the resulting maths float into a LPCWSTR
                    // Works for 2+2,84-9,5*70, 9/3 and  7/6
                    result << outputNum;
                    // displays result string
                    SetWindowTextW(hwndEditBox1, result.str().c_str());
                    result.str(L"");
                    result.clear();
                    break;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    // Work in hear to maybe color the text and background / foreground of window, boxes and text
    case WM_CTLCOLORSTATIC:

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

// All the controls are created here, this function is called in the WM_Create case in the WndProc loop
void AddControls(HWND hWnd)
{
    
    // These three "windows" are the text box where the current input is shown and the results will go, the stored arguments area waiting to be operated on, 
    // and an empty box w/ border for design
    hwndEditBox1 = CreateWindowW(L"EDIT", L"Type Formula Here", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER,
        11, 335, 373, 24, hWnd, (HMENU)IDC_EDITBOX1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    hwndEditBox2 = CreateWindowW(L"STATIC", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER,
        11, 310, 373, 25, hWnd, (HMENU)IDC_EDITBOX2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndBox1 = CreateWindowW(L"STATIC", L"", WS_TABSTOP | WS_VISIBLE | WS_BORDER | WS_CHILD,
        10, 310, 375, 50, hWnd, (HMENU)IDC_BOX1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    //It's the "1" button
    HWND hwndButton1 = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"1",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)IDC_BUTTON1,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    //It's the "2" button
    HWND hwndButton2 = CreateWindowW(L"BUTTON", L"2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        110, 10, 100, 100, hWnd, (HMENU)IDC_BUTTON2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton3 = CreateWindowW(L"BUTTON", L"3", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        210, 10, 100, 100, hWnd, (HMENU)IDC_BUTTON3, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton4 = CreateWindowW(L"BUTTON", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 110, 100, 100, hWnd, (HMENU)IDC_BUTTON4, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton5 = CreateWindowW(L"BUTTON", L"5", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        110, 110, 100, 100, hWnd, (HMENU)IDC_BUTTON5, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton6 = CreateWindowW(L"BUTTON", L"6", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        210, 110, 100, 100, hWnd, (HMENU)IDC_BUTTON6, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton7 = CreateWindowW(L"BUTTON", L"7", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 210, 100, 100, hWnd, (HMENU)IDC_BUTTON7, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton8 = CreateWindowW(L"BUTTON", L"8", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        110, 210, 100, 100, hWnd, (HMENU)IDC_BUTTON8, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButton9 = CreateWindowW(L"BUTTON", L"9", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        210, 210, 100, 100, hWnd, (HMENU)IDC_BUTTON9, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    // It's the plus button
    HWND hwndButtonPlus = CreateWindowW(L"BUTTON", L"+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        310, 10, 75, 75, hWnd, (HMENU)IDC_PLUS, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButtonMinus = CreateWindowW(L"BUTTON", L"-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        310, 85, 75, 75, hWnd, (HMENU)IDC_MINUS, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButtonDivide = CreateWindowW(L"BUTTON", L"/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        310, 160, 75, 75, hWnd, (HMENU)IDC_DIVIDE, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButtonMultiply = CreateWindowW(L"BUTTON", L"*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        310, 235, 75, 75, hWnd, (HMENU)IDC_MULTIPLY, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    // It's the ENTER button
    HWND hwndButtonEnter = CreateWindowW(L"BUTTON", L"ENTER", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        335, 360, 50, 50, hWnd, (HMENU)IDC_ENTER, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    // It's the clear and clear all buttons
    HWND hwndButtonClear = CreateWindowW(L"BUTTON", L"C", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        285, 360, 50, 50, hWnd, (HMENU)IDC_CLEAR, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    HWND hwndButtonClearAll = CreateWindowW(L"BUTTON", L"CC", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        235, 360, 50, 50, hWnd, (HMENU)IDC_CLEARALL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
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
