// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004E2382@@QAE@XZ @ 0x004E2382 (63B).
// Default ctor: AsciiString at +0 nulled plus int at +4 zeroed plus
// set<AsciiString> at +8 via rowed 0x000D3A71 plus vector at +0x14 via
// rowed Vector_base BfmeE16 0x00211E58. Caller 0x004E3E91 builds a temp
// with it then assigns an AsciiString arg to +0 and destroys the temp
// via 0x004E2941. Layout from that caller plus the dtor shape.
#include <set>
#include <vector>

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL {
template <> struct less<AsciiString> {
    bool operator()(const AsciiString &left, const AsciiString &right) const {
        return left < right;
    }
};
}

struct BfmeE16 { float x, y, z, w; };

class Rva004E2382 {
public:
    Rva004E2382();
private:
    AsciiString m_00;
    int m_04;
    _STL::set<AsciiString> m_08;
    _STL::vector<BfmeE16> m_14;
};

Rva004E2382::Rva004E2382()
    : m_00(), m_04(0), m_08(), m_14()
{
}

// Private copy views preserve the 12-byte field widths while leaving their
// target type names address-derived. The tree wrapper tests call scheduling:
// its member call may keep ECX live before the source pointer is pushed.
class Rva004E1FE4TreeCopyView
{
public:
    // ?Rva004E1FE4TreeCopyView::Rva004E1FE4TreeCopyView absent-from-retail
    __forceinline Rva004E1FE4TreeCopyView(const Rva004E1FE4TreeCopyView &that)
    {
        copyFrom(that);
    }
    void copyFrom(const Rva004E1FE4TreeCopyView &that);
    ~Rva004E1FE4TreeCopyView();
private:
    unsigned char m_prefix[12];
};

class Rva004E1D4EVectorCopyView
{
public:
    Rva004E1D4EVectorCopyView(const Rva004E1D4EVectorCopyView &that);
private:
    unsigned char m_prefix[12];
};

class Rva004E2C66
{
public:
    Rva004E2C66(const Rva004E2C66 &that);
private:
    AsciiString m_string00;
    int m_unknown04;
    Rva004E1FE4TreeCopyView m_tree08;
    Rva004E1D4EVectorCopyView m_vector14;
};

Rva004E2C66::Rva004E2C66(const Rva004E2C66 &that)
    : m_string00(that.m_string00)
    , m_unknown04(that.m_unknown04)
    , m_tree08(that.m_tree08)
    , m_vector14(that.m_vector14)
{
}
