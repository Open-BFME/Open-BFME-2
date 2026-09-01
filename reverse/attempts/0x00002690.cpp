// ?CreateEx@CImage@ATL@@QAEHHHHKPBKK@Z
// partial score=0.98 date=2026-09-01
// ATL 7.1 CImage::CreateEx at 0x00002690 (205 bytes). Identity is certain: the
// body allocates 0x428 = sizeof(BITMAPINFOHEADER) + 256 RGBQUADs through the
// CAtlSafeAllocBufferManager::Allocate at 0x000021E3, fills a BITMAPINFOHEADER
// field by field, zeroes the 0x400-byte palette when nBPP <= 8 or copies three
// DWORDs of bitfields when eCompression is BI_BITFIELDS, calls
// CreateDIBSection, inlines Attach into UpdateBitmapInfo at 0x00001642, sets
// m_bHasAlphaChannel from the flag bit and destroys the buffer manager at
// 0x00001D80. All of that matches byte for byte.
//
// It compiles to 203 bytes, not 205, and the whole gap is one block-placement
// choice at +0x8. Retail pushes ebx in the prologue and lays the alloc-failure
// path out inline:
//     jne over ; xor esi,esi ; jmp epilogue        (9 bytes)
// MSVC 7.1 defers the ebx push into the branch and jumps straight out:
//     je epilogue                                   (6 bytes)
//
// Refuted: braces round the early return, NULL/FALSE spellings, parenthesised
// returns, and -O1 -G7 with each of -Oy-, -Gs, -GX, -Op (all 203) and -O2 -G7
// (265). -O1 -G7 -Ob0 does reach 205 bytes but by the wrong route: it also
// stops the buffer manager's constructor inlining, which retail folds into the
// `and [ebp-4],0` in its prologue.
//
// NOTE the unit is now -O1 -G7, not -O1: /G7 is what gave
// CreateFromGdiplusBitmap its `and al,0FCh`. An earlier note here claimed /O1
// was certain from a flag sweep - that sweep was invalid, Git Bash had rewritten
// the leading /O1 into a path before cl ever saw it.
//
// Next lever: something that makes ebx live before the null test, which is the
// only thing that would stop MSVC deferring its push.
//
// atlimage.cpp already carries everything else this needs except BITMAPINFO,
// the CreateDIBSection import, memset and `inline` on CImage::Attach.

BOOL CImage::CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
    const DWORD *pdwBitfields, DWORD dwFlags) throw()
{
    _ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<CCRTAllocator> _AtlSafeAllocaManager;
    LPBITMAPINFO pbmi;
    HBITMAP hBitmap;

    // sizeof(BITMAPINFOHEADER) + 256 RGBQUADs is 1064, past the 1024-byte
    // threshold, so the _alloca arm of _ATL_SAFE_ALLOCA folds away at compile
    // time and only the heap arm is left.
    pbmi = (LPBITMAPINFO)_AtlSafeAllocaManager.Allocate(
        sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
    if (pbmi == 0)
        return 0;

    memset(&pbmi->bmiHeader, 0, sizeof(pbmi->bmiHeader));
    pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
    pbmi->bmiHeader.biWidth = nWidth;
    pbmi->bmiHeader.biHeight = nHeight;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = USHORT(nBPP);
    pbmi->bmiHeader.biCompression = eCompression;
    if (nBPP <= 8)
    {
        memset(pbmi->bmiColors, 0, 256 * sizeof(RGBQUAD));
    }
    else
    {
        if (eCompression == 3)
        {
            memcpy(pbmi->bmiColors, pdwBitfields, 3 * sizeof(DWORD));
        }
    }

    hBitmap = CreateDIBSection(0, pbmi, 0, &m_pBits, 0, 0);
    if (hBitmap == 0)
    {
        return 0;
    }

    Attach(hBitmap, (nHeight < 0) ? DIBOR_TOPDOWN : DIBOR_BOTTOMUP);

    if (dwFlags & createAlphaChannel)
    {
        m_bHasAlphaChannel = true;
    }

    return 1;
}
