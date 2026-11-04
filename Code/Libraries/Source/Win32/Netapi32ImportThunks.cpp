// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// netapi32.dll import thunk: typed C++ forwarding through the genuine PE
// import-pointer symbol, as Kernel32ImportThunks.cpp and
// Wsock32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signature: the VS2003 Platform SDK Nb30.h, included through windows.h; its
// declaration carries no dllimport. Y2NetConn.cpp's NetBIOS adapter queries
// call it.
// The retail six-byte thunk's IAT slot names the export (row notes).
#include <windows.h>
extern "C" {
// _Netbios@4
typedef UCHAR (APIENTRY *PFN_Netbios)(PNCB);
extern PFN_Netbios __identifier("_imp__Netbios@4");
UCHAR APIENTRY Netbios(PNCB pncb) {
 return __identifier("_imp__Netbios@4")(pncb);
}
}
