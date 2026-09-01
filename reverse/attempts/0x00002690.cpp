// ?CreateEx@CImage@ATL@@QAEHHHHKPBKK@Z
// partial score=0.96 date=2026-09-01
// ?CreateEx@CImage@ATL@@QAEHHHHKPBKK@Z
// partial score=0.96 date=2026-09-01
// ATL 7.1 CImage::CreateEx at 0x00002690 (205 bytes). Identity is certain:
// the body allocates 0x428 = sizeof(BITMAPINFOHEADER) + 256 RGBQUADs through
// the CAtlSafeAllocBufferManager::Allocate landed at 0x000021E3, fills a
// BITMAPINFOHEADER field by field (biSize 0x28, biPlanes 1, biBitCount from
// nBPP, biCompression from eCompression), zeroes the 0x400-byte palette when
// nBPP <= 8 or copies three DWORDs of bitfields when eCompression is
// BI_BITFIELDS, calls CreateDIBSection, inlines Attach, sets
// m_bHasAlphaChannel from the flag bit, and destroys the buffer manager at
// 0x00001D80 on the way out. Every one of those matches byte for byte, and the
// source below is the shipped atlimage.h body.
//
// It compiles to 203 bytes, not 205, and the whole gap is one block-placement
// choice at +0x8. Retail pushes ebx in the prologue and lays the alloc-failure
// path out inline:
//     jne over ; xor esi,esi ; jmp epilogue        (9 bytes)
// MSVC 7.1 defers the ebx push into the branch and jumps straight out:
//     je epilogue                                   (6 bytes)
// Everything downstream is identical, including ebx holding 0x28 and then
// nHeight. Refuted as the lever: braces around the early return, NULL/FALSE
// spellings, parenthesised returns, and /O2, /Ox, /O1 /Oy-, /O1 /Gy (which
// give 263, 263, 261 and 263 bytes - /O1 is certainly the unit's setting).
//
// Next lever: something that makes ebx live before the null test, which is the
// only thing that would stop MSVC deferring its push.
//
// Landing this needs atlimage.cpp to gain BITMAPINFO, RGBQUAD's real fields,
// the CreateDIBSection import, memset/memcpy, a declaration of
// CAtlSafeAllocBufferManager, and `inline` on CImage::Attach so it folds in.


