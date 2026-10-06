// cl: /MD
// PC predicates named by the corresponding checked-cast assertion strings.
// Signed seven-bit type occupies bits25..31; this is PC evidence, not PDB layout.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
    struct { unsigned int unknown : 25; int type : 7; } flags;
    unsigned char _padTo4C[0x44];
    struct Rva006E04A0Target { unsigned char _pad[0x10]; void *field10; } *m_p;
public:
    bool isUndefined() const;
    int isLookup() const;
    int isInteger() const;
    int isRegister() const;
    int isFloat() const;
    int isString() const;
    int isBoolean() const;
    int isNativeFunction() const;
    int isScriptFunction() const;
    int isArray() const;
    int isSound() const;
    int isDate() const;
    int isKey() const;
    int isMath() const;
    int isScriptColour() const;
    int isCIH(bool bUndefOK) const;
    int isObject() const;
    int isPrototype() const;
    int isTextFormat() const;
    int isMovieClip() const;
    int isStage() const;
    int rva006DC300() const;
    int rva006DC350() const;
    int rva006DC490() const;
    int rva006DCC60(bool bUndefOK) const;
    int rva006E01A0(bool bUndefOK) const;
    int isCharacterInst() const;
    int rva006E02B0() const;
    int rva006E0260() const;
    int rva006E0300() const;
    int rva006E0350() const;
    int rva006E03A0() const;
    int rva006CBEE0(bool bUndefOK) const;
    void *rva006E04A0() const;
    void *rva006E0F40() const;
};

class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
// Corresponding checked casts at 6DCD50/90/D0 and 6DCE10/50 assert these
// exact predicate names. Type numbers are independently decoded from PC.
// Godfather final PDB corroborates names but is structurally incompatible:
// its AptValue is4B and enum ends36; PC stores flags+4 and permits types<47.
// In particular PC isString accepts1 or42; do not copy the other enum wholesale.

int BfmeAptValue006DCD20::isLookup() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1459);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 8 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isInteger() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1535);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 7 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isRegister() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1560);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 4 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isFloat() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1585);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 6 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isString() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1484);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if ((flags.type == 1 || flags.type == 42) && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isBoolean() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1510);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 5 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isNativeFunction() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1610);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 9 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isScriptFunction() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1635);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type >= 43 && flags.type <= 45 && !isUndefined()) return 1;
    return 0;
}

// ?isArray@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC3A0, 78 bytes.
// Predicate for type 22 (0x2C000000), "this" assert at AptValue.inl:1711.
// Evidence: caller 0x006DCFA0 asserts "isArray()" after calling it; 12 callers
// in FUN_00ad9780/00ad9b50/00ad9c70/00ad9ce0/00ad9f00/00ada0c0; same /O2 shape
// as siblings in this TU.
int BfmeAptValue006DCD20::isArray() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1711);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 22 && !isUndefined()) return 1;
    return 0;
}

// ?isSound@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC3F0, 78 bytes.
// Predicate for type 21 (0x2A000000), "this" assert at AptValue.inl:1737.
// Evidence: caller 0x006DCFE0 asserts "isSound()" after calling it; callers at
// 0x006DCFE3/0x006F359D/0x006F3677/0x006F36B4; same /O2 shape as siblings.
int BfmeAptValue006DCD20::isSound() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1737);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 21 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isDate() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1944);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 29 && !isUndefined()) return 1;
    return 0;
}

// ?isKey@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC440, 78 bytes.
// Predicate for type 24 (0x30000000), "this" assert at AptValue.inl:1763.
// Evidence: caller 0x006DD020 asserts "isKey()" after calling it; second caller
// 0x006EACE2; same /O2 shape as isDate/isBoolean siblings in this TU.
int BfmeAptValue006DCD20::isKey() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1763);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 24 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::rva006DC490() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1789);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 31 && !isUndefined()) return 1;
    return 0;
}

// ?isMath@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC4E0, 78 bytes.
// Predicate for type 23 (0x2E000000), "this" assert at AptValue.inl:1816.
// Evidence: caller 0x006DD060 asserts "isMath()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isMath() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1816);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 23 && !isUndefined()) return 1;
    return 0;
}

// ?isScriptColour@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC530, 78 bytes.
// Predicate for type 26 (0x34000000), "this" assert at AptValue.inl:1843.
// Evidence: caller 0x006DD0A0 asserts "isScriptColour()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isScriptColour() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1843);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 26 && !isUndefined()) return 1;
    return 0;
}

// ?isCIH@BfmeAptValue006DCD20@@QBEH_N@Z, retail 0x006DC580, 91 bytes.
// Predicate for types 12..19 with bUndefOK flag, "this" assert at AptValue.inl:1868.
// Evidence: wrapper at 0x006DCF60 asserts "isCIH(bUndefOK)" after calling it;
// callers at 0x006DFAF2/0x006DFB0B/0x006DFB47/0x006DFC05/0x006DFC9D/0x006DFD1F push 0;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isCIH(bool bUndefOK) const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1868);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type >= 12 && flags.type <= 19) {
        if (bUndefOK) return 1;
        if (!isUndefined()) return 1;
    }
    return 0;
}

// ?isObject@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC5E0, 78 bytes.
// Predicate for type 27 (0x36000000), "this" assert at AptValue.inl:1894.
// Evidence: caller 0x006DD0E0 asserts "isObject()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isObject() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1894);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 27 && !isUndefined()) return 1;
    return 0;
}

// ?isPrototype@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC630, 78 bytes.
// Predicate for type 28 (0x38000000), "this" assert at AptValue.inl:1919.
// Evidence: caller 0x006DD120 asserts "isPrototype()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isPrototype() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1919);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 28 && !isUndefined()) return 1;
    return 0;
}

// ?isTextFormat@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC6D0, 78 bytes.
// Predicate for type 36 (0x48000000), "this" assert at AptValue.inl:1969.
// Evidence: caller 0x006DD1A0 asserts "isTextFormat()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isTextFormat() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1969);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 36 && !isUndefined()) return 1;
    return 0;
}

// ?isMovieClip@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC720, 78 bytes.
// Predicate for type 30 (0x3C000000), "this" assert at AptValue.inl:1994.
// Evidence: caller 0x006DD1E0 asserts "isMovieClip()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isMovieClip() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1994);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 30 && !isUndefined()) return 1;
    return 0;
}

// ?isStage@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC770, 78 bytes.
// Predicate for type 39 (0x4E000000), "this" assert at AptValue.inl:2021.
// Evidence: caller 0x006DD320 asserts "isStage()" after calling it;
// same /O2 shape as siblings in this TU.
int BfmeAptValue006DCD20::isStage() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",2021);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 39 && !isUndefined()) return 1;
    return 0;
}
// ?rva006DC300@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC300, 78 bytes.
// Predicate for type 11 (0x16000000), "this" assert at AptValue.inl:1661.
// Evidence: same /O2 shape as siblings; callers at 0x00703BD1/0x00703DE9.
int BfmeAptValue006DCD20::rva006DC300() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",0x67D);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 11 && !isUndefined()) return 1;
    return 0;
}
// ?rva006DC350@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006DC350, 78 bytes.
// Predicate for type 20 (0x28000000), "this" assert at AptValue.inl:1686.
// Evidence: gap between 0x006DC300 (type 11) and 0x006DC3A0 isArray (type 22);
// same /O2 shape as siblings; no callers yet so honest-address name.
int BfmeAptValue006DCD20::rva006DC350() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1686);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 20 && !isUndefined()) return 1;
    return 0;
}
// ?rva006DCC60@BfmeAptValue006DCD20@@QBEH_N@Z, retail 0x006DCC60, 90 bytes.
// Predicate for type 14 (0x1C000000) with bUndefOK, "this" assert at AptCIH.h:181.
// Evidence: same /O2 shape as isCIH sibling; callers at 0x006DFD33/0x006E2545;
// path AptCIH.h measured from retail string at 0x008E8C60.
int BfmeAptValue006DCD20::rva006DCC60(bool bUndefOK) const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB5);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 14) {
        if (bUndefOK) return 1;
        if (!isUndefined()) return 1;
    }
    return 0;
}

// ?rva006E01A0@BfmeAptValue006DCD20@@QBEH_N@Z, retail 0x006E01A0, 87 bytes.
// Predicate for type 13 (0x1A000000) with bUndefOK, "this" assert at AptCIH.h:171 (0xAB)
// via the same file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0xd plus bUndefOK/isUndefined path;
// callers at 0x006EF22A/0x006EF290/0x006FF17E/0x00702A62; same /O2 shape as
// rva006DCC60 sibling in this TU.
int BfmeAptValue006DCD20::rva006E01A0(bool bUndefOK) const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xAB);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 13) {
        if (bUndefOK) return 1;
        if (!isUndefined()) return 1;
    }
    return 0;
}

// retail 0x006E0200, 87 bytes. Predicate for CIH range 12..19 without
// bUndefOK, "this" assert at AptCIH.h:176 (0xB0) via file string at
// 0x008E8C60. Evidence: caller 0x006E1170 asserts "isCharacterInst()" at
// AptCIH.h:165 after calling it then returns +0x4C; type range via rowed
// get@Rva006DBB30SarDwordField plus !isUndefined via rowed isUndefined.
int BfmeAptValue006DCD20::isCharacterInst() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB0);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() < 12)
        goto ret0;
    if (((const Rva006DBB30SarDwordField *)this)->get() > 19)
        goto ret0;
    if (!isUndefined())
        return 1;
ret0:
    return 0;
}

// ?rva006E02B0@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006E02B0, 75 bytes.
// Predicate for type 15, "this" assert at AptCIH.h:196 (0xC4) via the same
// file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0xf plus !isUndefined via rowed
// isUndefined; 15 callers; same /O2 shape as isCharacterInst sibling.
int BfmeAptValue006DCD20::rva006E02B0() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xC4);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 15 && !isUndefined())
        return 1;
    return 0;
}

// ?rva006E0260@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006E0260, 75 bytes.
// Predicate for type 12, "this" assert at AptCIH.h:191 (0xBF) via the same
// file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0xc plus !isUndefined via rowed
// isUndefined; 4 callers; same /O2 shape as rva006E02B0 sibling.
int BfmeAptValue006DCD20::rva006E0260() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xBF);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 12 && !isUndefined())
        return 1;
    return 0;
}

// ?rva006E0300@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006E0300, 75 bytes.
// Predicate for type 16, "this" assert at AptCIH.h:201 (0xC9) via the same
// file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0x10 plus !isUndefined via rowed
// isUndefined; 2 callers; same /O2 shape as rva006E02B0 sibling.
int BfmeAptValue006DCD20::rva006E0300() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xC9);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 16 && !isUndefined())
        return 1;
    return 0;
}

// ?rva006E0350@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006E0350, 75 bytes.
// Predicate for type 17, "this" assert at AptCIH.h:206 (0xCE) via the same
// file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0x11 plus !isUndefined via rowed
// isUndefined; 4 callers; same /O2 shape as rva006E0300 sibling.
int BfmeAptValue006DCD20::rva006E0350() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xCE);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 17 && !isUndefined())
        return 1;
    return 0;
}

// ?rva006E03A0@BfmeAptValue006DCD20@@QBEHXZ, retail 0x006E03A0, 75 bytes.
// Predicate for type 19, "this" assert at AptCIH.h:216 (0xD8) via the same
// file string at 0x008E8C60 as isCharacterInst. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0x13 plus !isUndefined via rowed
// isUndefined; 10 callers; same /O2 shape as rva006E0350 sibling.
int BfmeAptValue006DCD20::rva006E03A0() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xD8);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 19 && !isUndefined())
        return 1;
    return 0;
}

// ?rva006CBEE0@BfmeAptValue006DCD20@@QBEH_N@Z, retail 0x006CBEE0, 87 bytes.
// Predicate for type 18, "this" assert at AptCIH.h:211 (0xD3) via the same
// file string at 0x008E8C60 as siblings. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0x12 plus bUndefOK/isUndefined path;
// callers at 0x006E2831/0x006EF240/0x006FF194/0x00702A78; same /O2 shape as
// rva006E01A0 sibling in this TU.
int BfmeAptValue006DCD20::rva006CBEE0(bool bUndefOK) const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xD3);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 18) {
        if (bUndefOK) return 1;
        if (!isUndefined()) return 1;
    }
    return 0;
}

// ?rva006E04A0@BfmeAptValue006DCD20@@QBEPAXXZ, retail 0x006E04A0, 88 bytes.
// Type-19-guarded display-object accessor, "this" assert at AptCIH.h:216 (0xD8)
// via the same file string at 0x008E8C60 as siblings. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0x13 plus rowed isUndefined guard, then
// +0x4c pointer validated against null/0xbaadf00d returning its +0x10 field;
// callers at 0x006DFD46/0x006E0510/0x006E11B4/0x006FA276/0x006FEF38 use the
// result as an object pointer; same /O2 shape as siblings in this TU.
void *BfmeAptValue006DCD20::rva006E04A0() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xD8);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 19 && !isUndefined())
        return 0;
    struct Rva006E04A0Target *p = m_p;
    if (!p || p == (struct Rva006E04A0Target *)0xbaadf00d)
        return 0;
    return p->field10;
}

// ?rva006E0F40@BfmeAptValue006DCD20@@QBEPAXXZ, retail 0x006E0F40, 103 bytes.
// Type-15 checked cast to the +0x4c display object, "this" assert at
// AptCIH.h:196 (0xC4) plus "isTextInst()" assert at AptCIH.h:130 (0x82), both
// via the file string at 0x008E8C60. Evidence: rowed
// get@Rva006DBB30SarDwordField equals 0xf plus rowed isUndefined fast path
// skipping the second assert; 30 callers use the result as an object;
// same /O2 shape as rva006E04A0 sibling in this TU. Barrier keeps the +0x4c
// load late (retail test-je-int3-mov, no hoist) like rva006E0FB0 neighbour;
// emits no bytes.
void *BfmeAptValue006DCD20::rva006E0F40() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xC4);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() != 15 || isUndefined()) {
        g_bfmeAptAssertAtE17734("isTextInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x82);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    _ReadWriteBarrier();
    return m_p;
}
