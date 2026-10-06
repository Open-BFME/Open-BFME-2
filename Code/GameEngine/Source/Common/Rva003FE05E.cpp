// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva003FE05E@Rva003FE05E@@QAEXXZ @0x003FE05E 85B: __thiscall refresh of +0x4C TreeHintRef from +0x38 int via Helper0056BABF else clear. Evidence: rowed TreeHintRef op= 0x002174A4 plus rowed clear 0x002BED91 plus pinned Helper0056BABF plus rowed Release 0x0007DEEF plus sibling setter 0x003FE0B3 same op-release shape plus callers 0x003FE125 0x003FE550.
struct TargetRef00217D4C
{
    void *m_vtbl;
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

struct RvaF6Ret
{
    TargetRef00217D4C *m_ptr;
    __forceinline ~RvaF6Ret()
    {
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
RvaF6Ret __cdecl Helper0056BABF(int v);

struct Rva002BED91
{
    TargetRef00217D4C *m_ptr;
    void clear();
};

class Rva003FE05E
{
    char m_pad00[0x38];
    int m_38;
    char m_pad3C[0x10];
    TreeHintRef00217D4C m_hint;
public:
    void rva003FE05E();
};

void Rva003FE05E::rva003FE05E()
{
    if (m_38 != 0)
    {
        m_hint = *reinterpret_cast<TreeHintRef00217D4C *>(&Helper0056BABF(m_38));
    }
    else
    {
        reinterpret_cast<Rva002BED91 *>(&m_hint)->clear();
    }
}
