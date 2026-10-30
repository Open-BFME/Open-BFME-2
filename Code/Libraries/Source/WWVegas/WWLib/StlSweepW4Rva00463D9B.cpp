// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
// The rowed callers erase ObjectID keys from the contain interface's int-keyed
// name set: OpenContain::onRemoving passes opaqueKey(rider->getID())
// (reinterpret_cast<const Element&>(int)) and HordeContain::removeMemberFromHorde
// passes *(const Element*)&id, so the element is a trivial 4-byte key compared
// as a signed int (the int-keyed twin of 0x00439862). The donor's declared
// ctor/copy/assign/dtor were over-specification that left
// ??1Rva00463D9BElement@@QAE@XZ unresolved; make the element trivial and give
// the free operator< the inlined int compare.
struct Rva00463D9BElement {
 int m_key;
 char m_pad[4];
};
inline bool operator<(const Rva00463D9BElement &left, const Rva00463D9BElement &right)
{
 return left.m_key < right.m_key;
}

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::_Rb_tree<Rva00463D9BElement, Rva00463D9BElement, _STL::_Identity<Rva00463D9BElement>, _STL::less<Rva00463D9BElement>, _STL::allocator<Rva00463D9BElement> >::erase(Rva00463D9BElement const &);

// Native 0x004643C9..0x004643CE is an independent forwarding entry.
// Retain the verified tree/key view without claiming set or multiset identity.
typedef _STL::_Rb_tree<Rva00463D9BElement, Rva00463D9BElement,
    _STL::_Identity<Rva00463D9BElement>, _STL::less<Rva00463D9BElement>,
    _STL::allocator<Rva00463D9BElement> > Rva004643C9Tree;
class Rva004643C9 : public Rva004643C9Tree {
public:
    unsigned int rva004643C9(const Rva00463D9BElement &key);
};
unsigned int Rva004643C9::rva004643C9(const Rva00463D9BElement &key)
{
    return erase(key);
}
