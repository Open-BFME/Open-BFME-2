// ??0Rva0022141E@@QAE@ABVAsciiString@@@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva0022141E@@QAE@ABVAsciiString@@@Z @0x0022141E 136B
// Ctor stores vtable s_slot3E4first at +0 plus iterator at +4 from static map insert via rowed getter 0x002213D9 plus make_pair 0x0032ACCF plus pair copy 0x00466EA7 plus insert_unique 0x00221329. Evidence: retail bytes plus callers plus rowed callees.
#include <map>
#include "ascii_string.h"

extern "C" char s_slot3E4first;

struct NoCaseTreeValue4 { unsigned char m_data[4]; };
class FXList;

namespace _STL {
template <class T1, class T2> struct pair;
template <class T1, class T2> _STL::pair<T1, T2> make_pair(const T1 &, const T2 &);
}

extern _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get();

class Rva0022141E {
public:
    Rva0022141E(const AsciiString &name);
private:
    void *volatile m_vtbl;
    void *volatile m_04;
};

Rva0022141E::Rva0022141E(const AsciiString &name) : m_vtbl(&s_slot3E4first), m_04(0)
{
    typedef _STL::map<AsciiString, NoCaseTreeValue4, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > MapNoCase;
    typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseVal;
    MapNoCase *map = (MapNoCase *)Rva002213D9Get();
    m_04 = *(void *volatile *)&map->insert(NoCaseVal(*(const NoCaseVal *)&_STL::make_pair(name, (const FXList *)this))).first;
}
