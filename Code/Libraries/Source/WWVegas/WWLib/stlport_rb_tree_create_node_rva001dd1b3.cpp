// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_create_node@?$_Rb_tree@URva001DD1B3@@U1@U?$_Identity@URva001DD1B3@@@_STL@@U?$less@URva001DD1B3@@@3@V?$allocator@URva001DD1B3@@@3@@_STL@@IAEPAU?$_Rb_tree_node@URva001DD1B3@@@2@ABURva001DD1B3@@@Z @0x001DD772 34B
// Rb_tree node create for 36-byte value: allocate 0x34 then rowed _Construct.
// Evidence: retail push 0 0x34 allocate then lea +0x10 Construct; callers in 0x001DD8EE.
#include <map>
#include <set>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct Rva001DD1B3 { public: unsigned char m_data[36]; };
typedef _STL::_Rb_tree<Rva001DD1B3, Rva001DD1B3, _STL::_Identity<Rva001DD1B3>, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> > URva001DD1B3SetTree;
namespace _STL {
template <> void _Construct<Rva001DD1B3>(Rva001DD1B3 *, const Rva001DD1B3 &);
}
// ?_M_create_node@?$_Rb_tree@URva001DD1B3@@U1@U?$_Identity@URva001DD1B3@@@_STL@@U?$less@URva001DD1B3@@@3@V?$allocator@URva001DD1B3@@@3@@_STL@@IAEPAU?$_Rb_tree_node@URva001DD1B3@@@2@ABURva001DD1B3@@@Z
template <>
URva001DD1B3SetTree::_Link_type URva001DD1B3SetTree::_M_create_node(const URva001DD1B3SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<URva001DD1B3SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template URva001DD1B3SetTree::_Link_type URva001DD1B3SetTree::_M_create_node(const URva001DD1B3SetTree::value_type &);
