// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_clone_node@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z 0x005041D8 30B evidence: Rb_tree map int to AsciiString clone 30B via rowed Record create_node 0x005041B6 plus color copy plus null links; callers 0x0050428C 0x005042BC in rowed _M_copy 0x0050427F
#include <map>

class AsciiString { public: void *m_data; };
class Rva00064640Record { public: unsigned char m_data[28]; };

typedef _STL::_Rb_tree<int, _STL::pair<const int, AsciiString>, _STL::_Select1st<_STL::pair<const int, AsciiString> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > HAsciiStringMapTree;
typedef _STL::_Rb_tree<Rva00064640Record, Rva00064640Record, _STL::_Identity<Rva00064640Record>, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > VRva00064640RecordSetTree;

// Access shim: _M_create_node is protected, so the cross-tree call below
// goes through a derived helper. It inlines, leaving a direct call that
// resolves through the rowed 0x005041B6 body.
struct RecordCreateCaller : public VRva00064640RecordSetTree
{
	__forceinline _Link_type createFrom(const value_type &value)
	{
		return _M_create_node(value);
	}
};

// ?_M_clone_node@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z
template <>
HAsciiStringMapTree::_Link_type HAsciiStringMapTree::_M_clone_node(HAsciiStringMapTree::_Link_type __x)
{
	_Link_type __tmp = (_Link_type)((RecordCreateCaller *)this)->createFrom((const VRva00064640RecordSetTree::value_type &)__x->_M_value_field);
	__tmp->_M_color = __x->_M_color;
	__tmp->_M_left = 0;
	__tmp->_M_right = 0;
	return __tmp;
}
template HAsciiStringMapTree::_Link_type HAsciiStringMapTree::_M_clone_node(HAsciiStringMapTree::_Link_type);
