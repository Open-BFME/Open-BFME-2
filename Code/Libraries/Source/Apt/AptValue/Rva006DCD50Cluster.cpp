// cl: /O2 /DNDEBUG /MD
// Four Apt checked casts returning this after asserting isX(), extending the
// recipe proven byte-exact for the 14 siblings in AptValueCheckedCastsBFME2.cpp:
// __asm int 3 is the proven blocker for the /O2 hoist that otherwise makes
// "mov eax,esi" jump above the break test and duplicate the return (54B).
// Retail 0x006DCD50/50B checkedLookup AptValue.inl:632 (assert "isLookup()"),
// 0x006DCD90/50B checkedInteger line 657, 0x006DCDD0/50B checkedRegister
// line 682, 0x006DCE10/50B checkedFloat line 707. Each calls its rowed
// predicate in AptValueTypePredicatesBFME2.cpp, asserts "<isX()>" with the
// AptValue.inl path at the retail line, then checks
// g_bfmeAptBreakOnAssertAtDDC01C. Names come from the retail assertion text.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
public:
    int isLookup() const;
    int isInteger() const;
    int isRegister() const;
    int isFloat() const;
    BfmeAptValue006DCD20 *checkedLookup();
    BfmeAptValue006DCD20 *checkedInteger();
    BfmeAptValue006DCD20 *checkedRegister();
    BfmeAptValue006DCD20 *checkedFloat();
};
// ?checkedLookup@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCD50 50B. Checked cast for isLookup.
// Evidence: calls rowed ?isLookup@BfmeAptValue006DCD20@@QBEHXZ; asserts "isLookup()" at AptValue.inl:632.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::checkedLookup()
{
    if (!static_cast<unsigned char>(isLookup())) {
        g_bfmeAptAssertAtE17734("isLookup()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x278);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?checkedInteger@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCD90 50B. Checked cast for isInteger.
// Evidence: calls rowed ?isInteger@BfmeAptValue006DCD20@@QBEHXZ; asserts "isInteger()" at AptValue.inl:657.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::checkedInteger()
{
    if (!static_cast<unsigned char>(isInteger())) {
        g_bfmeAptAssertAtE17734("isInteger()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x291);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?checkedRegister@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCDD0 50B. Checked cast for isRegister.
// Evidence: calls rowed ?isRegister@BfmeAptValue006DCD20@@QBEHXZ; asserts "isRegister()" at AptValue.inl:682.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::checkedRegister()
{
    if (!static_cast<unsigned char>(isRegister())) {
        g_bfmeAptAssertAtE17734("isRegister()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x2AA);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?checkedFloat@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCE10 50B. Checked cast for isFloat.
// Evidence: calls rowed ?isFloat@BfmeAptValue006DCD20@@QBEHXZ; asserts "isFloat()" at AptValue.inl:707.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::checkedFloat()
{
    if (!static_cast<unsigned char>(isFloat())) {
        g_bfmeAptAssertAtE17734("isFloat()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x2C3);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}