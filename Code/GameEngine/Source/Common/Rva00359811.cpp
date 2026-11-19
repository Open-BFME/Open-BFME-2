// cl: /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7 /MD
// stlport
// ?rva00359811@Rva00359811@@QAEIABURva003597C3Element@@_N@Z 0x00359811 27B; branch and set erase call are retail evidence
#include <set>
// Suppress this TU's non-retail copy of ?_M_upper_bound@?$_Rb_tree@URva003597C3Element@@U1@U?$_Identity@URva003597C3Element@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003597C3Element;
namespace _STL { template <> _Rb_tree_node<Rva003597C3Element> * _Rb_tree<Rva003597C3Element,Rva003597C3Element,_Identity<Rva003597C3Element>,less<Rva003597C3Element>,allocator<Rva003597C3Element> >::_M_upper_bound(Rva003597C3Element const &) const; }
// Suppress this TU's non-retail copy of ?_M_lower_bound@?$_Rb_tree@URva003597C3Element@@U1@U?$_Identity@URva003597C3Element@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Rb_tree_node<Rva003597C3Element> * _Rb_tree<Rva003597C3Element,Rva003597C3Element,_Identity<Rva003597C3Element>,less<Rva003597C3Element>,allocator<Rva003597C3Element> >::_M_lower_bound(Rva003597C3Element const &) const; }
// Suppress this TU's non-retail copy of ?erase@?$_Rb_tree@URva003597C3Element@@U1@U?$_Identity@URva003597C3Element@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Rb_tree<Rva003597C3Element,Rva003597C3Element,_Identity<Rva003597C3Element>,less<Rva003597C3Element>,allocator<Rva003597C3Element> >::erase(_Rb_tree_iterator<Rva003597C3Element,_Nonconst_traits<Rva003597C3Element> >); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@URva003597C3Element@@U1@U?$_Identity@URva003597C3Element@@@_STL@@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Rb_tree<Rva003597C3Element,Rva003597C3Element,_Identity<Rva003597C3Element>,less<Rva003597C3Element>,allocator<Rva003597C3Element> >::_M_erase(_Rb_tree_node<Rva003597C3Element> *); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@URva003597C3Element@@@_STL@@@_STL@@QBEXPAU?$_Rb_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<_Rb_tree_node<Rva003597C3Element> >::deallocate(_Rb_tree_node<Rva003597C3Element> *,unsigned int) const; }

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva003597C3Element
{
	char bytes[8];
};

bool operator<(const Rva003597C3Element &left, const Rva003597C3Element &right);

class Rva00359811
{
public:
	unsigned int rva00359811(const Rva003597C3Element &key, bool useSecond);
private:
	char m_pad00[0x0c];
	_STL::set<Rva003597C3Element> m_first;
	_STL::set<Rva003597C3Element> m_second;
};

unsigned int Rva00359811::rva00359811(const Rva003597C3Element &key, bool useSecond)
{
	return (useSecond ? m_second : m_first).erase(key);
}
