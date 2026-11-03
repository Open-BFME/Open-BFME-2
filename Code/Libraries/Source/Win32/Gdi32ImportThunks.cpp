// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// gdi32.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as Kernel32ImportThunks.cpp and
// User32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signatures: the VS2003 Platform SDK WinGDI.h, included with _GDI32_ defined
// (the header's own switch) so WINGDIAPI is empty and these definitions are
// not dllimport. WinGDI.h leaves most parameters unnamed; the names here are
// the documented Win32 API parameter names.
// Each retail six-byte thunk's IAT slot names the export (row notes).
#define _GDI32_
#include <windows.h>
extern "C" {
// _CreateCompatibleDC@4
typedef HDC (WINAPI *PFN_CreateCompatibleDC)(HDC);
extern PFN_CreateCompatibleDC __identifier("_imp__CreateCompatibleDC@4");
HDC WINAPI CreateCompatibleDC(HDC hdc) {
 return __identifier("_imp__CreateCompatibleDC@4")(hdc);
}

// _DeleteDC@4
typedef BOOL (WINAPI *PFN_DeleteDC)(HDC);
extern PFN_DeleteDC __identifier("_imp__DeleteDC@4");
BOOL WINAPI DeleteDC(HDC hdc) {
 return __identifier("_imp__DeleteDC@4")(hdc);
}

// _SelectObject@8
typedef HGDIOBJ (WINAPI *PFN_SelectObject)(HDC, HGDIOBJ);
extern PFN_SelectObject __identifier("_imp__SelectObject@8");
HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h) {
 return __identifier("_imp__SelectObject@8")(hdc, h);
}

// _SetDIBColorTable@16
typedef UINT (WINAPI *PFN_SetDIBColorTable)(HDC, UINT, UINT, CONST RGBQUAD *);
extern PFN_SetDIBColorTable __identifier("_imp__SetDIBColorTable@16");
UINT WINAPI SetDIBColorTable(HDC hdc, UINT iStart, UINT cEntries, CONST RGBQUAD * prgbq) {
 return __identifier("_imp__SetDIBColorTable@16")(hdc, iStart, cEntries, prgbq);
}

// _GetObjectA@12
typedef int (WINAPI *PFN_GetObjectA)(HGDIOBJ, int, LPVOID);
extern PFN_GetObjectA __identifier("_imp__GetObjectA@12");
int WINAPI GetObjectA(HGDIOBJ h, int bufferSize, LPVOID pv) {
 return __identifier("_imp__GetObjectA@12")(h, bufferSize, pv);
}

// _RestoreDC@8
typedef BOOL (WINAPI *PFN_RestoreDC)(HDC, int);
extern PFN_RestoreDC __identifier("_imp__RestoreDC@8");
BOOL WINAPI RestoreDC(HDC hdc, int nSavedDC) {
 return __identifier("_imp__RestoreDC@8")(hdc, nSavedDC);
}

// _BitBlt@36
typedef BOOL (WINAPI *PFN_BitBlt)(HDC, int, int, int, int, HDC, int, int, DWORD);
extern PFN_BitBlt __identifier("_imp__BitBlt@36");
BOOL WINAPI BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop) {
 return __identifier("_imp__BitBlt@36")(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

// _SaveDC@4
typedef int (WINAPI *PFN_SaveDC)(HDC);
extern PFN_SaveDC __identifier("_imp__SaveDC@4");
int WINAPI SaveDC(HDC hdc) {
 return __identifier("_imp__SaveDC@4")(hdc);
}

// _DeleteObject@4
typedef BOOL (WINAPI *PFN_DeleteObject)(HGDIOBJ);
extern PFN_DeleteObject __identifier("_imp__DeleteObject@4");
BOOL WINAPI DeleteObject(HGDIOBJ ho) {
 return __identifier("_imp__DeleteObject@4")(ho);
}

// _CreateDIBSection@24
typedef HBITMAP (WINAPI *PFN_CreateDIBSection)(HDC, CONST BITMAPINFO *, UINT, VOID **, HANDLE, DWORD);
extern PFN_CreateDIBSection __identifier("_imp__CreateDIBSection@24");
HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO * pbmi, UINT usage, VOID ** ppvBits, HANDLE hSection, DWORD offset) {
 return __identifier("_imp__CreateDIBSection@24")(hdc, pbmi, usage, ppvBits, hSection, offset);
}

// _GetStockObject@4
typedef HGDIOBJ (WINAPI *PFN_GetStockObject)(int);
extern PFN_GetStockObject __identifier("_imp__GetStockObject@4");
HGDIOBJ WINAPI GetStockObject(int i) {
 return __identifier("_imp__GetStockObject@4")(i);
}

// _CreateFontA@56
typedef HFONT (WINAPI *PFN_CreateFontA)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
extern PFN_CreateFontA __identifier("_imp__CreateFontA@56");
HFONT WINAPI CreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName) {
 return __identifier("_imp__CreateFontA@56")(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
}

// _SetDeviceGammaRamp@8
typedef BOOL (WINAPI *PFN_SetDeviceGammaRamp)(HDC, LPVOID);
extern PFN_SetDeviceGammaRamp __identifier("_imp__SetDeviceGammaRamp@8");
BOOL WINAPI SetDeviceGammaRamp(HDC hdc, LPVOID lpRamp) {
 return __identifier("_imp__SetDeviceGammaRamp@8")(hdc, lpRamp);
}

// _SetTextColor@8
typedef COLORREF (WINAPI *PFN_SetTextColor)(HDC, COLORREF);
extern PFN_SetTextColor __identifier("_imp__SetTextColor@8");
COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color) {
 return __identifier("_imp__SetTextColor@8")(hdc, color);
}

// _SetBkColor@8
typedef COLORREF (WINAPI *PFN_SetBkColor)(HDC, COLORREF);
extern PFN_SetBkColor __identifier("_imp__SetBkColor@8");
COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color) {
 return __identifier("_imp__SetBkColor@8")(hdc, color);
}

// _GetGlyphIndicesW@20
typedef DWORD (WINAPI *PFN_GetGlyphIndicesW)(HDC, LPCWSTR, int, LPWORD, DWORD);
extern PFN_GetGlyphIndicesW __identifier("_imp__GetGlyphIndicesW@20");
DWORD WINAPI GetGlyphIndicesW(HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl) {
 return __identifier("_imp__GetGlyphIndicesW@20")(hdc, lpstr, c, pgi, fl);
}

// _GetTextMetricsA@8
typedef BOOL (WINAPI *PFN_GetTextMetricsA)(HDC, LPTEXTMETRICA);
extern PFN_GetTextMetricsA __identifier("_imp__GetTextMetricsA@8");
BOOL WINAPI GetTextMetricsA(HDC hdc, LPTEXTMETRICA lptm) {
 return __identifier("_imp__GetTextMetricsA@8")(hdc, lptm);
}

// _ExtTextOutW@32
typedef BOOL (WINAPI *PFN_ExtTextOutW)(HDC, int, int, UINT, CONST RECT *, LPCWSTR, UINT, CONST INT *);
extern PFN_ExtTextOutW __identifier("_imp__ExtTextOutW@32");
BOOL WINAPI ExtTextOutW(HDC hdc, int x, int y, UINT options, CONST RECT * lprect, LPCWSTR lpString, UINT c, CONST INT * lpDx) {
 return __identifier("_imp__ExtTextOutW@32")(hdc, x, y, options, lprect, lpString, c, lpDx);
}

// _GetTextExtentPoint32W@16
typedef BOOL (APIENTRY *PFN_GetTextExtentPoint32W)(HDC, LPCWSTR, int, LPSIZE);
extern PFN_GetTextExtentPoint32W __identifier("_imp__GetTextExtentPoint32W@16");
BOOL APIENTRY GetTextExtentPoint32W(HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl) {
 return __identifier("_imp__GetTextExtentPoint32W@16")(hdc, lpString, c, psizl);
}

// _GetCharABCWidthsI@20
typedef BOOL (WINAPI *PFN_GetCharABCWidthsI)(HDC, UINT, UINT, LPWORD, LPABC);
extern PFN_GetCharABCWidthsI __identifier("_imp__GetCharABCWidthsI@20");
BOOL WINAPI GetCharABCWidthsI(HDC hdc, UINT giFirst, UINT cgi, LPWORD pgi, LPABC pabc) {
 return __identifier("_imp__GetCharABCWidthsI@20")(hdc, giFirst, cgi, pgi, pabc);
}

// _GetTextExtentPointI@16
typedef BOOL (WINAPI *PFN_GetTextExtentPointI)(HDC, LPWORD, int, LPSIZE);
extern PFN_GetTextExtentPointI __identifier("_imp__GetTextExtentPointI@16");
BOOL WINAPI GetTextExtentPointI(HDC hdc, LPWORD pgiIn, int cgi, LPSIZE psize) {
 return __identifier("_imp__GetTextExtentPointI@16")(hdc, pgiIn, cgi, psize);
}

// _GetPixel@12
typedef COLORREF (WINAPI *PFN_GetPixel)(HDC, int, int);
extern PFN_GetPixel __identifier("_imp__GetPixel@12");
COLORREF WINAPI GetPixel(HDC hdc, int x, int y) {
 return __identifier("_imp__GetPixel@12")(hdc, x, y);
}

// _ExtTextOutA@32
typedef BOOL (WINAPI *PFN_ExtTextOutA)(HDC, int, int, UINT, CONST RECT *, LPCSTR, UINT, CONST INT *);
extern PFN_ExtTextOutA __identifier("_imp__ExtTextOutA@32");
BOOL WINAPI ExtTextOutA(HDC hdc, int x, int y, UINT options, CONST RECT * lprect, LPCSTR lpString, UINT c, CONST INT * lpDx) {
 return __identifier("_imp__ExtTextOutA@32")(hdc, x, y, options, lprect, lpString, c, lpDx);
}

// _SetBkMode@8
typedef int (WINAPI *PFN_SetBkMode)(HDC, int);
extern PFN_SetBkMode __identifier("_imp__SetBkMode@8");
int WINAPI SetBkMode(HDC hdc, int mode) {
 return __identifier("_imp__SetBkMode@8")(hdc, mode);
}

// _CreateBitmap@20
typedef HBITMAP (WINAPI *PFN_CreateBitmap)(int, int, UINT, UINT, CONST VOID *);
extern PFN_CreateBitmap __identifier("_imp__CreateBitmap@20");
HBITMAP WINAPI CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, CONST VOID * lpBits) {
 return __identifier("_imp__CreateBitmap@20")(nWidth, nHeight, nPlanes, nBitCount, lpBits);
}
}
