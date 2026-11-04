// cl: /MD
// Reuse PC AptValueSetTypeBFME2 assertion convention. PC own assertions and
// constructor identify type7bit, defined-bit4, and 47-type bound independently.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "../BfmeAptValue006DCD20.h"
bool BfmeAptValue006DCD20::isUndefined() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1433);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1434);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return !static_cast<unsigned char>(((field04 >> 4) & 1u));
}
