// cl: /MD
// ??0Rva0035EE66@@QAE@XZ @ 0x0035EE66 37B: derived ctor calling base ??0Rva001DBAA4 at 0x001DBAA4.
// Same shape as 0x0035E2E6; vtable 0x0081661C same as dtor ??1Rva0035ED92 at 0x0035ED92.
// Clears +0xC then sets +0x20=-1 +0x4=8 +0x9=1. Gap between 0x0035ED92 and 0x0035EE8B.
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
class Rva0035EE66 : public Rva001DBAA4
{
public:
    virtual ~Rva0035EE66();
    Rva0035EE66();
    char m_pad10[0x10];
    int m_20;
};
Rva0035EE66::Rva0035EE66()
{
    m_C = 0;
    m_20 = -1;
    m_4 = 8;
    m_9 = true;
}
