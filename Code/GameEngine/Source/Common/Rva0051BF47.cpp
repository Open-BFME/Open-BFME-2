// cl: /DNDEBUG /MD
// ?Rva0051BF47Run@@YAXXZ @0x0051BF47 46B
// evidence: unlock lane, caller 0x0051C160 (no args void), callees rowed enable 0x00222479 plus vslot 0x28 plus pin AptTimeLine 0x0051ED7E, globals g_00E04914 g_Va00A01E48 TheRva00222A8BTarget
extern int g_00E04914;

struct GlobalA01E48
{
    char _pad[0x54];
    unsigned char m_54;
};
extern class Shell *TheShell;

class Rva00222479ByteOneSetter
{
public:
    void enable();
};

class Rva00222A8BTarget
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

void Rva0051ED7ETail();

void Rva0051BF47Run()
{
    if (g_00E04914 == 0)
        return;
    (*(GlobalA01E48 **)&TheShell)->m_54 = 1;
    ((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
    (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->v10();
    Rva0051ED7ETail();
}
