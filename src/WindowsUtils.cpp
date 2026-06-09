#ifdef _WIN32
#include <windows.h>
#include <string>

extern "C" void* GetWindowHandle(void);

std::string g_newUriReceived = "";
bool g_hasNewUri = false;
WNDPROC g_originalWndProc = nullptr;

LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_COPYDATA) {
        COPYDATASTRUCT* cds = (COPYDATASTRUCT*)lParam;
        if (cds->dwData == 1) {
            g_newUriReceived = std::string((char*)cds->lpData);
            g_hasNewUri = true;
        }
        return 1;
    }
    return CallWindowProc(g_originalWndProc, hwnd, msg, wParam, lParam);
}

void Windows_CheckSingleInstance(int argc, char* argv[]) {
    HWND existingHwnd = FindWindowA(NULL, "FOC World TCG - Arene de Combat");
    if (existingHwnd != NULL) {
        if (argc > 1) {
            std::string uri(argv[1]);
            COPYDATASTRUCT cds;
            cds.dwData = 1;
            cds.cbData = uri.length() + 1;
            cds.lpData = (PVOID)uri.c_str();
            SendMessage(existingHwnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
        }
        ShowWindow(existingHwnd, SW_RESTORE);
        SetForegroundWindow(existingHwnd);
        exit(0);
    }
}

void Windows_SetupCustomWndProc() {
    HWND hwnd = (HWND)GetWindowHandle();
    g_originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
}

bool Windows_HasNewUri() {
    return g_hasNewUri;
}

std::string Windows_GetNewUri() {
    return g_newUriReceived;
}

void Windows_ClearNewUri() {
    g_hasNewUri = false;
    g_newUriReceived = "";
}
#endif
