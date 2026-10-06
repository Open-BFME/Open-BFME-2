// cl: /MD
//
// ??0Rva0035D0D1@@QAE@XZ @ 0x0035D097 58B.
// Ctor via base ??0Rva001DBAA4 at 0x001DBAA4 plus vtable 0x008163D8 with
// +4=30 +0x10=0 +0x14=30 +0x18=7 +0x1C=0 +0x20=float +0x24=0.
// Evidence: vtable store 0x008163D8 same as dtor 0x0035D0D1, callee 0x001DBAA4 row,
// float from 1.0f, INI StartFrame +0x10 EndFrame +0x14 ViewsToFade +0x18 LeaveSilent +0x1C.
// Caller 0x0035D0FE. The base ctor is rowed under Rva001DBAA4 while the dtor
// TU (Rva001DBAC3Derived.cpp) names the base by its dtor, so this ctor stays
// in its own TU. The +0x20 initial value is the 1.0f literal (pooled at
// 0x00BBB8D8), not a float global.

class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    char m_padB;
    int m_C;
};

class Rva0035D0D1 : public Rva001DBAA4
{
public:
    Rva0035D0D1();
    virtual ~Rva0035D0D1();
    virtual void slot1(int);
    virtual void slot2(int);
    virtual void slot3();
    virtual void slot4();
    virtual void Rva0035D1C6();
    virtual void slot6();
    int m_10;
    int m_14;
    int m_18;
    bool m_1C;
    char m_pad1D[3];
    float m_20;
    bool m_24;
};

Rva0035D0D1::Rva0035D0D1() : m_10(0), m_14(30), m_18(7), m_1C(false), m_20(1.0f), m_24(false)
{
    m_4 = 30;
}
