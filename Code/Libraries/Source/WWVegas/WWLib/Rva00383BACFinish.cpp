// ?_M_insert_00383BAC@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z
// ?_M_insert_00383BAC@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Map<int,int> _M_insert for 0x00383BAC (136B): address-scoped spelling (the
// unsuffixed name is claimed by the distinct 0x0038341E build in
// stlport_map_int_int_os.cpp). Verbatim header logic, except the two node
// creates go through the rowed YG create 0x003834CD as thiscall (the dead
// mov ecx reload in retail proves a receiver is passed); the callee ignores
// it. Callers 0x00383CA7 (134B) and 0x003840F2 (294B).
#define _M_insert _M_insert_00383BAC
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::pair<const int, int> IntIntValue;
typedef _STL::_Rb_tree_node<IntIntValue> IntIntNode;
typedef _STL::_Rb_tree<int, IntIntValue, _STL::_Select1st<IntIntValue>, _STL::less<int>, _STL::allocator<IntIntValue> > MapIntIntTree;

IntIntNode * __stdcall Rva003834CDCreate(const IntIntValue &value);
#pragma warning(push)
#pragma warning(disable : 4234)
typedef MapIntIntTree::_Link_type (__thiscall *CreateNodeFn)(void *, const MapIntIntTree::value_type &);
#pragma warning(pop)

// TU-scoped shim: the second retail map<int,int> _M_insert build calls its
// node-create as a thiscall (mov ecx,edi before the call) rather than the
// push-this/pop-pop the __stdcall free spelling degrades to; naming the create
// through a same-layout member preserves the ABI. Body folds with
// Rva003834CDCreate at 0x003834CD.
class Rva003834CDHelper
{
public:
	IntIntNode *_M_create_node_00383BAC(const IntIntValue &value);
};

// ?_M_insert@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBHH@2@0@Z present-unmatched
template <>
MapIntIntTree::iterator MapIntIntTree::_M_insert(MapIntIntTree::_Base_ptr __x_, MapIntIntTree::_Base_ptr __y_, const MapIntIntTree::value_type &__v, MapIntIntTree::_Base_ptr __w_)
{
	MapIntIntTree::_Link_type __w = (MapIntIntTree::_Link_type)__w_;
	MapIntIntTree::_Link_type __x = (MapIntIntTree::_Link_type)__x_;
	MapIntIntTree::_Link_type __y = (MapIntIntTree::_Link_type)__y_;
	MapIntIntTree::_Link_type __z;

	if (__y == this->_M_header._M_data ||
		(__w == 0 &&
			(__x != 0 ||
				_M_key_compare(_STL::_Select1st<IntIntValue>()(__v), _S_key(__y)))))
	{
		__z = ((Rva003834CDHelper *)this)->_M_create_node_00383BAC(__v);
		_S_left(__y) = __z;
		if (__y == this->_M_header._M_data) {
			_M_root() = __z;
			_M_rightmost() = __z;
		}
		else if (__y == _M_leftmost())
			_M_leftmost() = __z;
	}
	else {
		__z = ((Rva003834CDHelper *)this)->_M_create_node_00383BAC(__v);
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
