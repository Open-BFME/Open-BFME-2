// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_create_node@?$list@UTreeKey00242F5E@@V?$allocator@UTreeKey00242F5E@@@_STL@@@_STL@@IAEPAU?$_List_node@UTreeKey00242F5E@@@2@ABUTreeKey00242F5E@@@Z retail 0x002A1361 34B
// Evidence: frameless allocate 0x10 plus _Construct at node+8; _Construct is the rowed TreeKey00242F5E
// helper at 0x0029FB9C via rowed copy ctor 0x000CF475; byte allocator at 0x000307F0; caller 0x002A1BC6
// performs list hook insertion; same 34B frameless shape as crate 0x0035CAB4 and UnicodeString 0x00433B1E.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"

#include "TreeKey00242F5E.h"

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _List_iterator<TreeKey00242F5E,_Nonconst_traits<TreeKey00242F5E> > list<TreeKey00242F5E,allocator<TreeKey00242F5E> >::insert(_List_iterator<TreeKey00242F5E,_Nonconst_traits<TreeKey00242F5E> >,TreeKey00242F5E const &); }

// remove()/unique() need an operator== retail never defines; declare them
// specialized so the class instantiation below does not emit them.
namespace _STL {
template <> void list<TreeKey00242F5E,allocator<TreeKey00242F5E> >::remove(TreeKey00242F5E const &);
template <> void list<TreeKey00242F5E,allocator<TreeKey00242F5E> >::unique();
}

// Retail's placement copy here is the distinct body rowed at 0x0029FB9C, not
// the _Construct<TreeKey00242F5E> row at 0x000A7876: call it by its row name.
void Rva0029FB9CConstruct(TreeKey00242F5E *, const TreeKey00242F5E &);

// Retail calls the null-guarded copy at 0x0029FB9C, rowed under its own name.
void Rva0029FB9CConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);

// ?_M_create_node@?$list@UTreeKey00242F5E@@V?$allocator@UTreeKey00242F5E@@@_STL@@@_STL@@IAEPAU?$_List_node@UTreeKey00242F5E@@@2@ABUTreeKey00242F5E@@@Z @0x002A1361
template <>
_STL::_List_node<TreeKey00242F5E> *
_STL::list<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::_M_create_node(
	const TreeKey00242F5E &__x)
{
	_STL::_List_node<TreeKey00242F5E> *__p =
		(_STL::_List_node<TreeKey00242F5E> *)_STL::allocator<char>::allocate(16, 0);
	Rva0029FB9CConstruct(&__p->_M_data, __x);
	return __p;
}

// Explicit instantiation so inline callers odr-use the specialization above.
template class _STL::list<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >;
