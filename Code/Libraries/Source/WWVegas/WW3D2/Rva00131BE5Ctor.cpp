// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0Rva00131BE5@@QAE@PAX000HH@Z @ 0x00131B57 (142B): ctor stores vtable 0x007D25D8 then StringClass at +0x18 and Gen_00920A20 at +0x1C then new Rva0013107A backend at +0x14 plus CreateTexture. Evidence: same vtable and base as neighbouring dtor 0x00131BE5 plus same 0x3C layout as BfmeThingSJ plus rowed GenBase 0x0061ED40 plus rowed StringClass 0x00065F34 plus pinned Gen_00920A20 0x0013EA00 plus rowed Rva0013107A 0x0013107A plus rowed CreateTexture 0x001310E3. Callers 0x000EF289 and 0x00131E32.
class GenBase009EB7D0
{
public:
    GenBase009EB7D0();
    virtual ~GenBase009EB7D0();
};

class StringClass
{
public:
    StringClass(int value, bool flag);
    ~StringClass();
    char *m_Buffer;
};

class Gen_00920A20
{
public:
    Gen_00920A20(int mode);
    ~Gen_00920A20();
    int m_bfmeA;
    int m_bfmeB;
    int m_bfmeC;
    int m_bfmeD;
    int m_bfmeE;
};

class Rva0013107A
{
public:
    Rva0013107A() throw();
    virtual ~Rva0013107A();
    char m_pad[0x54];
};

class BfmeResetTextureBackend
{
public:
    void CreateTexture(int a, int b, int c, int d, int e, int f, int g) throw();
};

void *__cdecl operator new(unsigned int size) throw();

class Rva00131BE5 : public GenBase009EB7D0
{
public:
    Rva00131BE5(void *first, void *second, void *third, void *fourth, int fifth, int sixth);
    virtual ~Rva00131BE5();
    char m_pad04[0x10];
    Rva0013107A *m_14;
    StringClass m_str;
    Gen_00920A20 m_gen;
    int m_30;
    void *m_34;
    int m_38;
};

// ??0Rva00131BE5@@QAE@PAX000HH@Z
Rva00131BE5::Rva00131BE5(void *first, void *second, void *third, void *fourth, int fifth, int sixth)
    : m_14(0), m_str(0, false), m_gen(0), m_30(0), m_34(third), m_38(0)
{
    Rva0013107A *backend = new Rva0013107A;
    m_14 = backend;
    ((BfmeResetTextureBackend *)backend)->CreateTexture((int)first, (int)second, (int)third, (int)fourth, fifth, sixth, 0);
}
