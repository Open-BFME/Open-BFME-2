// cl: /O1 /EHsc
// platformsdk
// Microsoft Platform SDK GDI+ 1.0 GdiPlusBitmap.h inlines, emitted out of line
// by the ATL 7.1 CImage translation unit that carries the Gdiplus::Image and
// Gdiplus::Bitmap vtables.
#include <windows.h>
#include <objidl.h>
#include <float.h>

struct IDirectDrawSurface7;
#include <pshpack8.h>
namespace Gdiplus
{
namespace DllExports
{
#include <GdiPlusMem.h>
}
#include <GdiPlusBase.h>
#include <GdiPlusEnums.h>
#include <GdiPlusTypes.h>
#include <GdiPlusPixelFormats.h>
#include <GdiPlusColor.h>
#include <GdiPlusMetaHeader.h>
#include <GdiPlusImaging.h>
#include <GdiPlusColorMatrix.h>
#include <GdiPlusGpStubs.h>
#include <GdiPlusHeaders.h>
namespace DllExports
{
#include <GdiPlusFlat.h>
}
// Keep the selected bitmap inlines below: the SDK's complete class declarations
// and flat API declarations above supply their types without local copies.

// Not noinline: Image's scalar deleting destructor at 0x00001E43 folds this in
// whole, while /EHsc keeps Bitmap's (0x00002111) calling the out-of-line ~Bitmap.
inline Image::~Image()
{
    DllExports::GdipDisposeImage(nativeImage);
}

// `inline` for the COMDAT selection only, with no __declspec(noinline):
// gdiplusbitmap_dtor.cpp emits Image's vtable, which forces a second copy of
// this virtual. Without `inline` this one is SELECT_NODUPLICATES against that
// unit's SELECT_ANY copy, which is a duplicate at link -- one of the real
// link's last two (reverse/link_status.csv). noinline would also forbid
// inlining the Image ctor into this body, which retail does.
inline Image *Image::Clone()
{
    GpImage *cloneimage = 0;

    SetStatus(DllExports::GdipCloneImage(nativeImage, &cloneimage));

    return new Image(cloneimage, lastResult);
}

UINT Image::GetWidth()
{
    UINT width = 0;

    SetStatus(DllExports::GdipGetImageWidth(nativeImage, &width));

    return width;
}

UINT Image::GetHeight()
{
    UINT height = 0;

    SetStatus(DllExports::GdipGetImageHeight(nativeImage, &height));

    return height;
}

PixelFormat Image::GetPixelFormat()
{
    PixelFormat format;

    SetStatus(DllExports::GdipGetImagePixelFormat(nativeImage, &format));

    return format;
}

INT Image::GetPaletteSize()
{
    INT size = 0;

    SetStatus(DllExports::GdipGetImagePaletteSize(nativeImage, &size));

    return size;
}

Status Image::GetPalette(ColorPalette *palette, INT size)
{
    return SetStatus(DllExports::GdipGetImagePalette(nativeImage, palette, size));
}

Image::Image(GpImage *nativeImage, Status status)
{
    SetNativeImage(nativeImage);
    lastResult = status;
}

// ?Image::SetNativeImage present-unmatched
// `inline` for the same reason as Image::Clone above, and likewise without
// noinline: retail inlines this into the Image constructor.
inline void Image::SetNativeImage(GpImage *nativeImage)
{
    this->nativeImage = nativeImage;
}

inline Bitmap::Bitmap(const WCHAR *filename, BOOL useEmbeddedColorManagement)
{
    GpBitmap *bitmap = NULL;

    if (useEmbeddedColorManagement)
    {
        lastResult = DllExports::GdipCreateBitmapFromFileICM(filename, &bitmap);
    }
    else
    {
        lastResult = DllExports::GdipCreateBitmapFromFile(filename, &bitmap);
    }

    SetNativeImage(bitmap);
}

// Emits Bitmap's vtable here, and with it Bitmap's scalar deleting destructor
// and the implicit ~Bitmap it calls.
// ?bfmeAnchorGdiplusBitmapVtable absent-from-retail
Bitmap *bfmeAnchorGdiplusBitmapVtable(const WCHAR *filename, BOOL useEmbeddedColorManagement)
{
    return new Bitmap(filename, useEmbeddedColorManagement);
}

Status Bitmap::LockBits(const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData)
{
    return SetStatus(DllExports::GdipBitmapLockBits(
        (GpBitmap *)nativeImage, rect, flags, format, lockedBitmapData));
}

Status Bitmap::UnlockBits(BitmapData *lockedBitmapData)
{
    return SetStatus(DllExports::GdipBitmapUnlockBits((GpBitmap *)nativeImage, lockedBitmapData));
}

}

#include <poppack.h>
