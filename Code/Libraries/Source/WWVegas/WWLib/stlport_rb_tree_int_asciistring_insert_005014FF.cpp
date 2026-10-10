// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?_M_insert_005014FF@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHVAsciiString@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBHVAsciiString@@@2@0@Z @0x005014FF 136B
// _Rb_tree<int pair<const int AsciiString>>::_M_insert 4-arg form with iterator
// return (hidden first arg). Retail calls rowed _M_create_node 0x0050116B
// (44B node for 28B pair) as thiscall and rowed _Rebalance 0x00025490.
// Evidence: callees rowed 0x0050116B and 0x00025490; callers 0x00501587 and
// 0x00501BD8; key compare int at node+0x10; shape matches Rva00383BACFinish 136B.
#define _M_insert _M_insert_005014FF
#include <map>
#include "ascii_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::pair<const int, AsciiString> IntAsciiValue;
typedef _STL::_Rb_tree_node<IntAsciiValue> IntAsciiNode;
typedef _STL::_Rb_tree<int, IntAsciiValue, _STL::_Select1st<IntAsciiValue>, _STL::less<int>, _STL::allocator<IntAsciiValue> > MapIntAsciiTree;

// ?_M_insert@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHVAsciiString@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBHVAsciiString@@@2@0@Z present-unmatched
template <>
MapIntAsciiTree::iterator MapIntAsciiTree::_M_insert(MapIntAsciiTree::_Base_ptr __x_, MapIntAsciiTree::_Base_ptr __y_, const MapIntAsciiTree::value_type &__v, MapIntAsciiTree::_Base_ptr __w_)
{
	MapIntAsciiTree::_Link_type __w = (MapIntAsciiTree::_Link_type)__w_;
	MapIntAsciiTree::_Link_type __x = (MapIntAsciiTree::_Link_type)__x_;
	MapIntAsciiTree::_Link_type __y = (MapIntAsciiTree::_Link_type)__y_;
	MapIntAsciiTree::_Link_type __z;

	if (__y == this->_M_header._M_data ||
		(__w == 0 &&
			(__x != 0 ||
				_M_key_compare(_STL::_Select1st<IntAsciiValue>()(__v), _S_key(__y)))))
	{
		__z = _M_create_node(__v);
		_S_left(__y) = __z;
		if (__y == this->_M_header._M_data) {
			_M_root() = __z;
			_M_rightmost() = __z;
		}
		else if (__y == _M_leftmost())
			_M_leftmost() = __z;
	}
	else {
		__z = _M_create_node(__v);
		_S_right(__y) = __z;
		if (__y == _M_rightmost())
			_M_rightmost() = __z;
	}
	_S_parent(__z) = __y;
	_S_left(__z) = 0;
	_S_right(__z) = 0;
	_Rb_global_inst::_Rebalance(__z, this->_M_header._M_data->_M_parent);
	++_M_node_count;
	return iterator(__z);
}
#undef _M_insert
