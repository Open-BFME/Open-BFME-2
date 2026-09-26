// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// List-of-vector-uint _M_create_node, retail 0x0007981B (34 bytes). _List_node create for a list of
// unsigned-int vectors: allocates a 0x14 node (8-byte links plus the 12-byte
// vector) through the rowed byte allocator at 0x307F0, then constructs the
// vector value through the rowed _Construct at 0x796E8. The vector value
// type is call-proven by retail's own displacement. Custom No-exceptions
// MALLOC shape from the _M_create_node batch (no allocation-cleanup catch
// path); the _Construct specialization is declared only so its call resolves
// through its own row.
#include <list>
#include <vector>

namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
template <> void _Construct<_STL::vector<unsigned int> >(_STL::vector<unsigned int> *, _STL::vector<unsigned int> const &);
}

// ?_M_create_node@?$list@V?$vector@IV?$allocator@I@_STL@@@_STL@@V?$allocator@V?$vector@IV?$allocator@I@_STL@@@_STL@@@2@@_STL@@IAEPAU?$_List_node@V?$vector@IV?$allocator@I@_STL@@@_STL@@@2@ABV?$vector@IV?$allocator@I@_STL@@@2@@Z
template <>
_STL::_List_node<_STL::vector<unsigned int> > *_STL::list<_STL::vector<unsigned int>, _STL::allocator<_STL::vector<unsigned int> > >::_M_create_node(const _STL::vector<unsigned int> &__x)
{
	_STL::_List_node<_STL::vector<unsigned int> > *__p =
		(_STL::_List_node<_STL::vector<unsigned int> > *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<_STL::vector<unsigned int> >), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<_STL::vector<unsigned int> > *_STL::list<_STL::vector<unsigned int>, _STL::allocator<_STL::vector<unsigned int> > >::_M_create_node(const _STL::vector<unsigned int> &);
