// cl: /MD
// ??0Rva0035E2E6@@QAE@XZ @ 0x0035E2E6 37B: derived ctor calling base ??0Rva001DBAA4 at 0x001DBAA4.
// Same vtable 0x008165D0 as dtor ??1Rva0035E2CF at 0x0035E2CF; clears +0xC then sets +0x20=-1
// +0x4=6 +0x9=1. Gap between 0x0035E2CF and 0x0035E30B in FamilyTailDtors1DBAC3.cpp.
// Opaque address-derived name; base layout copied from Rva001DBAA4Ctor.cpp.
class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    int m_C;
};
class Rva0035E2E6 : public Rva001DBAA4
{
public:
    virtual ~Rva0035E2E6();
    Rva0035E2E6();
    char m_pad10[0x10];
    int m_20;
};
Rva0035E2E6::Rva0035E2E6()
{
    m_C = 0;
    m_20 = -1;
    m_4 = 6;
    m_9 = true;
}
