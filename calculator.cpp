#include <tchar.h>
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

HWND textfield, buttonPlus, buttonMinus, buttonMultiply, buttonDivide, TextBoxOne, TextBoxTwo;
char textOne[20], textTwo[20], answerStr[20];
double numOne, numTwo, answer;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE:
            textfield = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, 20, 20, 195, 20, hwnd, NULL, NULL, NULL);
            buttonPlus = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 70, 115, 25, 25, hwnd, (HMENU)1, NULL, NULL);
            buttonMinus = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 100, 115, 25, 25, hwnd, (HMENU)2, NULL, NULL);
            buttonMultiply = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 115, 25, 25, hwnd, (HMENU)3, NULL, NULL);
            buttonDivide = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 160, 115, 25, 25, hwnd, (HMENU)4, NULL, NULL);
            TextBoxOne = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 50, 150, 20, hwnd, NULL, NULL, NULL);
            TextBoxTwo = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 75, 150, 20, hwnd, NULL, NULL, NULL);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case 1: case 2: case 3: case 4:
                    GetWindowText(TextBoxOne, textOne, 20);
                    GetWindowText(TextBoxTwo, textTwo, 20);
                    numOne = atof(textOne);
                    numTwo = atof(textTwo);
                    if (LOWORD(wParam) == 1) answer = numOne + numTwo;
                    if (LOWORD(wParam) == 2) answer = numOne - numTwo;
                    if (LOWORD(wParam) == 3) answer = numOne * numTwo;
                    if (LOWORD(wParam) == 4) {
                        if (numTwo == 0) {
                            MessageBox(hwnd, "Cannot divide by zero.", "Error", MB_ICONEXCLAMATION | MB_OK);
                            break;
                        }
                        answer = numOne / numTwo;
                    }
                    sprintf(answerStr, "%f", answer);
                    MessageBox(hwnd, answerStr, "Result", MB_OK);
                    break;
            }
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);

            const int numColors = 7;
            COLORREF rainbowColors[numColors] = {
                RGB(255, 0, 0), RGB(255, 165, 0), RGB(255, 255, 0),
                RGB(0, 255, 0), RGB(0, 0, 255), RGB(75, 0, 130), RGB(148, 0, 211)
            };

            int height = (rect.bottom - rect.top) / numColors;
            for (int i = 0; i < numColors; i++) {
                HBRUSH hBrush = CreateSolidBrush(rainbowColors[i]);
                RECT band = { rect.left, rect.top + i * height, rect.right, rect.top + (i + 1) * height };
                FillRect(hdc, &band, hBrush);
                DeleteObject(hBrush);
            }
            EndPaint(hwnd, &ps);
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(0, "WindowClass", "Rainbow Calculator", WS_VISIBLE | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
