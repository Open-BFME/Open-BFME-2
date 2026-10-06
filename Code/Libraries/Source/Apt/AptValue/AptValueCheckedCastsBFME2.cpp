// cl: /DNDEBUG /MD
// 14 Apt checked casts returning this after asserting isX().
// Retail 0x006DCF60/57B isCIH(bUndefOK) line 840,
// Retail 0x006DD020/50B isKey line 917, 0x006DD060/50B isMath line 995,
// 0x006DD0A0/50B isScriptColour line 1022, 0x006DD0E0/50B isObject line 1048,
// 0x006DD120/50B isPrototype line 1073, 0x006DD160/50B isDate line 1098,
// 0x006DD1A0/50B isTextFormat line 1123, 0x006DD1E0/50B isMovieClip line 1148,
// 0x006DD220/50B isXmlNode line 1173, 0x006DD260/50B isXml line 1198,
// 0x006DD2A0/50B isXmlAttributes line 1223, 0x006DD2E0/50B isLoadVars line 1249,
// 0x006DD320/50B isStage line 1277. Each calls its rowed predicate in
// AptValueTypePredicatesBFME2.cpp or AptValueXmlPredicatesBFME2.cpp,
// asserts "<isX()>" with AptValue.inl path at the retail line,
// then checks g_bfmeAptBreakOnAssertAtDDC01C.
// __asm int 3 is a proven blocker: the __debugbreak() intrinsic makes /O2
// hoist "mov eax,esi" above the break test and duplicate the return (54B);
// the asm barrier keeps the single shared return and the retail
// mov-eax-then-test shape (50B exact). Names are honest address names;
// original method names unknown.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
public:
    int isBoolean() const;
    int isKey() const;
    int isMath() const;
    int isScriptColour() const;
    int isObject() const;
    int isPrototype() const;
    int isDate() const;
    int isTextFormat() const;
    int isMovieClip() const;
    int isXmlNode() const;
    int isXml() const;
    int isXmlAttributes() const;
    int isLoadVars() const;
    int isStage() const;
    int isArray() const;
    int isSound() const;
    int isNativeFunction() const;
    int isScriptFunction() const;
    int isCIH(bool bUndefOK) const;
    BfmeAptValue006DCD20 *rva006DCEA0();
    BfmeAptValue006DCD20 *rva006DCEE0();
    BfmeAptValue006DCD20 *rva006DCF20();
    BfmeAptValue006DCD20 *rva006DCFA0();
    BfmeAptValue006DCD20 *rva006DCFE0();
    BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK);
    BfmeAptValue006DCD20 *rva006DD020();
    BfmeAptValue006DCD20 *rva006DD060();
    BfmeAptValue006DCD20 *rva006DD0A0();
    BfmeAptValue006DCD20 *rva006DD0E0();
    BfmeAptValue006DCD20 *rva006DD120();
    BfmeAptValue006DCD20 *rva006DD160();
    BfmeAptValue006DCD20 *rva006DD1A0();
    BfmeAptValue006DCD20 *rva006DD1E0();
    BfmeAptValue006DCD20 *rva006DD220();
    BfmeAptValue006DCD20 *rva006DD260();
    BfmeAptValue006DCD20 *rva006DD2A0();
    BfmeAptValue006DCD20 *rva006DD2E0();
    BfmeAptValue006DCD20 *rva006DD320();
};
// ?rva006DD020@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD020 50B. Checked cast for isKey type 24.
// Evidence: calls rowed ?isKey@BfmeAptValue006DCD20@@QBEHXZ; asserts "isKey()" at AptValue.inl:917.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD020()
{
    if (!static_cast<unsigned char>(isKey())) {
        g_bfmeAptAssertAtE17734("isKey()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x395);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD060@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD060 50B. Checked cast for isMath type 23.
// Evidence: calls rowed ?isMath@BfmeAptValue006DCD20@@QBEHXZ; asserts "isMath()" at AptValue.inl:995.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD060()
{
    if (!static_cast<unsigned char>(isMath())) {
        g_bfmeAptAssertAtE17734("isMath()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x3E3);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD0A0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD0A0 50B. Checked cast for isScriptColour type 26.
// Evidence: calls rowed ?isScriptColour@BfmeAptValue006DCD20@@QBEHXZ; asserts "isScriptColour()" at AptValue.inl:1022; callers at 0x006F2655/0x006F2705.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD0A0()
{
    if (!static_cast<unsigned char>(isScriptColour())) {
        g_bfmeAptAssertAtE17734("isScriptColour()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x3FE);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD0E0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD0E0 50B. Checked cast for isObject type 27.
// Evidence: calls rowed ?isObject@BfmeAptValue006DCD20@@QBEHXZ; asserts "isObject()" at AptValue.inl:1048; callers at 0x006D9F97.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD0E0()
{
    if (!static_cast<unsigned char>(isObject())) {
        g_bfmeAptAssertAtE17734("isObject()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x418);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD120@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD120 50B. Checked cast for isPrototype type 28.
// Evidence: calls rowed ?isPrototype@BfmeAptValue006DCD20@@QBEHXZ; asserts "isPrototype()" at AptValue.inl:1073; callers at 0x006DFC67.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD120()
{
    if (!static_cast<unsigned char>(isPrototype())) {
        g_bfmeAptAssertAtE17734("isPrototype()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x431);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD160@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD160 50B. Checked cast for isDate type 29.
// Evidence: calls rowed ?isDate@BfmeAptValue006DCD20@@QBEHXZ; asserts "isDate()" at AptValue.inl:1098; many callers from 0x006DDA02.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD160()
{
    if (!static_cast<unsigned char>(isDate())) {
        g_bfmeAptAssertAtE17734("isDate()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x44A);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD1A0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD1A0 50B. Checked cast for isTextFormat type 36.
// Evidence: calls rowed ?isTextFormat@BfmeAptValue006DCD20@@QBEHXZ; asserts "isTextFormat()" at AptValue.inl:1123; caller at 0x006EF5D5.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD1A0()
{
    if (!static_cast<unsigned char>(isTextFormat())) {
        g_bfmeAptAssertAtE17734("isTextFormat()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x463);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD1E0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD1E0 50B. Checked cast for isMovieClip type 30.
// Evidence: calls rowed ?isMovieClip@BfmeAptValue006DCD20@@QBEHXZ; asserts "isMovieClip()" at AptValue.inl:1148.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD1E0()
{
    if (!static_cast<unsigned char>(isMovieClip())) {
        g_bfmeAptAssertAtE17734("isMovieClip()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x47C);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD320@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD320 50B. Checked cast for isStage type 39.
// Evidence: calls rowed ?isStage@BfmeAptValue006DCD20@@QBEHXZ; asserts "isStage()" at AptValue.inl:1277.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD320()
{
    if (!static_cast<unsigned char>(isStage())) {
        g_bfmeAptAssertAtE17734("isStage()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x4FD);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD220@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD220 50B. Checked cast for isXmlNode type 32.
// Evidence: calls rowed ?isXmlNode@BfmeAptValue006DCD20@@QBEHXZ; asserts "isXmlNode()" at AptValue.inl:1173.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD220()
{
    if (!static_cast<unsigned char>(isXmlNode())) {
        g_bfmeAptAssertAtE17734("isXmlNode()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x495);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD260@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD260 50B. Checked cast for isXml type 33.
// Evidence: calls rowed ?isXml@BfmeAptValue006DCD20@@QBEHXZ; asserts "isXml()" at AptValue.inl:1198.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD260()
{
    if (!static_cast<unsigned char>(isXml())) {
        g_bfmeAptAssertAtE17734("isXml()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x4AE);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD2A0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD2A0 50B. Checked cast for isXmlAttributes type 34.
// Evidence: calls rowed ?isXmlAttributes@BfmeAptValue006DCD20@@QBEHXZ; asserts "isXmlAttributes()" at AptValue.inl:1223.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD2A0()
{
    if (!static_cast<unsigned char>(isXmlAttributes())) {
        g_bfmeAptAssertAtE17734("isXmlAttributes()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x4C7);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DD2E0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DD2E0 50B. Checked cast for isLoadVars type 35.
// Evidence: calls rowed ?isLoadVars@BfmeAptValue006DCD20@@QBEHXZ; asserts "isLoadVars()" at AptValue.inl:1249.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DD2E0()
{
    if (!static_cast<unsigned char>(isLoadVars())) {
        g_bfmeAptAssertAtE17734("isLoadVars()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x4E1);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCF60(bool bUndefOK)
{
    if (!static_cast<unsigned char>(isCIH(bUndefOK))) {
        g_bfmeAptAssertAtE17734("isCIH(bUndefOK)", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x348);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DCEA0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCEA0 50B. Checked cast for isBoolean type 5.
// Evidence: calls rowed ?isBoolean@BfmeAptValue006DCD20@@QBEHXZ; asserts "isBoolean()" at AptValue.inl:766.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCEA0()
{
    if (!static_cast<unsigned char>(isBoolean())) {
        g_bfmeAptAssertAtE17734("isBoolean()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x2FE);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DCEE0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCEE0 50B. Checked cast for isScriptFunction types 43-45.
// Evidence: calls rowed ?isScriptFunction@BfmeAptValue006DCD20@@QBEHXZ; asserts "isScriptFunction()" at AptValue.inl:791.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCEE0()
{
    if (!static_cast<unsigned char>(isScriptFunction())) {
        g_bfmeAptAssertAtE17734("isScriptFunction()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x317);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DCF20@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCF20 50B. Checked cast for isNativeFunction type 9.
// Evidence: calls rowed ?isNativeFunction@BfmeAptValue006DCD20@@QBEHXZ; asserts "isNativeFunction()" at AptValue.inl:816.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCF20()
{
    if (!static_cast<unsigned char>(isNativeFunction())) {
        g_bfmeAptAssertAtE17734("isNativeFunction()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x330);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DCFA0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCFA0 50B. Checked cast for isArray type 22.
// Evidence: calls rowed ?isArray@BfmeAptValue006DCD20@@QBEHXZ; asserts "isArray()" at AptValue.inl:865.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCFA0()
{
    if (!static_cast<unsigned char>(isArray())) {
        g_bfmeAptAssertAtE17734("isArray()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x361);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
// ?rva006DCFE0@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCFE0 50B. Checked cast for isSound type 21.
// Evidence: calls rowed ?isSound@BfmeAptValue006DCD20@@QBEHXZ; asserts "isSound()" at AptValue.inl:891.
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006DCFE0()
{
    if (!static_cast<unsigned char>(isSound())) {
        g_bfmeAptAssertAtE17734("isSound()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x37B);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}
