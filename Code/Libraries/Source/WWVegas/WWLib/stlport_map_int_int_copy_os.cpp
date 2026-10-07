// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Map<int,int> tree copy at 0x00383C34 (115B): address-scoped spelling (fleet
// _M_copy_0021C2CC precedent in stlport_map_int_int_create_node.cpp: the
// unsuffixed name is claimed by the distinct 0x2CF6CF build in
// stlport_map_int_int_copy.cpp). Custom body clones through the rowed
// member variant at 0x003834EF (dead ecx reload), parent store,
// recursive right copy, iterative left descent.
// Callers 0x00383C5D/0x00383C8A (self) and 0x003840B6/0x003B1F16.
#define _M_copy _M_copy_00383C34
#include <map>

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > MapIntIntTree;

// Address-scoped call view: the receiver is unused; this clone calls the
// 0x3834CD create variant rather than the ordinary tree's 0x382B7F variant.
class Rva003834EFClone
{
public:
	MapIntIntTree::_Link_type clone(MapIntIntTree::_Link_type);
};

// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z present-unmatched
template <>
MapIntIntTree::_Link_type MapIntIntTree::_M_copy(MapIntIntTree::_Link_type __x, MapIntIntTree::_Link_type __p)
{
	MapIntIntTree::_Link_type __top = reinterpret_cast<Rva003834EFClone *>(this)->clone(__x);
	__top->_M_parent = __p;
	if (__x->_M_right)
		__top->_M_right = _M_copy((MapIntIntTree::_Link_type)__x->_M_right, __top);
	__p = __top;
	__x = (MapIntIntTree::_Link_type)__x->_M_left;
	while (__x != 0) {
		MapIntIntTree::_Link_type __y = reinterpret_cast<Rva003834EFClone *>(this)->clone(__x);
		__p->_M_left = __y;
		__y->_M_parent = __p;
		if (__x->_M_right)
			__y->_M_right = _M_copy((MapIntIntTree::_Link_type)__x->_M_right, __y);
		__p = __y;
		__x = (MapIntIntTree::_Link_type)__x->_M_left;
	}
	return __top;
}
#undef _M_copy
