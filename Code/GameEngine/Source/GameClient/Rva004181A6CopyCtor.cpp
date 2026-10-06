// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva004181A6@@QAE@ABV0@@Z @0x004181A6 79B
// Copy ctor with AsciiString at +0 via pinned StringBase copy 0x000365F0
// plus 4-byte FixedStorage at +4 via rowed 0x002CF0F0 plus map<int,BfmePod24>
// at +8 via rowed Rb_tree copy 0x00418066 plus byte at +0x14. No vptrs.
// AsciiString inline copy/dtor via StringBase releaseBuffer gives EH state
// after first call; FixedStorage nothrow and Rb_tree NO_EXCEPTIONS need none.
// Evidence: unlock lane; callees rowed/pinned; unblocks 0x00418232 0x004181F5.
#include <map>
struct BfmePod24 { int a[6]; };
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeFixedStorage002CF0F0 {
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
class Rva004181A6 {
public:
    Rva004181A6(const Rva004181A6 &other);
private:
    AsciiString m_str;
    BfmeFixedStorage002CF0F0 m_fixed;
    _STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > m_tree;
    unsigned char m_14;
};
Rva004181A6::Rva004181A6(const Rva004181A6 &other)
    : m_str(other.m_str)
    , m_fixed(other.m_fixed)
    , m_tree(other.m_tree)
    , m_14(other.m_14)
{
}
