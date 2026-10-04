// ?_M_insert@?$_Rb_tree@UBfmeStringRecord004071F7@@U1@U?$_Identity@UBfmeStringRecord004071F7@@@_STL@@URecordNocaseLess@@V?$allocator@UBfmeStringRecord004071F7@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@UBfmeStringRecord004071F7@@U?$_Nonconst_traits@UBfmeStringRecord004071F7@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABUBfmeStringRecord004071F7@@0@Z @ 0x003ED70D (149B).
// Finish from banked 0.98 stash reverse/attempts/0x003ed70d.cpp via out-of-line nocase compare; retail lea ecx edi+8 proves thiscall compare at 0x0002C63C and RecordNocaseLess create_node twin at 0x003ED6C2 plus rowed Rebalance 0x00025490.
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include "ascii_string.h"
struct BfmeStringRecord004071F7 { AsciiString key; char payload[8]; };
struct RecordNocaseLess {
    bool operator()(const BfmeStringRecord004071F7 &a, const BfmeStringRecord004071F7 &b) const;
};
typedef _STL::_Rb_tree<BfmeStringRecord004071F7, BfmeStringRecord004071F7, _STL::_Identity<BfmeStringRecord004071F7>, RecordNocaseLess, _STL::allocator<BfmeStringRecord004071F7> > TestTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
namespace _STL {
template <> void _Construct<BfmeStringRecord004071F7>(BfmeStringRecord004071F7 *, const BfmeStringRecord004071F7 &);
}
// ?_M_create_node@?$_Rb_tree@UBfmeStringRecord004071F7@@U1@U?$_Identity@UBfmeStringRecord004071F7@@@_STL@@URecordNocaseLess@@V?$allocator@UBfmeStringRecord004071F7@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord004071F7@@@2@ABUBfmeStringRecord004071F7@@@Z present-unmatched
template <>
TestTree::_Link_type TestTree::_M_create_node(const TestTree::value_type &value)
{
	TestTree::_Link_type node = (TestTree::_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TestTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template TestTree::_Link_type TestTree::_M_create_node(const TestTree::value_type &);
template _STL::pair<TestTree::iterator, bool> TestTree::insert_unique(const TestTree::value_type &);
