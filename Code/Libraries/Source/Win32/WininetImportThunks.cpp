// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// wininet.dll import thunk: typed C++ forwarding through the genuine PE
// import-pointer symbol, as Kernel32ImportThunks.cpp and
// Netapi32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signature: the VS2003 Platform SDK WinInet.h; _WINX32_ (the header's own
// switch) drops its DECLSPEC_IMPORT so the definition is the thunk.
// The retail six-byte thunk's IAT slot names the export (row notes).
#define _WINX32_
#include <windows.h>
#include <wininet.h>
extern "C" {
// _InternetCrackUrlA@16
typedef BOOL (STDAPICALLTYPE *PFN_InternetCrackUrlA)(LPCSTR, DWORD, DWORD, LPURL_COMPONENTSA);
extern PFN_InternetCrackUrlA __identifier("_imp__InternetCrackUrlA@16");
BOOL STDAPICALLTYPE InternetCrackUrlA(LPCSTR lpszUrl, DWORD dwUrlLength, DWORD dwFlags, LPURL_COMPONENTSA lpUrlComponents) {
 return __identifier("_imp__InternetCrackUrlA@16")(lpszUrl, dwUrlLength, dwFlags, lpUrlComponents);
}
}
