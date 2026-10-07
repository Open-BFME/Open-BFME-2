// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva005C96A9@Rva005C96A9@@QAEXUTreeHintRef00217D4C@@H@Z 0x005C96A9 66B
// Evidence: caller 0x005C976F passes TreeHintRef by value plus dword at +0x264 with ecx=sub-object at +0x218; callees rowed TreeHintRef op= 0x002174A4 and Release 0x0007DEEF; stores to +0x34/+0x38; EH prolog with funclet.
// ICF/EH funclet at 0x7A0F09 is generated per-TU; reloc filled by gate.
#include "ascii_string.h"
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
    char m_pad04[0x20];
    unsigned char m_state24;
    char m_pad25[0x0f];
    TreeHintRef00217D4C m_hint;
    int m_value;
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    void rva005C96A9(TreeHintRef00217D4C hint, int value);
    void rva00524D01(const AsciiString &name, int flags);
    unsigned char stateFlags() const { return m_state24; }
};
void Rva005C96A9::rva005C96A9(TreeHintRef00217D4C hint, int value)
{
    TreeHintRef00217D4C &slot = m_hint;
    slot = hint;
    m_value = value;
}

// The owner at 0x005C976F contains this same setter object at +0x218.
// Native calls expose its vptr at +0 and state byte +0x24 while the
// already verified setter establishes +0x34/+0x38. Original names remain
// unknown; the layout here is limited to these measured members.
class Rva005C976F
{
public:
    void rva005C976F();
private:
    char m_pad00[8];
    unsigned int m_flags08;
    char m_pad0c[0x218 - 0x0c];
    Rva005C96A9 m_helper218;
    unsigned int m_previous254;
    AsciiString m_name258;
    int m_flags25c;
    TreeHintRef00217D4C m_hint260;
    int m_value264;
    bool m_pending268;
};

// ?rva005C976F@Rva005C976F@@QAEXXZ
// Native Ghidra extent 0x005C976F..0x005C97BE; RET 0. The by-value
// reference copy increments +4, exactly as the rowed setter consumes it.
// Callee 0x00524D01 copies its string argument through 0x000365F0 and
// reads its integer flag argument; the remaining subsystem is unknown.
void Rva005C976F::rva005C976F()
{
    if (m_pending268)
    {
        m_helper218.rva005C96A9(m_hint260, m_value264);
        m_helper218.rva00524D01(m_name258, m_flags25c);
    }
}
