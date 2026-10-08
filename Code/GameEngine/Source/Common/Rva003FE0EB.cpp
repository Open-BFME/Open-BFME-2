// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva003FE0EB@Rva003FE05E@@QAE?AUTreeHintRef00217D4C@@XZ @0x003FE0EB 83B: __thiscall TreeHintRef getter that refreshes +0x4C via rowed rva003FE05E when +0x38 link differs then returns +0x4C with AddRef. Evidence: rowed rva003FE05E 0x003FE05E plus pinned helper 0x002E0BC0 plus global g_009FEF10 plus sibling layouts 0x003FE0B3 0x003FE05E.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct TargetRef00217D4C
{
    void *m_vtbl;
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            ++m_ptr->references;
    }
    __forceinline ~TreeHintRef00217D4C()
    {
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
struct Rva003FE38
{
    char m_pad00[0x54];
    int m_54;
};
// The native provider normalizes its bool result with movzx eax,al at
// 0x002E0BE0. Keep each caller's byte-sized test while naming its int ABI.
class Rva002E071E
{
public:
    char m_pad00[0x14];
    int m_14;
public:
    int rva002E0BC0(int v);
};
class Rva002BA8F1Logic
{
public:
    char m_pad00[0x98];
    Rva002E071E *m_98;
    char m_pad9C[0xF4 - 0x9C];
    int m_F4;
};

class Rva003FE05E
{
    char m_pad00[0x38];
    Rva003FE38 *m_38;
    char m_pad3C[0x4C - 0x3C];
    TreeHintRef00217D4C m_hint;
public:
    void rva003FE05E();
    TreeHintRef00217D4C rva003FE0EB();
};
TreeHintRef00217D4C Rva003FE05E::rva003FE0EB()
{
    if (m_38)
    {
        int v = m_38->m_54;
        Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
        int f4 = logic->m_F4;
        Rva002E071E *helper = logic->m_98;
        if (f4 != 0)
            rva003FE05E();
        else if (helper->m_14 == v)
            rva003FE05E();
        else if ((unsigned char)helper->rva002E0BC0(v))
            rva003FE05E();
    }
    return m_hint;
}
