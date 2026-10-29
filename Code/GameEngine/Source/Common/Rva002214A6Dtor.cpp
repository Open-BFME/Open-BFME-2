// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport46
// ??0Rva002215F4@@QAE@PAXABVAsciiString@@@Z, retail 0x002215D5 31B.
// Caller 0x00221635 allocates 12 bytes and calls this with its this pointer and
// the same AsciiString passed to base ctor 0x0022141E; this stores the pointer
// at +8 then installs the vtable shared with the matched dtor at 0x002215F4.
// The field purpose and enclosing class identity remain address-derived.
// ??1Rva002214A6@@UAE@XZ, retail 0x002214A6 31B.
// Base dtor stores vtable 0x00C1C780 then erases iterator at +4 from global
// AsciiString set reached through rowed getter 0x002213D9 and rowed Rb_tree
// erase 0x00056BC3. Evidence: retail bytes plus derived tail-jmp 0x002215F4.
#include <map>
#include <set>
#include "ascii_string.h"

_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get();
struct NoCaseTreeValue4 { char m_body[4]; };
// bfme link decl-only begin
// The set erase is the row at 0x00056BC3; instantiating it here would emit erase, _Destroy and ??_G copies.
namespace _STL { template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::erase(_Rb_tree_iterator<AsciiString, _Nonconst_traits<AsciiString> >); }
// The node constructor is the row at 0x00221201 (stlport_rb_tree_create_nodes2.cpp); this
// unit's copy calls the _Construct name instead of retail's 0x0022112D construct helper.
namespace _STL { template <> _Rb_tree_node<pair<const AsciiString, NoCaseTreeValue4> > *_Rb_tree<AsciiString, pair<const AsciiString, NoCaseTreeValue4>, _Select1st<pair<const AsciiString, NoCaseTreeValue4> >, less<AsciiString>, allocator<pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(const pair<const AsciiString, NoCaseTreeValue4> &); }
// bfme link decl-only end

class Rva002214A6 {
public:
    virtual ~Rva002214A6();
    _STL::set<AsciiString>::iterator m_it;
    Rva002214A6(const AsciiString &name);
};

class Rva002215F4 : public Rva002214A6 {
public:
    void *m_owner; // +8; passed by the enclosing constructor at 0x00221635
    Rva002215F4(void *owner, const AsciiString &name);
    virtual ~Rva002215F4();
};

Rva002215F4::Rva002215F4(void *owner, const AsciiString &name)
    : Rva002214A6(name), m_owner(owner)
{
}

Rva002214A6::~Rva002214A6()
{
    _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *p = Rva002213D9Get();
    ((_STL::set<AsciiString> *)p)->erase(m_it);
}

Rva002215F4::~Rva002215F4()
{
}

Rva002214A6::Rva002214A6(const AsciiString &name)
{
    typedef _STL::map<AsciiString, NoCaseTreeValue4, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > MapV;
    MapV *map = (MapV *)Rva002213D9Get();
    NoCaseTreeValue4 value;
    *(const void **)&value = this;
    *(void *volatile *)&m_it = *(void *volatile *)&map->insert(_STL::make_pair(name, value)).first;
}
