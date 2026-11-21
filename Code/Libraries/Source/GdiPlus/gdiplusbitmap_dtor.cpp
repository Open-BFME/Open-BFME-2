// cl: /O1 /EHsc
// platformsdk
// Microsoft Platform SDK GDI+ 1.0 GdiPlusBitmap.h inlines, emitted out of line
// by the ATL 7.1 CImage translation unit that carries the Gdiplus::Image and
// Gdiplus::Bitmap vtables.
//
// Bitmap's constructors share this unit with Image's scalar deleting destructor.
// Under /EHsc that one folds ~Image in whole (36 bytes: the vftable store at
// 0x00BBB524 and the dispose), while Bitmap's calls the out-of-line implicit
// ~Bitmap (27 bytes). The constructors only call extern "C" GDI+ entry points,
// so /EHsc gives them no frame.

#include <windows.h>
#include <gdiplus.h>

namespace Gdiplus
{

// ?bfmeAnchorGdiplusBitmapDtor absent-from-retail
Bitmap *bfmeAnchorGdiplusBitmapDtor(const WCHAR *filename, BOOL useEmbeddedColorManagement,
    INT width, INT height, INT stride, PixelFormat format, BYTE *scan0)
{
    Bitmap *a = new Bitmap(filename, useEmbeddedColorManagement);
    delete a;
    return new Bitmap(width, height, stride, format, scan0);
}

}
