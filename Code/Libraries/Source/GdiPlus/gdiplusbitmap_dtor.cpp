// cl: /O1 /GX-
// platformsdk
// Microsoft Platform SDK GDI+ 1.0 GdiPlusBitmap.h inlines, emitted out of line
// by the ATL 7.1 CImage translation unit that carries the Gdiplus::Image and
// Gdiplus::Bitmap vtables.
//
// Bitmap's constructors and scalar deleting destructor share this unit. Its 36 bytes are
// ~Image folded in whole - the vftable store at 0x00BBB524 and the dispose -
// because the destructor is DEFINED here rather than declared. The main unit
// keeps the out-of-line definition, which is what lets Image's own scalar
// deleting destructor at 0x00002111 stay a 27-byte call; define it in the
// class there and that body grows to 30.

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
