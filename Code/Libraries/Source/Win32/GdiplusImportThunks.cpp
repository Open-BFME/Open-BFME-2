// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// gdiplus.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as Kernel32ImportThunks.cpp and
// Avifil32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signatures: the VS2003 Platform SDK GDI+ 1.0 headers (GdiPlusMem.h and
// GdiPlusFlat.h inside Gdiplus::DllExports, GdiPlusInit.h inside Gdiplus, as
// GdiPlus.h nests them); their WINGDIPAPI/WINAPI declarations carry no
// dllimport. GdiPlusFlat.h leaves some parameters unnamed; the documented
// names are used.
// Each retail six-byte thunk's IAT slot names the export (row notes).
#include <windows.h>
#include <gdiplus.h>

namespace Gdiplus {
namespace DllExports {
extern "C" {
// _GdipAlloc@4
typedef void* (WINGDIPAPI *PFN_GdipAlloc)(size_t);
extern PFN_GdipAlloc __identifier("_imp__GdipAlloc@4");
void* WINGDIPAPI GdipAlloc(size_t size) {
 return __identifier("_imp__GdipAlloc@4")(size);
}

// _GdipFree@4
typedef void (WINGDIPAPI *PFN_GdipFree)(void*);
extern PFN_GdipFree __identifier("_imp__GdipFree@4");
void WINGDIPAPI GdipFree(void* ptr) {
 __identifier("_imp__GdipFree@4")(ptr);
}
}
}
}

namespace Gdiplus {
extern "C" {
// _GdiplusStartup@12
typedef Status (WINAPI *PFN_GdiplusStartup)(ULONG_PTR *, const GdiplusStartupInput *, GdiplusStartupOutput *);
extern PFN_GdiplusStartup __identifier("_imp__GdiplusStartup@12");
Status WINAPI GdiplusStartup(ULONG_PTR * token, const GdiplusStartupInput * input, GdiplusStartupOutput * output) {
 return __identifier("_imp__GdiplusStartup@12")(token, input, output);
}

// _GdiplusShutdown@4
typedef VOID (WINAPI *PFN_GdiplusShutdown)(ULONG_PTR);
extern PFN_GdiplusShutdown __identifier("_imp__GdiplusShutdown@4");
VOID WINAPI GdiplusShutdown(ULONG_PTR token) {
 __identifier("_imp__GdiplusShutdown@4")(token);
}
}
}

namespace Gdiplus {
namespace DllExports {
extern "C" {
// _GdipDeleteGraphics@4
typedef GpStatus (WINGDIPAPI *PFN_GdipDeleteGraphics)(GpGraphics *);
extern PFN_GdipDeleteGraphics __identifier("_imp__GdipDeleteGraphics@4");
GpStatus WINGDIPAPI GdipDeleteGraphics(GpGraphics * graphics) {
 return __identifier("_imp__GdipDeleteGraphics@4")(graphics);
}

// _GdipDisposeImage@4
typedef GpStatus (WINGDIPAPI *PFN_GdipDisposeImage)(GpImage *);
extern PFN_GdipDisposeImage __identifier("_imp__GdipDisposeImage@4");
GpStatus WINGDIPAPI GdipDisposeImage(GpImage * image) {
 return __identifier("_imp__GdipDisposeImage@4")(image);
}

// _GdipGetImageWidth@8
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImageWidth)(GpImage *, UINT *);
extern PFN_GdipGetImageWidth __identifier("_imp__GdipGetImageWidth@8");
GpStatus WINGDIPAPI GdipGetImageWidth(GpImage * image, UINT * width) {
 return __identifier("_imp__GdipGetImageWidth@8")(image, width);
}

// _GdipGetImageHeight@8
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImageHeight)(GpImage *, UINT *);
extern PFN_GdipGetImageHeight __identifier("_imp__GdipGetImageHeight@8");
GpStatus WINGDIPAPI GdipGetImageHeight(GpImage * image, UINT * height) {
 return __identifier("_imp__GdipGetImageHeight@8")(image, height);
}

// _GdipGetImagePixelFormat@8
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImagePixelFormat)(GpImage *, PixelFormat *);
extern PFN_GdipGetImagePixelFormat __identifier("_imp__GdipGetImagePixelFormat@8");
GpStatus WINGDIPAPI GdipGetImagePixelFormat(GpImage * image, PixelFormat * format) {
 return __identifier("_imp__GdipGetImagePixelFormat@8")(image, format);
}

// _GdipGetImagePaletteSize@8
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImagePaletteSize)(GpImage *, INT *);
extern PFN_GdipGetImagePaletteSize __identifier("_imp__GdipGetImagePaletteSize@8");
GpStatus WINGDIPAPI GdipGetImagePaletteSize(GpImage * image, INT * size) {
 return __identifier("_imp__GdipGetImagePaletteSize@8")(image, size);
}

// _GdipGetImagePalette@12
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImagePalette)(GpImage *, ColorPalette *, INT);
extern PFN_GdipGetImagePalette __identifier("_imp__GdipGetImagePalette@12");
GpStatus WINGDIPAPI GdipGetImagePalette(GpImage * image, ColorPalette * palette, INT size) {
 return __identifier("_imp__GdipGetImagePalette@12")(image, palette, size);
}

// _GdipCreateBitmapFromFile@8
typedef GpStatus (WINGDIPAPI *PFN_GdipCreateBitmapFromFile)(GDIPCONST WCHAR *, GpBitmap **);
extern PFN_GdipCreateBitmapFromFile __identifier("_imp__GdipCreateBitmapFromFile@8");
GpStatus WINGDIPAPI GdipCreateBitmapFromFile(GDIPCONST WCHAR * filename, GpBitmap ** bitmap) {
 return __identifier("_imp__GdipCreateBitmapFromFile@8")(filename, bitmap);
}

// _GdipCreateBitmapFromFileICM@8
typedef GpStatus (WINGDIPAPI *PFN_GdipCreateBitmapFromFileICM)(GDIPCONST WCHAR *, GpBitmap **);
extern PFN_GdipCreateBitmapFromFileICM __identifier("_imp__GdipCreateBitmapFromFileICM@8");
GpStatus WINGDIPAPI GdipCreateBitmapFromFileICM(GDIPCONST WCHAR * filename, GpBitmap ** bitmap) {
 return __identifier("_imp__GdipCreateBitmapFromFileICM@8")(filename, bitmap);
}

// _GdipBitmapUnlockBits@8
typedef GpStatus (WINGDIPAPI *PFN_GdipBitmapUnlockBits)(GpBitmap *, BitmapData *);
extern PFN_GdipBitmapUnlockBits __identifier("_imp__GdipBitmapUnlockBits@8");
GpStatus WINGDIPAPI GdipBitmapUnlockBits(GpBitmap * bitmap, BitmapData * lockedBitmapData) {
 return __identifier("_imp__GdipBitmapUnlockBits@8")(bitmap, lockedBitmapData);
}

// _GdipGetImageGraphicsContext@8
typedef GpStatus (WINGDIPAPI *PFN_GdipGetImageGraphicsContext)(GpImage *, GpGraphics **);
extern PFN_GdipGetImageGraphicsContext __identifier("_imp__GdipGetImageGraphicsContext@8");
GpStatus WINGDIPAPI GdipGetImageGraphicsContext(GpImage * image, GpGraphics ** graphics) {
 return __identifier("_imp__GdipGetImageGraphicsContext@8")(image, graphics);
}

// _GdipDrawImageI@16
typedef GpStatus (WINGDIPAPI *PFN_GdipDrawImageI)(GpGraphics *, GpImage *, INT, INT);
extern PFN_GdipDrawImageI __identifier("_imp__GdipDrawImageI@16");
GpStatus WINGDIPAPI GdipDrawImageI(GpGraphics * graphics, GpImage * image, INT x, INT y) {
 return __identifier("_imp__GdipDrawImageI@16")(graphics, image, x, y);
}

// _GdipCloneImage@8
typedef GpStatus (WINGDIPAPI *PFN_GdipCloneImage)(GpImage *, GpImage **);
extern PFN_GdipCloneImage __identifier("_imp__GdipCloneImage@8");
GpStatus WINGDIPAPI GdipCloneImage(GpImage * image, GpImage ** cloneImage) {
 return __identifier("_imp__GdipCloneImage@8")(image, cloneImage);
}
}
}
}
