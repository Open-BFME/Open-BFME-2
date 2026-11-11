// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva005C96A9@Rva005C96A9@@QAEXUTreeHintRef00217D4C@@H@Z 0x005C96A9 66B
// Evidence: caller 0x005C976F passes TreeHintRef by value plus dword at +0x264 with ecx=sub-object at +0x218; callees rowed TreeHintRef op= 0x002174A4 and Release 0x0007DEEF; stores to +0x34/+0x38; EH prolog with funclet.
// ICF/EH funclet at 0x7A0F09 is generated per-TU; reloc filled by gate.
#include "ascii_string.h"
#include "../../Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
    if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
}
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

// LINK: the open call binds the rowed owner at 0x00524D01 (MovieWindowPlayback::OpenMovie, Rva00524B7ACtor.cpp).
#include "../../../../GameEngine/Include/Common/MovieWindowPlayback.h"

// The owner at 0x005C976F contains this same setter object at +0x218.
// Native calls expose its vptr at +0 and state byte +0x24 while the
// already verified setter establishes +0x34/+0x38. Original names remain
// unknown; the layout here is limited to these measured members.
// The +0x258 setting record (rowed copy 0x005C962C).
struct Rva005C962C
{
    Rva005C962C &rva005C962C(const Rva005C962C &other);
};

class Rva005C976F
{
public:
    void rva005C976F();
    int rva005C9823();
    int rva005C97BE(int msg, int id, const Rva005C962C *setting);
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
        reinterpret_cast<MovieWindowPlayback *>(&m_helper218)->OpenMovie(m_name258, m_flags25c);
    }
}

// ?rva005C9823@Rva005C976F@@QAEHXZ
// Native Ghidra extent 0x005C9823..0x005C9880; RET 0. Changes in bit
// 0x10 choose a virtual +0x24 call or the verified restoration wrapper.
// The helper's state bit 0 gates its final virtual +0x28 call.
int Rva005C976F::rva005C9823()
{
    if (!(m_previous254 & 0x10) && (m_flags08 & 0x10))
    {
        if (m_helper218.stateFlags() & 1)
            m_helper218.slot24();
    }
    else if ((m_previous254 & 0x10) && !(m_flags08 & 0x10))
    {
        rva005C976F();
    }
    m_previous254 = m_flags08;
    if (m_helper218.stateFlags() & 1)
        m_helper218.slot28();
    return 1;
}

// ?rva005C97BE@Rva005C976F@@QAEHHHPBURva005C962C@@@Z
// Native 0x005C97BE..0x005C9823, RET 0xC: the window's message handler
// (vtable 0x0086DAC4 slot 2). Messages 1 and 2 reach the +0x218 helper's
// slots 1 and 9; message 0x1D with id 1000 copies a supplied setting into
// +0x258 (rowed 0x005C962C), marks it pending and applies it (0x005C976F
// above). Those answer handled; anything else is not.
int Rva005C976F::rva005C97BE(int msg, int id, const Rva005C962C *setting)
{
    switch (msg)
    {
    case 1:
        m_helper218.slot04();
        break;
    case 2:
        m_helper218.slot24();
        break;
    case 0x1D:
        if (id != 1000)
            return 0;
        if (setting)
        {
            ((Rva005C962C *)&m_name258)->rva005C962C(*setting);
            m_pending268 = true;
            rva005C976F();
        }
        break;
    default:
        return 0;
    }
    return 1;
}
