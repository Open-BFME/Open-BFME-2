// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva005C96A9@Rva005C96A9@@QAEXUTreeHintRef00217D4C@@H@Z 0x005C96A9 66B
// Evidence: caller 0x005C976F passes TreeHintRef by value plus dword at +0x264 with ecx=sub-object at +0x218; callees rowed TreeHintRef op= 0x002174A4 and Release 0x0007DEEF; stores to +0x34/+0x38; EH prolog with funclet.
// ICF/EH funclet at 0x7A0F09 is generated per-TU; reloc filled by gate.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
    __forceinline ~TreeHintRef00217D4C() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
class Rva005C96A9 {
    char m_pad[0x34];
    TreeHintRef00217D4C m_hint;
    int m_value;
public:
    void rva005C96A9(TreeHintRef00217D4C hint, int value);
};
void Rva005C96A9::rva005C96A9(TreeHintRef00217D4C hint, int value)
{
    TreeHintRef00217D4C &slot = m_hint;
    slot = hint;
    m_value = value;
}
