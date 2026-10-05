// ??0Rva00709870Base@@QAE@HPAVAptValueBig@@PAVBfmeAptValue006DCD20@@_N@Z
// partial score=0.93 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc
// ?rva00709870@Rva00709870Base@@QAEXHPAVAptValue@@00@Z @0x00709870 397B
// Evidence: forwards to rowed ??0Rva006D6360@@QAE@HH@Z with (type 8); installs vtable VA 0x00CEE8C8;
// clears byte +0x1C and bits 8-9; stores third arg at +0x20; asserts spRegBlockBase line 0xF4 and
// nZombieCounter<65536 line 0x53 via g_bfmeAptAssertAtE17734; isCIH false path via 1-arg factory at
// 0x006CC530; zombie inc at +0x5C; 0x20 alloc via allocBlock 0x006D29E0 plus ??0Rva006DE1A0@@QAE@XZ;
// callers at 0x00709BA3 0x00709CE3 0x0070A2D3; frame ctor 0x0070A2C0 passes type 0x2d.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

class AptValueBig {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual AptValueBig *s03();
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
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
};

class BfmeAptValue006DCD20 : public AptValueBig {
public:
    unsigned int m_flags;
    int isCIH(bool bUndefOK) const;
};

class AptCIH : public AptValueBig {
public:
    char m_pad[0x5C - 4];
    unsigned int m_zombie : 16;
    const AptCIH *rva006E0CB0() const;
};

void *__cdecl Rva006CC530Get(int);
class Rva006D2A60 {
public:
    void *allocBlock(int nBytes);
};
extern Rva006D2A60 *g_00E176F4;
extern void *g_00E1834C;
extern AptValueBig *g_00E1835C;
extern AptValueBig *g_00E180F0;

class Rva006DE1A0 : public AptValueBig {
public:
    int m_04;
    void *m_08;
    char m_pad2[0x20 - 0x0C];
    Rva006DE1A0();
    static void *operator new(unsigned int size)
    {
        return ((Rva006D2A60 *)g_00E176F4)->allocBlock((int)size);
    }
    static void operator delete(void *p)
    {
        (void)p;
    }
};

class AptNativeHash {
public:
    int mnTotalSize;
    void *mpData;
    AptValueBig *mpProto;
    AptValueBig *mpPrototype;
    unsigned int nEventHandlers;
    AptNativeHash(int size);
};

class Rva006D6360 : public BfmeAptValue006DCD20 {
public:
    AptNativeHash m_hash;
    Rva006D6360(int type, int size);
    virtual ~Rva006D6360();
};

class Rva00709870Base : public Rva006D6360 {
public:
    unsigned int m_bits;
    BfmeAptValue006DCD20 *m_20;
    AptCIH *m_24;
    AptValueBig *m_28;
    unsigned short m_2C;
    Rva00709870Base(int type, AptValueBig *a2, BfmeAptValue006DCD20 *a3, bool bFlag);
};

Rva00709870Base::Rva00709870Base(int type, AptValueBig *a2, BfmeAptValue006DCD20 *a3, bool bFlag)
    : Rva006D6360(type, 8)
{
    *(unsigned char *)&m_bits = 0;
    m_bits &= 0xFFFFFCFF;
    m_20 = a3;
    m_24 = 0;
    m_28 = 0;
    m_2C = 0;
    if (!g_00E1834C) {
        g_bfmeAptAssertAtE17734("spRegBlockBase", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0xF4);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (a2) {
        a2->s24();
        m_28 = g_00E1835C;
        if (m_28)
            m_28->s00();
    }
    const AptCIH *ci;
    if ((unsigned char)a3->isCIH(false))
        ci = ((AptCIH *)m_20)->rva006E0CB0();
    else
        ci = (const AptCIH *)Rva006CC530Get(0);
    m_24 = (AptCIH *)ci;
    m_20->s00();
    m_24->s00();
    AptCIH *z = m_24;
    if (z->m_zombie >= 65536) {
        g_bfmeAptAssertAtE17734("nZombieCounter < 65536", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x53);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    bool f = bFlag;
    ++z->m_zombie;
    if (f) {
        Rva006DE1A0 *obj = new Rva006DE1A0();
        if (obj)
            obj->s00();
        AptValueBig *old = m_hash.mpPrototype;
        if (old)
            old->s01();
        m_hash.mpPrototype = obj;
        AptValueBig *glob = g_00E180F0;
        AptValueBig *ret = obj->s03();
        if (glob)
            glob->s00();
        AptValueBig *old8 = *(AptValueBig **)((char *)ret + 8);
        if (old8)
            old8->s01();
        *(AptValueBig **)((char *)ret + 8) = glob;
    }
}
