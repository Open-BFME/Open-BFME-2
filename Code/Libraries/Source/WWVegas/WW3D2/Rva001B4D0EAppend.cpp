// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/stlp_nodealloc
// stlport
// Native 0x001B4D0E..0x001B4D16 forwards to the STLport list push_back
// at 0x001B4CEF with the list receiver at this+12. The callee is the
// existing 72-byte element instantiation; retain its opaque element name.
// The original enclosing type is not established. This view asserts only
// the observed list offset and the callee's const-reference argument ABI.
// Reference: STLport 4.5.3 _list.h through Open-BFME-1
// a7c38d3b2597121f178ab5190b3062478823257d.
#include <list>
struct BfmePod72 { int a[18]; };

// The native push_back provider owns the record construction machinery.
namespace _STL {
template <> void list<BfmePod72>::push_back(const BfmePod72 &);
}

class Rva001B4D0E {
public:
    void append(const BfmePod72 &value);
};

void Rva001B4D0E::append(const BfmePod72 &value)
{
    typedef _STL::list<BfmePod72, _STL::allocator<BfmePod72> > List;
    reinterpret_cast<List *>(reinterpret_cast<char *>(this) + 12)->push_back(value);
}
