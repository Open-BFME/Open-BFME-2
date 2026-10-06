// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1Rva002214A6@@UAE@XZ, retail 0x002214A6 31B.
// Base dtor stores vtable 0x00C1C780 then erases iterator at +4 from global
// AsciiString set reached through rowed getter 0x002213D9 and rowed Rb_tree
// erase 0x00056BC3. Evidence: retail bytes plus derived tail-jmp 0x002215F4.
#include <map>
#include <set>
#include "ascii_string.h"

_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get();

class Rva002214A6 {
public:
    virtual ~Rva002214A6();
    _STL::set<AsciiString>::iterator m_it;
};

class Rva002215F4 : public Rva002214A6 {
public:
    virtual ~Rva002215F4();
};

Rva002214A6::~Rva002214A6()
{
    _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *p = Rva002213D9Get();
    ((_STL::set<AsciiString> *)p)->erase(m_it);
}

Rva002215F4::~Rva002215F4()
{
}
