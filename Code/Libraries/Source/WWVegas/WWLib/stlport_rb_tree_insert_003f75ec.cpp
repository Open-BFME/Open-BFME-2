// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// STLport 4.5.3 _M_insert, specialized to the retail 0x003F75EC tree.
// Target: Ghidra 0x003F75EC/136; sole direct caller 0x003F76B1/134
// traverses with signed greater-than at value +0 and node +0x10.
// Node creator 0x003F753F allocates 0x20 and copies 16 value bytes.
// The adjacent equality body 0x003F7561 compares float payloads at
// node +0x14/+0x18/+0x1C and an integer key at +0x10. These fields
// are target evidence; the original application type and tree name
// remain unknown. The record/key-extractor names below are stand-ins.
// Donor: vendor/stlport/stl/_tree.c, _M_insert and insert_unique.
#include <map>
struct Rva003F75ECValue {
    int key;
    float x, y, z;
};
struct Rva003F75ECKey {
    const int &operator()(const Rva003F75ECValue &v) const { return v.key; }
};
typedef _STL::_Rb_tree<int, Rva003F75ECValue, Rva003F75ECKey,
    _STL::greater<int>, _STL::allocator<Rva003F75ECValue> > Rva003F75ECTree;
// The separately compiled creator is byte-identical to retail's rowed
// 0x003F753F provider. Declare it here to preserve the retail call ABI.
template <> Rva003F75ECTree::_Link_type
Rva003F75ECTree::_M_create_node(const Rva003F75ECTree::value_type &);

// ?_M_insert@?$_Rb_tree@HURva003F75ECValue@@URva003F75ECKey@@U?$greater@H@_STL@@V?$allocator@URva003F75ECValue@@@4@@_STL@@AAE?AU?$_Rb_tree_iterator@URva003F75ECValue@@U?$_Nonconst_traits@URva003F75ECValue@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABURva003F75ECValue@@0@Z
template Rva003F75ECTree::iterator Rva003F75ECTree::_M_insert(
    _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
    const Rva003F75ECTree::value_type &, _STL::_Rb_tree_node_base *);

// Both creators compile to the same 34-byte body and call the same
// verified 21-byte trivial construction at 0x0059CE9E. Resolve the
// typed declaration to the existing provider when linking.
#pragma comment(linker, "/alternatename:?_M_create_node@?$_Rb_tree@HURva003F75ECValue@@URva003F75ECKey@@U?$greater@H@_STL@@V?$allocator@URva003F75ECValue@@@4@@_STL@@IAEPAU?$_Rb_tree_node@URva003F75ECValue@@@2@ABURva003F75ECValue@@@Z=?_M_create_node@?$_Rb_tree@UBfmeE16@@U1@U?$_Identity@UBfmeE16@@@_STL@@U?$less@UBfmeE16@@@3@V?$allocator@UBfmeE16@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeE16@@@2@ABUBfmeE16@@@Z")

// 0x003F76B1/134 is the sole caller of the rowed _M_insert. The
// target loop compares the signed key in descending order and returns
// the iterator and insertion flag through the caller's result pointer.
template _STL::pair<Rva003F75ECTree::iterator, bool> Rva003F75ECTree::insert_unique(const Rva003F75ECTree::value_type &);
