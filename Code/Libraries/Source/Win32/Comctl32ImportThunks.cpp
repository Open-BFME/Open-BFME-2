// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// comctl32.dll import thunk: typed C++ forwarding through the genuine PE
// import-pointer symbol, as Kernel32ImportThunks.cpp and
// Netapi32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signature: the VS2003 Platform SDK CommCtrl.h; _COMCTL32_ (the header's own
// switch) drops its DECLSPEC_IMPORT so the definition is the thunk.
// The retail six-byte thunk's IAT slot names the export (row notes).
#define _COMCTL32_
#include <windows.h>
#include <commctrl.h>
extern "C" {
// _InitCommonControls@0
typedef void (WINAPI *PFN_InitCommonControls)(void);
extern PFN_InitCommonControls __identifier("_imp__InitCommonControls@0");
void WINAPI InitCommonControls(void) {
 __identifier("_imp__InitCommonControls@0")();
}
}
