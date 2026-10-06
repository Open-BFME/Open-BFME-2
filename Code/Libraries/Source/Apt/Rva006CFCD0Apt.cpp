// ?isSpriteInstBase@Rva006CFCD0@@QBEHXZ
// partial score=0.95 date=2026-09-27
// cl: /MD
// ?isSpriteInstBase@Rva006CFCD0@@QBEHXZ @0x006CFCD0 91B. Predicate for AptVFT
// types 13 (0x1A000000) and 18 (0x24000000): returns true when defined and
// type is either. Evidence: callers 0x006CFF40/48B and 0x006E1F90/115B call
// this address then assert "isSpriteInstBase()" at AptCIH.h:125 (0x7D);
// this body asserts "this" at AptCIH.h:226 (0xE2) then calls rowed
// ?isUndefined@BfmeAptValue006DCD20@@QBE_NXZ and twice calls rowed
// ?get@Rva006DBB30SarDwordField@@QBEHXZ comparing to 0xD and 0x12.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
public:
    bool isUndefined() const;
};
class Rva006DBB30SarDwordField {
public:
    int get() const;
};
class Rva006CFCD0 {
    virtual void vtableSlot0();
    unsigned int m_flags;
public:
    bool isSpriteInstBase() const;
};
bool Rva006CFCD0::isSpriteInstBase() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xE2);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (reinterpret_cast<const BfmeAptValue006DCD20 *>(this)->isUndefined())
        return false;
    return reinterpret_cast<const Rva006DBB30SarDwordField *>(this)->get() == 0xD
        || reinterpret_cast<const Rva006DBB30SarDwordField *>(this)->get() == 0x12;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?rva006CFCD0@AptCIH@@QBE_NXZ=?isSpriteInstBase@Rva006CFCD0@@QBE_NXZ")
