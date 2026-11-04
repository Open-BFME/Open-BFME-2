// cl: /MD
// ?rva006DBFA0@BfmeAptValue006DCD20@@QBEHXZ @0x006DBFA0 110B evidence same TU as isXmlNode family plus AptValue.inl lines 1407/1408 plus type 3 via sub 0x6000000
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#include "../BfmeAptValue006DCD20.h"
int BfmeAptValue006DCD20::rva006DBFA0() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x57f);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x580);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return (static_cast<int>(field04) >> 25) == 3;
}
