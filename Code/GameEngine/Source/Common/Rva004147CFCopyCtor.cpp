// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Fix over the banked 0.95 attempt, from the retail unwind map: state 2
// destroys the member at +0x14 through the rowed pool-aware member dtor
// 0x00360D26, so that member is a Rva00360D26Member (trivially copied, own
// destructor), not an int; the vector copied last needs no state of its own.
// ??0Rva004147CF@@QAE@ABV0@@Z @ 0x004147CF 125B: copy ctor with vtable 0x0083A09C,
// StringBase copy at +0x04 via pin 0x000365F0, ints/bytes at +0x08..+0x19,
// vector<BfmePod44> copy at +0x1C via row 0x00414490, ints at +0x28/+0x2C.
// Prev/next STLport; caller 0x00414A92 in 0x00414A76.
#include <vector>

#include "ascii_string.h"

struct BfmePod44 { int a[11]; };

namespace _STL
{
// Suppress duplicate vector<BfmePod44> copy COMDAT; retail's copy is
// rowed at 0x00414490. The row below keeps calling it, so its bytes
// are unchanged.
template <> vector<BfmePod44, allocator<BfmePod44> >::vector(const vector<BfmePod44, allocator<BfmePod44> > &);
}

class Rva00360D26Member
{
public:
    ~Rva00360D26Member();
private:
    int m_x;
};
class EmptyBase
{
public:
    EmptyBase() {}
    ~EmptyBase();
};

class Rva004147CF : public EmptyBase
{
public:
    virtual ~Rva004147CF();
    Rva004147CF(const Rva004147CF &other);
private:
    AsciiString m_str04;
    int m_08;
    int m_0C;
    int m_10;
    Rva00360D26Member m_14;
    unsigned char m_18;
    unsigned char m_19;
    char m_pad1A[2];
    _STL::vector<BfmePod44, _STL::allocator<BfmePod44> > m_vec1C;
    int m_28;
    int m_2C;
};

// ??0Rva004147CF@@QAE@ABV0@@Z @0x004147CF
Rva004147CF::Rva004147CF(const Rva004147CF &other)
    : m_str04(other.m_str04),
      m_08(other.m_08),
      m_0C(other.m_0C),
      m_10(other.m_10),
      m_14(other.m_14),
      m_18(other.m_18),
      m_19(other.m_19),
      m_vec1C(other.m_vec1C),
      m_28(other.m_28),
      m_2C(other.m_2C)
{
}
