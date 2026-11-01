// cl: /MD
// BFME2 Apt type initializer at RVA 0x006DBBC0, 106 bytes.
// Directly called by AptValueConstructorBFME2.cpp; retail assertion strings
// identify AptValue/AptValue.inl lines 326-327 and the AptVFT enum bounds.
// This BFME2 layout places the type in flag bits 25-31 (BFME1 differs).
// The assertion callback and break switch are data pointers, not imported APIs.
// __debugbreak is the compiler intrinsic for the retail assertion breakpoint.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "../BfmeAptValue006DCD20.h"
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void BfmeAptValue006DCD20::setTypeAt006DBBC0(int type)
{
    if (!(type > 0)) {
        g_bfmeAptAssertAtE17734("n > AptVFT_xxx", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 326);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (!(type < 47)) {
        g_bfmeAptAssertAtE17734("n < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 327);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    field04 = (field04 & 0x01ffffffu) | (static_cast<unsigned int>(type) << 25);
}

// ?bfmeAnchorAptValueSetType absent-from-retail
void bfmeAnchorAptValueSetType(BfmeAptValue006DCD20 *p, int type)
{
	p->setTypeAt006DBBC0(type);
}

