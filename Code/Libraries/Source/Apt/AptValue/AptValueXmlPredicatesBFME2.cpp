// cl: /MD
// 4 Apt Xml predicates for types 32..35.
// Retail 0x006DBDE0/110B isXmlNode type 32 lines 1301/1302,
// 0x006DBE50/110B isXml type 33 lines 1327/1328,
// 0x006DBEC0/110B isXmlAttributes type 34 lines 1353/1354,
// 0x006DBF30/110B isLoadVars type 35 lines 1380/1381.
// Each asserts "this" then "getVtblIndex() < AptVFT_NumVFTs" with AptValue.inl
// path, then returns ((static_cast<int>(field04) >> 25) == N) via sub/neg/sbb/inc.
// Named by corresponding checked-cast assertions at 0x006DD220/0x006DD260/
// 0x006DD2A0/0x006DD2E0 which call them. __debugbreak(); keeps retail
// mov-eax-then-test shape under /O2.
extern "C" void __cdecl __debugbreak(void);
#pragma intrinsic(__debugbreak)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#include "../BfmeAptValue006DCD20.h"
// ?isXmlNode@BfmeAptValue006DCD20@@QBEHXZ @0x006DBDE0 110B. Predicate for type 32.
// Evidence: caller 0x006DD220 asserts "isXmlNode()" after calling it.
int BfmeAptValue006DCD20::isXmlNode() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x515);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x516);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return (static_cast<int>(field04) >> 25) == 32;
}
// ?isXml@BfmeAptValue006DCD20@@QBEHXZ @0x006DBE50 110B. Predicate for type 33.
// Evidence: caller 0x006DD260 asserts "isXml()" after calling it.
int BfmeAptValue006DCD20::isXml() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x52F);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x530);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return (static_cast<int>(field04) >> 25) == 33;
}
// ?isXmlAttributes@BfmeAptValue006DCD20@@QBEHXZ @0x006DBEC0 110B. Predicate for type 34.
// Evidence: caller 0x006DD2A0 asserts "isXmlAttributes()" after calling it.
int BfmeAptValue006DCD20::isXmlAttributes() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x549);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x54A);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return (static_cast<int>(field04) >> 25) == 34;
}
// ?isLoadVars@BfmeAptValue006DCD20@@QBEHXZ @0x006DBF30 110B. Predicate for type 35.
// Evidence: caller 0x006DD2E0 asserts "isLoadVars()" after calling it.
int BfmeAptValue006DCD20::isLoadVars() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x564);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (!((static_cast<int>(field04) >> 25) < 47)) {
        g_bfmeAptAssertAtE17734("getVtblIndex() < AptVFT_NumVFTs", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x565);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return (static_cast<int>(field04) >> 25) == 35;
}
