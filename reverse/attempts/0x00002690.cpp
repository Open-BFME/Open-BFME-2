// ?CreateEx@CImage@ATL@@QAEHHHHKPBKK@Z
// partial score=0.99 date=2026-09-02
// ATL 7.1 CImage::CreateEx at 0x00002690 (205 bytes). Identity is certain: the
// body allocates 0x428 = sizeof(BITMAPINFOHEADER) + 256 RGBQUADs through the
// CAtlSafeAllocBufferManager::Allocate at 0x000021E3, fills a BITMAPINFOHEADER
// field by field, zeroes the 0x400-byte palette when nBPP <= 8 or copies three
// DWORDs of bitfields when eCompression is BI_BITFIELDS, calls
// CreateDIBSection, inlines Attach into UpdateBitmapInfo at 0x00001642, sets
// m_bHasAlphaChannel from the flag bit and destroys the buffer manager at
// 0x00001D80.
//
// 203 bytes against 205, and every byte outside the two blocks below is
// identical - prologue, the whole BITMAPINFOHEADER fill, both memsets, the
// memcpy, the CreateDIBSection call and the Attach/alpha tail all match.
//
// SOLVED since the last bank: the prologue.  MSVC sank `push ebx` into the
// branch as long as the first failure was an early `return 0` - in any of its
// spellings, including if/else and a goto.  Writing the failure as a jump
// FORWARD over a return-0 block (the goto shape below) puts the push back in
// the prologue where retail has it, and with it the 53 56 57 the earlier
// attempts were missing.
//
// STILL OPEN: where the shared return-0 block lands.  Retail lays it inline
// as the fallthrough of the first test and jumps BACK to it from the
// CreateDIBSection failure:
//     test esi,esi ; jne body ; xor esi,esi ; jmp epilogue     (9 bytes)
//     ... test eax,eax ; je -0x79
// MSVC 7.1 keeps one copy too, but sinks it past the success tail:
//     test esi,esi ; je +0x94                                  (6 bytes)
//     ... xor esi,esi ; inc esi ; jmp +2 ; xor esi,esi         (2 bytes back)
// Retail's placement is also what gives its epilogue the `lea esp,[ebp-0x10]`
// (a jumped-to epilogue restores esp) where ours falls through and pops.
//
// Refuted for the placement: early return in every spelling, if/else, the
// structured `if (pbmi != 0) { ... } return 0;` form, an explicit goto to a
// label placed before the body, the real _ATL_SAFE_ALLOCA macro (its _alloca
// arm folds at compile time and never reaches the back end), and
// #pragma optimize with t, s, a, w, gt, gs, g-off and y-off around the
// function alone.  A whole-file flag change is not available: the other 18
// bodies in atlimage.cpp match on -O1 -G7.
//
// Next lever: something that makes cross-jumping keep the FIRST copy of the
// return-0 block rather than sinking it - the two failure paths differing in
// some way the merge still tolerates, or a third reference to the block.
//
// atlimage.cpp needs four additions for this body, all of them already
// written and reverted with it: a BITMAPINFO/LPBITMAPINFO struct after
// RGBQUAD, the CreateDIBSection and memset declarations beside memcpy, and
// `inline` on CImage::Attach so it folds into the call to UpdateBitmapInfo.

BOOL CImage::CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
    const DWORD *pdwBitfields, DWORD dwFlags) throw()
{
    _ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<CCRTAllocator> _AtlSafeAllocaManager;
    LPBITMAPINFO pbmi;
    HBITMAP hBitmap;

    pbmi = (LPBITMAPINFO)_ATL_SAFE_ALLOCA(
        sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256,
        _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
    if (pbmi != 0)
        goto gotBuffer;
fail:
    return 0;

gotBuffer:
    memset(&pbmi->bmiHeader, 0, sizeof(pbmi->bmiHeader));
    pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
    pbmi->bmiHeader.biWidth = nWidth;
    pbmi->bmiHeader.biHeight = nHeight;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = WORD(nBPP);
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
        goto fail;

    Attach(hBitmap, (nHeight < 0) ? DIBOR_TOPDOWN : DIBOR_BOTTOMUP);

    if (dwFlags & createAlphaChannel)
    {
        m_bHasAlphaChannel = true;
    }

    return 1;
}
