// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// dxsdk
// dinput8.dll import thunk: typed C++ forwarding through the genuine PE
// import-pointer symbol, as Kernel32ImportThunks.cpp and
// D3DX9ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signature: the August 2005 DirectX SDK dinput.h (DIRECTINPUT_VERSION
// 0x0800); its declaration carries no dllimport. Win32DIMouse.cpp
// and Win32DIKeyboard.cpp call it with a direct call, which reaches this thunk.
// The retail six-byte thunk's IAT slot names the export (row notes).
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <dinput.h>
extern "C" {
// _DirectInput8Create@20
typedef HRESULT (WINAPI *PFN_DirectInput8Create)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
extern PFN_DirectInput8Create __identifier("_imp__DirectInput8Create@20");
HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter) {
 return __identifier("_imp__DirectInput8Create@20")(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}
}
