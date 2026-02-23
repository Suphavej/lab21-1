#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_EDIT1 1
#define ID_EDIT2 2
#define ID_BTN_ADD 3
#define ID_BTN_SUB 4
#define ID_BTN_MUL 5
#define ID_BTN_DIV 6

HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        
        case WM_CREATE: {
            CreateWindowA("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE | SS_CENTER,
                30, 20, 170, 20, hwnd, NULL, NULL, NULL);

            hEdit1 = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                30, 45, 170, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                30, 80, 170, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

            CreateWindowA("BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                40, 115, 30, 25, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindowA("BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                75, 115, 30, 25, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindowA("BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                110, 115, 30, 25, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindowA("BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                145, 115, 30, 25, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            if (wmId >= ID_BTN_ADD && wmId <= ID_BTN_DIV) {
                char text1[100] = {0};
                char text2[100] = {0};
                
                GetWindowTextA(hEdit1, text1, 100);
                GetWindowTextA(hEdit2, text2, 100);

                double num1 = atof(text1);
                double num2 = atof(text2);
                double result = 0;

                switch (wmId) {
                    case ID_BTN_ADD: result = num1 + num2; break;
                    case ID_BTN_SUB: result = num1 - num2; break;
                    case ID_BTN_MUL: result = num1 * num2; break;
                    case ID_BTN_DIV: 
                        if (num2 == 0) {
                            MessageBoxA(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2; 
                        break;
                }

                char t[100];
                sprintf(t, "%f", result);
                MessageBoxA(hwnd, t, "Result", MB_OK);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProcA(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXA wc; 
    HWND hwnd; 
    MSG msg; 

    memset(&wc,0,sizeof(wc));
    wc.cbSize    = sizeof(WNDCLASSEXA);
    wc.lpfnWndProc   = WndProc; 
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
    
    wc.hbrBackground = CreateSolidBrush(RGB(220, 10, 150)); 
    wc.lpszClassName = "WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); 

    if(!RegisterClassExA(&wc)) {
        MessageBoxA(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowExA(0,"WindowClass","My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, 
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL) {
        MessageBoxA(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }
    return msg.wParam;
}