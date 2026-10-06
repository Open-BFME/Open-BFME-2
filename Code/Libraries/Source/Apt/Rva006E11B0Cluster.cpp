// cl: /MD
// ?rva006E11B0@AptCIH@@QAEXXZ, retail 0x006E11B0, 169 bytes.
//
// GC mark pass over one AptCIH node, no SEH frame (leaf-shaped apart from the
// indirect calls). Evidence: same /O2 AptCIH layout as the neighbours in
// AptCIHLevel006E0B80.cpp (m_parent/+0x48, m_4C/+0x4C, vptr at 0), the
// AptValue setGCMark 0x006DBC50 and shr-and getter 0x006DBB40, the native-hash
// mark 0x0070B220, the display-list item mark 0x006F6D30, and the two Apt
// asserts: "isSpriteInstBase()" in AptCIH.h line 0x7D (lower-case path) and
// "pDisp" in AptCIH.cpp line 0x1D4. The first accessor 0x006E04A0 is the rowed
// BfmeAptValue006DCD20 type-19 display accessor. The predicate 0x006CFCD0 is
// called twice because the assert re-evaluates it; both call sites are the
// same pin.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

class BfmeAptValue006DCD20
{
public:
    void *rva006E04A0() const;
};

class Rva006DBB40ShrAndField
{
public:
    bool get() const;
};

class AptValue
{
public:
    void setGCMark(bool mark);
};

class Rva006DBC30
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
};

class AptNativeHash
{
public:
    void rva0070B220(void *value);
};

class Rva006F6D30
{
public:
    void rva006F6D30(void *value);
};

class AptCIH
{
public:
    virtual void vtableSlot0();
    bool rva006CFCD0() const;
    void rva006E11B0();

private:
    unsigned char _pad[0x40];
    void *m_44;
    void *m_48;
    void *m_4C;
    unsigned char _pad3[8];
    int m_code;
};

void AptCIH::rva006E11B0()
{
    void *display = ((const BfmeAptValue006DCD20 *)this)->rva006E04A0();
    if (m_48 != 0) {
        if (!((Rva006DBB40ShrAndField *)m_48)->get()) {
            ((AptValue *)m_48)->setGCMark(true);
            ((Rva006DBC30 *)m_48)->s13();
        }
    }
    if (display != 0)
        ((AptNativeHash *)display)->rva0070B220(this);
    if (rva006CFCD0()) {
        if (!rva006CFCD0()) {
            g_bfmeAptAssertAtE17734("isSpriteInstBase()",
                "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (m_4C != 0) {
            void *pDisp = *(void **)((char *)m_4C + 0x24);
            if (pDisp == 0) {
                g_bfmeAptAssertAtE17734("pDisp",
                    "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x1D4);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
            ((Rva006F6D30 *)pDisp)->rva006F6D30(this);
        }
    }
}
