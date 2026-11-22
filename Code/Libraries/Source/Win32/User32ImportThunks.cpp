// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// user32.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as D3DX9ImportThunks.cpp does for d3dx9. VS2003
// __identifier names the actual decorated __imp__ symbol; no alias, address
// pin, inline assembly, emitted bytes or replacement datum is used.
// Signatures: the VS2003 Platform SDK WinUser.h, included with _USER32_
// defined (the header's own switch) so WINUSERAPI is empty and these
// definitions are not dllimport (no C4273 /EXPORT directives).
// Each retail six-byte thunk's IAT slot names the export (row notes).
#define _USER32_
#include <windows.h>
extern "C" {
// _GetWindowRect@8
typedef BOOL (WINAPI *PFN_GetWindowRect)(HWND, LPRECT);
extern PFN_GetWindowRect __identifier("_imp__GetWindowRect@8");
BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect) {
 return __identifier("_imp__GetWindowRect@8")(hWnd, lpRect);
}

// _PostQuitMessage@4
typedef VOID (WINAPI *PFN_PostQuitMessage)(int);
extern PFN_PostQuitMessage __identifier("_imp__PostQuitMessage@4");
VOID WINAPI PostQuitMessage(int nExitCode) {
 __identifier("_imp__PostQuitMessage@4")(nExitCode);
}

// _GetClientRect@8
typedef BOOL (WINAPI *PFN_GetClientRect)(HWND, LPRECT);
extern PFN_GetClientRect __identifier("_imp__GetClientRect@8");
BOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect) {
 return __identifier("_imp__GetClientRect@8")(hWnd, lpRect);
}

// _EndPaint@8
typedef BOOL (WINAPI *PFN_EndPaint)(HWND, CONST PAINTSTRUCT *);
extern PFN_EndPaint __identifier("_imp__EndPaint@8");
BOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT * lpPaint) {
 return __identifier("_imp__EndPaint@8")(hWnd, lpPaint);
}

// _BeginPaint@8
typedef HDC (WINAPI *PFN_BeginPaint)(HWND, LPPAINTSTRUCT);
extern PFN_BeginPaint __identifier("_imp__BeginPaint@8");
HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint) {
 return __identifier("_imp__BeginPaint@8")(hWnd, lpPaint);
}

// _ClipCursor@4
typedef BOOL (WINAPI *PFN_ClipCursor)(CONST RECT *);
extern PFN_ClipCursor __identifier("_imp__ClipCursor@4");
BOOL WINAPI ClipCursor(CONST RECT * lpRect) {
 return __identifier("_imp__ClipCursor@4")(lpRect);
}

// _DefWindowProcA@16
typedef LRESULT (WINAPI *PFN_DefWindowProcA)(HWND, UINT, WPARAM, LPARAM);
extern PFN_DefWindowProcA __identifier("_imp__DefWindowProcA@16");
LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
 return __identifier("_imp__DefWindowProcA@16")(hWnd, Msg, wParam, lParam);
}

// _DefWindowProcW@16
typedef LRESULT (WINAPI *PFN_DefWindowProcW)(HWND, UINT, WPARAM, LPARAM);
extern PFN_DefWindowProcW __identifier("_imp__DefWindowProcW@16");
LRESULT WINAPI DefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
 return __identifier("_imp__DefWindowProcW@16")(hWnd, Msg, wParam, lParam);
}

// _IsWindowUnicode@4
typedef BOOL (WINAPI *PFN_IsWindowUnicode)(HWND);
extern PFN_IsWindowUnicode __identifier("_imp__IsWindowUnicode@4");
BOOL WINAPI IsWindowUnicode(HWND hWnd) {
 return __identifier("_imp__IsWindowUnicode@4")(hWnd);
}

// _UpdateWindow@4
typedef BOOL (WINAPI *PFN_UpdateWindow)(HWND);
extern PFN_UpdateWindow __identifier("_imp__UpdateWindow@4");
BOOL WINAPI UpdateWindow(HWND hWnd) {
 return __identifier("_imp__UpdateWindow@4")(hWnd);
}

// _ShowWindow@8
typedef BOOL (WINAPI *PFN_ShowWindow)(HWND, int);
extern PFN_ShowWindow __identifier("_imp__ShowWindow@8");
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {
 return __identifier("_imp__ShowWindow@8")(hWnd, nCmdShow);
}

// _SetForegroundWindow@4
typedef BOOL (WINAPI *PFN_SetForegroundWindow)(HWND);
extern PFN_SetForegroundWindow __identifier("_imp__SetForegroundWindow@4");
BOOL WINAPI SetForegroundWindow(HWND hWnd) {
 return __identifier("_imp__SetForegroundWindow@4")(hWnd);
}

// _SetFocus@4
typedef HWND (WINAPI *PFN_SetFocus)(HWND);
extern PFN_SetFocus __identifier("_imp__SetFocus@4");
HWND WINAPI SetFocus(HWND hWnd) {
 return __identifier("_imp__SetFocus@4")(hWnd);
}

// _SetWindowPos@28
typedef BOOL (WINAPI *PFN_SetWindowPos)(HWND, HWND, int, int, int, int, UINT);
extern PFN_SetWindowPos __identifier("_imp__SetWindowPos@28");
BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
 return __identifier("_imp__SetWindowPos@28")(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

// _CreateWindowExW@48
typedef HWND (WINAPI *PFN_CreateWindowExW)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
extern PFN_CreateWindowExW __identifier("_imp__CreateWindowExW@48");
HWND WINAPI CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
 return __identifier("_imp__CreateWindowExW@48")(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

// _GetSystemMetrics@4
typedef int (WINAPI *PFN_GetSystemMetrics)(int);
extern PFN_GetSystemMetrics __identifier("_imp__GetSystemMetrics@4");
int WINAPI GetSystemMetrics(int nIndex) {
 return __identifier("_imp__GetSystemMetrics@4")(nIndex);
}

// _AdjustWindowRect@12
typedef BOOL (WINAPI *PFN_AdjustWindowRect)(LPRECT, DWORD, BOOL);
extern PFN_AdjustWindowRect __identifier("_imp__AdjustWindowRect@12");
BOOL WINAPI AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu) {
 return __identifier("_imp__AdjustWindowRect@12")(lpRect, dwStyle, bMenu);
}

// _RegisterClassW@4
typedef ATOM (WINAPI *PFN_RegisterClassW)(CONST WNDCLASSW *);
extern PFN_RegisterClassW __identifier("_imp__RegisterClassW@4");
ATOM WINAPI RegisterClassW(CONST WNDCLASSW * lpWndClass) {
 return __identifier("_imp__RegisterClassW@4")(lpWndClass);
}

// _LoadImageA@24
typedef HANDLE (WINAPI *PFN_LoadImageA)(HINSTANCE, LPCSTR, UINT, int, int, UINT);
extern PFN_LoadImageA __identifier("_imp__LoadImageA@24");
HANDLE WINAPI LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad) {
 return __identifier("_imp__LoadImageA@24")(hInst, name, type, cx, cy, fuLoad);
}

// _FindWindowW@8
typedef HWND (WINAPI *PFN_FindWindowW)(LPCWSTR, LPCWSTR);
extern PFN_FindWindowW __identifier("_imp__FindWindowW@8");
HWND WINAPI FindWindowW(LPCWSTR lpClassName, LPCWSTR lpWindowName) {
 return __identifier("_imp__FindWindowW@8")(lpClassName, lpWindowName);
}

// _CharLowerA@4
typedef LPSTR (WINAPI *PFN_CharLowerA)(LPSTR);
extern PFN_CharLowerA __identifier("_imp__CharLowerA@4");
LPSTR WINAPI CharLowerA(LPSTR lpsz) {
 return __identifier("_imp__CharLowerA@4")(lpsz);
}

// _CharLowerW@4
typedef LPWSTR (WINAPI *PFN_CharLowerW)(LPWSTR);
extern PFN_CharLowerW __identifier("_imp__CharLowerW@4");
LPWSTR WINAPI CharLowerW(LPWSTR lpsz) {
 return __identifier("_imp__CharLowerW@4")(lpsz);
}

// _CharUpperA@4
typedef LPSTR (WINAPI *PFN_CharUpperA)(LPSTR);
extern PFN_CharUpperA __identifier("_imp__CharUpperA@4");
LPSTR WINAPI CharUpperA(LPSTR lpsz) {
 return __identifier("_imp__CharUpperA@4")(lpsz);
}

// _CharUpperW@4
typedef LPWSTR (WINAPI *PFN_CharUpperW)(LPWSTR);
extern PFN_CharUpperW __identifier("_imp__CharUpperW@4");
LPWSTR WINAPI CharUpperW(LPWSTR lpsz) {
 return __identifier("_imp__CharUpperW@4")(lpsz);
}

// _UnregisterClassA@8
typedef BOOL (WINAPI *PFN_UnregisterClassA)(LPCSTR, HINSTANCE);
extern PFN_UnregisterClassA __identifier("_imp__UnregisterClassA@8");
BOOL WINAPI UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance) {
 return __identifier("_imp__UnregisterClassA@8")(lpClassName, hInstance);
}

// _MessageBoxA@16
typedef int (WINAPI *PFN_MessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
extern PFN_MessageBoxA __identifier("_imp__MessageBoxA@16");
int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
 return __identifier("_imp__MessageBoxA@16")(hWnd, lpText, lpCaption, uType);
}

// _GetWindowLongA@8
typedef LONG (WINAPI *PFN_GetWindowLongA)(HWND, int);
extern PFN_GetWindowLongA __identifier("_imp__GetWindowLongA@8");
LONG WINAPI GetWindowLongA(HWND hWnd, int nIndex) {
 return __identifier("_imp__GetWindowLongA@8")(hWnd, nIndex);
}

// _EnumThreadWindows@12
typedef BOOL (WINAPI *PFN_EnumThreadWindows)(DWORD, WNDENUMPROC, LPARAM);
extern PFN_EnumThreadWindows __identifier("_imp__EnumThreadWindows@12");
BOOL WINAPI EnumThreadWindows(DWORD dwThreadId, WNDENUMPROC lpfn, LPARAM lParam) {
 return __identifier("_imp__EnumThreadWindows@12")(dwThreadId, lpfn, lParam);
}

// _wvsprintfA@12
typedef int (WINAPI *PFN_wvsprintfA)(LPSTR, LPCSTR, va_list);
extern PFN_wvsprintfA __identifier("_imp__wvsprintfA@12");
int WINAPI wvsprintfA(LPSTR lpOutput, LPCSTR lpFmt, va_list arglist) {
 return __identifier("_imp__wvsprintfA@12")(lpOutput, lpFmt, arglist);
}

// _CloseClipboard@0
typedef BOOL (WINAPI *PFN_CloseClipboard)(VOID);
extern PFN_CloseClipboard __identifier("_imp__CloseClipboard@0");
BOOL WINAPI CloseClipboard(VOID) {
 return __identifier("_imp__CloseClipboard@0")();
}

// _SetClipboardData@8
typedef HANDLE (WINAPI *PFN_SetClipboardData)(UINT, HANDLE);
extern PFN_SetClipboardData __identifier("_imp__SetClipboardData@8");
HANDLE WINAPI SetClipboardData(UINT uFormat, HANDLE hMem) {
 return __identifier("_imp__SetClipboardData@8")(uFormat, hMem);
}

// _EmptyClipboard@0
typedef BOOL (WINAPI *PFN_EmptyClipboard)(VOID);
extern PFN_EmptyClipboard __identifier("_imp__EmptyClipboard@0");
BOOL WINAPI EmptyClipboard(VOID) {
 return __identifier("_imp__EmptyClipboard@0")();
}

// _OpenClipboard@4
typedef BOOL (WINAPI *PFN_OpenClipboard)(HWND);
extern PFN_OpenClipboard __identifier("_imp__OpenClipboard@4");
BOOL WINAPI OpenClipboard(HWND hWndNewOwner) {
 return __identifier("_imp__OpenClipboard@4")(hWndNewOwner);
}

// _SendMessageA@16
typedef LRESULT (WINAPI *PFN_SendMessageA)(HWND, UINT, WPARAM, LPARAM);
extern PFN_SendMessageA __identifier("_imp__SendMessageA@16");
LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
 return __identifier("_imp__SendMessageA@16")(hWnd, Msg, wParam, lParam);
}

// _SendDlgItemMessageA@20
typedef LRESULT (WINAPI *PFN_SendDlgItemMessageA)(HWND, int, UINT, WPARAM, LPARAM);
extern PFN_SendDlgItemMessageA __identifier("_imp__SendDlgItemMessageA@20");
LRESULT WINAPI SendDlgItemMessageA(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) {
 return __identifier("_imp__SendDlgItemMessageA@20")(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

// _GetDlgItem@8
typedef HWND (WINAPI *PFN_GetDlgItem)(HWND, int);
extern PFN_GetDlgItem __identifier("_imp__GetDlgItem@8");
HWND WINAPI GetDlgItem(HWND hDlg, int nIDDlgItem) {
 return __identifier("_imp__GetDlgItem@8")(hDlg, nIDDlgItem);
}

// _EndDialog@8
typedef BOOL (WINAPI *PFN_EndDialog)(HWND, INT_PTR);
extern PFN_EndDialog __identifier("_imp__EndDialog@8");
BOOL WINAPI EndDialog(HWND hDlg, INT_PTR nResult) {
 return __identifier("_imp__EndDialog@8")(hDlg, nResult);
}

// _SetWindowTextA@8
typedef BOOL (WINAPI *PFN_SetWindowTextA)(HWND, LPCSTR);
extern PFN_SetWindowTextA __identifier("_imp__SetWindowTextA@8");
BOOL WINAPI SetWindowTextA(HWND hWnd, LPCSTR lpString) {
 return __identifier("_imp__SetWindowTextA@8")(hWnd, lpString);
}

// _KillTimer@8
typedef BOOL (WINAPI *PFN_KillTimer)(HWND, UINT_PTR);
extern PFN_KillTimer __identifier("_imp__KillTimer@8");
BOOL WINAPI KillTimer(HWND hWnd, UINT_PTR uIDEvent) {
 return __identifier("_imp__KillTimer@8")(hWnd, uIDEvent);
}

// _DialogBoxIndirectParamA@20
typedef INT_PTR (WINAPI *PFN_DialogBoxIndirectParamA)(HINSTANCE, LPCDLGTEMPLATEA, HWND, DLGPROC, LPARAM);
extern PFN_DialogBoxIndirectParamA __identifier("_imp__DialogBoxIndirectParamA@20");
INT_PTR WINAPI DialogBoxIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) {
 return __identifier("_imp__DialogBoxIndirectParamA@20")(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

// _SetTimer@16
typedef UINT_PTR (WINAPI *PFN_SetTimer)(HWND, UINT_PTR, UINT, TIMERPROC);
extern PFN_SetTimer __identifier("_imp__SetTimer@16");
UINT_PTR WINAPI SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) {
 return __identifier("_imp__SetTimer@16")(hWnd, nIDEvent, uElapse, lpTimerFunc);
}

// _DrawMenuBar@4
typedef BOOL (WINAPI *PFN_DrawMenuBar)(HWND);
extern PFN_DrawMenuBar __identifier("_imp__DrawMenuBar@4");
BOOL WINAPI DrawMenuBar(HWND hWnd) {
 return __identifier("_imp__DrawMenuBar@4")(hWnd);
}

// _DeleteMenu@12
typedef BOOL (WINAPI *PFN_DeleteMenu)(HMENU, UINT, UINT);
extern PFN_DeleteMenu __identifier("_imp__DeleteMenu@12");
BOOL WINAPI DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags) {
 return __identifier("_imp__DeleteMenu@12")(hMenu, uPosition, uFlags);
}

// _GetSystemMenu@8
typedef HMENU (WINAPI *PFN_GetSystemMenu)(HWND, BOOL);
extern PFN_GetSystemMenu __identifier("_imp__GetSystemMenu@8");
HMENU WINAPI GetSystemMenu(HWND hWnd, BOOL bRevert) {
 return __identifier("_imp__GetSystemMenu@8")(hWnd, bRevert);
}

// _FindWindowA@8
typedef HWND (WINAPI *PFN_FindWindowA)(LPCSTR, LPCSTR);
extern PFN_FindWindowA __identifier("_imp__FindWindowA@8");
HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
 return __identifier("_imp__FindWindowA@8")(lpClassName, lpWindowName);
}

// _ScreenToClient@8
typedef BOOL (WINAPI *PFN_ScreenToClient)(HWND, LPPOINT);
extern PFN_ScreenToClient __identifier("_imp__ScreenToClient@8");
BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint) {
 return __identifier("_imp__ScreenToClient@8")(hWnd, lpPoint);
}

// _SetCursor@4
typedef HCURSOR (WINAPI *PFN_SetCursor)(HCURSOR);
extern PFN_SetCursor __identifier("_imp__SetCursor@4");
HCURSOR WINAPI SetCursor(HCURSOR hCursor) {
 return __identifier("_imp__SetCursor@4")(hCursor);
}

// _SetCursorPos@8
typedef BOOL (WINAPI *PFN_SetCursorPos)(int, int);
extern PFN_SetCursorPos __identifier("_imp__SetCursorPos@8");
BOOL WINAPI SetCursorPos(int X, int Y) {
 return __identifier("_imp__SetCursorPos@8")(X, Y);
}

// _ClientToScreen@8
typedef BOOL (WINAPI *PFN_ClientToScreen)(HWND, LPPOINT);
extern PFN_ClientToScreen __identifier("_imp__ClientToScreen@8");
BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint) {
 return __identifier("_imp__ClientToScreen@8")(hWnd, lpPoint);
}

// _LoadCursorFromFileA@4
typedef HCURSOR (WINAPI *PFN_LoadCursorFromFileA)(LPCSTR);
extern PFN_LoadCursorFromFileA __identifier("_imp__LoadCursorFromFileA@4");
HCURSOR WINAPI LoadCursorFromFileA(LPCSTR lpFileName) {
 return __identifier("_imp__LoadCursorFromFileA@4")(lpFileName);
}

// _IsIconic@4
typedef BOOL (WINAPI *PFN_IsIconic)(HWND);
extern PFN_IsIconic __identifier("_imp__IsIconic@4");
BOOL WINAPI IsIconic(HWND hWnd) {
 return __identifier("_imp__IsIconic@4")(hWnd);
}

// _DispatchMessageA@4
typedef LRESULT (WINAPI *PFN_DispatchMessageA)(CONST MSG *);
extern PFN_DispatchMessageA __identifier("_imp__DispatchMessageA@4");
LRESULT WINAPI DispatchMessageA(CONST MSG * lpMsg) {
 return __identifier("_imp__DispatchMessageA@4")(lpMsg);
}

// _TranslateMessage@4
typedef BOOL (WINAPI *PFN_TranslateMessage)(CONST MSG *);
extern PFN_TranslateMessage __identifier("_imp__TranslateMessage@4");
BOOL WINAPI TranslateMessage(CONST MSG * lpMsg) {
 return __identifier("_imp__TranslateMessage@4")(lpMsg);
}

// _GetMessageA@16
typedef BOOL (WINAPI *PFN_GetMessageA)(LPMSG, HWND, UINT, UINT);
extern PFN_GetMessageA __identifier("_imp__GetMessageA@16");
BOOL WINAPI GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) {
 return __identifier("_imp__GetMessageA@16")(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

// _PeekMessageA@20
typedef BOOL (WINAPI *PFN_PeekMessageA)(LPMSG, HWND, UINT, UINT, UINT);
extern PFN_PeekMessageA __identifier("_imp__PeekMessageA@20");
BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
 return __identifier("_imp__PeekMessageA@20")(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

// _IsRectEmpty@4
typedef BOOL (WINAPI *PFN_IsRectEmpty)(CONST RECT *);
extern PFN_IsRectEmpty __identifier("_imp__IsRectEmpty@4");
BOOL WINAPI IsRectEmpty(CONST RECT * lprc) {
 return __identifier("_imp__IsRectEmpty@4")(lprc);
}

// _GetKeyState@4
typedef SHORT (WINAPI *PFN_GetKeyState)(int);
extern PFN_GetKeyState __identifier("_imp__GetKeyState@4");
SHORT WINAPI GetKeyState(int nVirtKey) {
 return __identifier("_imp__GetKeyState@4")(nVirtKey);
}

// _GetCursorPos@4
typedef BOOL (WINAPI *PFN_GetCursorPos)(LPPOINT);
extern PFN_GetCursorPos __identifier("_imp__GetCursorPos@4");
BOOL WINAPI GetCursorPos(LPPOINT lpPoint) {
 return __identifier("_imp__GetCursorPos@4")(lpPoint);
}

// _GetAsyncKeyState@4
typedef SHORT (WINAPI *PFN_GetAsyncKeyState)(int);
extern PFN_GetAsyncKeyState __identifier("_imp__GetAsyncKeyState@4");
SHORT WINAPI GetAsyncKeyState(int vKey) {
 return __identifier("_imp__GetAsyncKeyState@4")(vKey);
}

// _ReleaseDC@8
typedef int (WINAPI *PFN_ReleaseDC)(HWND, HDC);
extern PFN_ReleaseDC __identifier("_imp__ReleaseDC@8");
int WINAPI ReleaseDC(HWND hWnd, HDC hDC) {
 return __identifier("_imp__ReleaseDC@8")(hWnd, hDC);
}

// _GetDC@4
typedef HDC (WINAPI *PFN_GetDC)(HWND);
extern PFN_GetDC __identifier("_imp__GetDC@4");
HDC WINAPI GetDC(HWND hWnd) {
 return __identifier("_imp__GetDC@4")(hWnd);
}

// _GetDesktopWindow@0
typedef HWND (WINAPI *PFN_GetDesktopWindow)(VOID);
extern PFN_GetDesktopWindow __identifier("_imp__GetDesktopWindow@0");
HWND WINAPI GetDesktopWindow(VOID) {
 return __identifier("_imp__GetDesktopWindow@0")();
}

// _SetRect@20
typedef BOOL (WINAPI *PFN_SetRect)(LPRECT, int, int, int, int);
extern PFN_SetRect __identifier("_imp__SetRect@20");
BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom) {
 return __identifier("_imp__SetRect@20")(lprc, xLeft, yTop, xRight, yBottom);
}

// _ShowCursor@4
typedef int (WINAPI *PFN_ShowCursor)(BOOL);
extern PFN_ShowCursor __identifier("_imp__ShowCursor@4");
int WINAPI ShowCursor(BOOL bShow) {
 return __identifier("_imp__ShowCursor@4")(bShow);
}

// _MessageBoxW@16
typedef int (WINAPI *PFN_MessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT);
extern PFN_MessageBoxW __identifier("_imp__MessageBoxW@16");
int WINAPI MessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
 return __identifier("_imp__MessageBoxW@16")(hWnd, lpText, lpCaption, uType);
}

// _GetKeyboardLayout@4
typedef HKL (WINAPI *PFN_GetKeyboardLayout)(DWORD);
extern PFN_GetKeyboardLayout __identifier("_imp__GetKeyboardLayout@4");
HKL WINAPI GetKeyboardLayout(DWORD idThread) {
 return __identifier("_imp__GetKeyboardLayout@4")(idThread);
}

// _GetKeyboardLayoutList@8
typedef int (WINAPI *PFN_GetKeyboardLayoutList)(int, HKL FAR *);
extern PFN_GetKeyboardLayoutList __identifier("_imp__GetKeyboardLayoutList@8");
int WINAPI GetKeyboardLayoutList(int nBuff, HKL FAR * lpList) {
 return __identifier("_imp__GetKeyboardLayoutList@8")(nBuff, lpList);
}

// _GetDoubleClickTime@0
typedef UINT (WINAPI *PFN_GetDoubleClickTime)(VOID);
extern PFN_GetDoubleClickTime __identifier("_imp__GetDoubleClickTime@0");
UINT WINAPI GetDoubleClickTime(VOID) {
 return __identifier("_imp__GetDoubleClickTime@0")();
}

// _EnableMenuItem@12
typedef BOOL (WINAPI *PFN_EnableMenuItem)(HMENU, UINT, UINT);
extern PFN_EnableMenuItem __identifier("_imp__EnableMenuItem@12");
BOOL WINAPI EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable) {
 return __identifier("_imp__EnableMenuItem@12")(hMenu, uIDEnableItem, uEnable);
}

// _SetWindowTextW@8
typedef BOOL (WINAPI *PFN_SetWindowTextW)(HWND, LPCWSTR);
extern PFN_SetWindowTextW __identifier("_imp__SetWindowTextW@8");
BOOL WINAPI SetWindowTextW(HWND hWnd, LPCWSTR lpString) {
 return __identifier("_imp__SetWindowTextW@8")(hWnd, lpString);
}

// _GetForegroundWindow@0
typedef HWND (WINAPI *PFN_GetForegroundWindow)(VOID);
extern PFN_GetForegroundWindow __identifier("_imp__GetForegroundWindow@0");
HWND WINAPI GetForegroundWindow(VOID) {
 return __identifier("_imp__GetForegroundWindow@0")();
}

// _PostThreadMessageA@16
typedef BOOL (WINAPI *PFN_PostThreadMessageA)(DWORD, UINT, WPARAM, LPARAM);
extern PFN_PostThreadMessageA __identifier("_imp__PostThreadMessageA@16");
BOOL WINAPI PostThreadMessageA(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam) {
 return __identifier("_imp__PostThreadMessageA@16")(idThread, Msg, wParam, lParam);
}
}
