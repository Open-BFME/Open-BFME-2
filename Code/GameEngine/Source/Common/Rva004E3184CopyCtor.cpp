// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0Rva004E3184@@QAE@ABV0@@Z @ 0x004E2F9F (295B).
// Copy ctor of the ModuleData class with vtable 0x00861F28 whose dtor is
// rowed at 0x004E3184. Same temp is built here and torn down by that dtor
// in caller 0x004FB924. _Construct wrapper at 0x004E3706 treats it as
// 88-byte BfmePod88. Members call StringBase<char> copy at 0x000365F0 and
// vector<AsciiString> copy at 0x000BC07E. Layout from the dtor TU plus
// retail offsets. Snapshot base dtor arms EH state 0 before the first member
// like retail.
#include <memory>
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"

class Rva004E3184 : public Snapshot {
public:
    virtual ~Rva004E3184();
    Rva004E3184(const Rva004E3184 &o);
private:
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    AsciiString m_10;
    AsciiString m_14;
    AsciiString m_18;
    AsciiString m_1c;
    unsigned int m_20;
    unsigned int m_24;
    AsciiString m_28;
    AsciiString m_2c;
    AsciiString m_30;
    AsciiString m_34;
    _STL::vector<AsciiString> m_vec38;
    unsigned int m_44;
    unsigned int m_48;
    unsigned int m_4c;
    AsciiString m_50;
    unsigned char m_54;
    unsigned char m_55;
};

Rva004E3184::Rva004E3184(const Rva004E3184 &o)
    : m_04(o.m_04), m_08(o.m_08), m_0c(o.m_0c), m_10(o.m_10),
      m_14(o.m_14), m_18(o.m_18), m_1c(o.m_1c),
      m_20(o.m_20), m_24(o.m_24),
      m_28(o.m_28), m_2c(o.m_2c), m_30(o.m_30), m_34(o.m_34),
      m_vec38(o.m_vec38),
      m_44(o.m_44), m_48(o.m_48), m_4c(o.m_4c),
      m_50(o.m_50), m_54(o.m_54), m_55(o.m_55)
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmePod88@@QAE@ABU0@@Z=??0Rva004E3184@@QAE@ABV0@@Z")
