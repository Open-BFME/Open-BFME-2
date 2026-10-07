// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Batch _M_create_node family recovery (generated): one explicit
// specialization per sibling, each proven by its own retail call
// displacement to a rowed _Construct plus the allocate size fixing
// the value size. Custom No-exceptions MALLOC shape from
// stlport_rb_tree_hint_asciistring_set (no allocation-cleanup catch
// path); each _Construct is declared only so its call resolves
// through its own row.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>
#include <list>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct TreeKey00242F5E { public: unsigned char m_data[8]; };
struct BfmeRecord001DD3BC { public: unsigned char m_data[8]; };
class Rva0033A4F0 { public: unsigned char m_data[12]; };
struct BfmeStringRecord002049D6 { public: unsigned char m_data[12]; };
struct BfmeStringRecord004071F7 { public: unsigned char m_data[12]; };
struct BfmeE16 { float x, y, z, w; };
struct BfmePod16 { int a[4]; };
struct Rva00204B12 { public: unsigned char m_data[16]; };
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
struct BfmePod52 { int a[13]; };
struct BfmeStringRecord00448113 { public: unsigned char m_data[8]; };
struct BfmeStringRecord004D05B8 { public: unsigned char m_data[8]; };
class Rva00064640Record { public: unsigned char m_data[28]; };

// ?_M_create_node@?$_Rb_tree@UTreeKey00242F5E@@U1@U?$_Identity@UTreeKey00242F5E@@@_STL@@U?$less@UTreeKey00242F5E@@@3@V?$allocator@UTreeKey00242F5E@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UTreeKey00242F5E@@@2@ABUTreeKey00242F5E@@@Z
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, _STL::less<TreeKey00242F5E>, _STL::allocator<TreeKey00242F5E> > UTreeKey00242F5ESetTree;
namespace _STL {
template <> void _Construct<TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
}
template <>
UTreeKey00242F5ESetTree::_Link_type UTreeKey00242F5ESetTree::_M_create_node(const UTreeKey00242F5ESetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UTreeKey00242F5ESetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UTreeKey00242F5ESetTree::_Link_type UTreeKey00242F5ESetTree::_M_create_node(const UTreeKey00242F5ESetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeRecord001DD3BC@@U1@U?$_Identity@UBfmeRecord001DD3BC@@@_STL@@U?$less@UBfmeRecord001DD3BC@@@3@V?$allocator@UBfmeRecord001DD3BC@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeRecord001DD3BC@@@2@ABUBfmeRecord001DD3BC@@@Z
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > UBfmeRecord001DD3BCSetTree;
namespace _STL {
template <> void _Construct<BfmeRecord001DD3BC>(BfmeRecord001DD3BC *, const BfmeRecord001DD3BC &);
}
template <>
UBfmeRecord001DD3BCSetTree::_Link_type UBfmeRecord001DD3BCSetTree::_M_create_node(const UBfmeRecord001DD3BCSetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeRecord001DD3BCSetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeRecord001DD3BCSetTree::_Link_type UBfmeRecord001DD3BCSetTree::_M_create_node(const UBfmeRecord001DD3BCSetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@VRva0033A4F0@@V1@U?$_Identity@VRva0033A4F0@@@_STL@@U?$less@VRva0033A4F0@@@3@V?$allocator@VRva0033A4F0@@@3@@_STL@@IAEPAU?$_Rb_tree_node@VRva0033A4F0@@@2@ABVRva0033A4F0@@@Z
typedef _STL::_Rb_tree<Rva0033A4F0, Rva0033A4F0, _STL::_Identity<Rva0033A4F0>, _STL::less<Rva0033A4F0>, _STL::allocator<Rva0033A4F0> > VRva0033A4F0SetTree;
namespace _STL {
template <> void _Construct<Rva0033A4F0>(Rva0033A4F0 *, const Rva0033A4F0 &);
}
template <>
VRva0033A4F0SetTree::_Link_type VRva0033A4F0SetTree::_M_create_node(const VRva0033A4F0SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<VRva0033A4F0SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template VRva0033A4F0SetTree::_Link_type VRva0033A4F0SetTree::_M_create_node(const VRva0033A4F0SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeStringRecord002049D6@@U1@U?$_Identity@UBfmeStringRecord002049D6@@@_STL@@U?$less@UBfmeStringRecord002049D6@@@3@V?$allocator@UBfmeStringRecord002049D6@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord002049D6@@@2@ABUBfmeStringRecord002049D6@@@Z
typedef _STL::_Rb_tree<BfmeStringRecord002049D6, BfmeStringRecord002049D6, _STL::_Identity<BfmeStringRecord002049D6>, _STL::less<BfmeStringRecord002049D6>, _STL::allocator<BfmeStringRecord002049D6> > UBfmeStringRecord002049D6SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord002049D6>(BfmeStringRecord002049D6 *, const BfmeStringRecord002049D6 &);
}
template <>
UBfmeStringRecord002049D6SetTree::_Link_type UBfmeStringRecord002049D6SetTree::_M_create_node(const UBfmeStringRecord002049D6SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeStringRecord002049D6SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeStringRecord002049D6SetTree::_Link_type UBfmeStringRecord002049D6SetTree::_M_create_node(const UBfmeStringRecord002049D6SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeStringRecord004071F7@@U1@U?$_Identity@UBfmeStringRecord004071F7@@@_STL@@U?$less@UBfmeStringRecord004071F7@@@3@V?$allocator@UBfmeStringRecord004071F7@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord004071F7@@@2@ABUBfmeStringRecord004071F7@@@Z
typedef _STL::_Rb_tree<BfmeStringRecord004071F7, BfmeStringRecord004071F7, _STL::_Identity<BfmeStringRecord004071F7>, _STL::less<BfmeStringRecord004071F7>, _STL::allocator<BfmeStringRecord004071F7> > UBfmeStringRecord004071F7SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord004071F7>(BfmeStringRecord004071F7 *, const BfmeStringRecord004071F7 &);
}
template <>
UBfmeStringRecord004071F7SetTree::_Link_type UBfmeStringRecord004071F7SetTree::_M_create_node(const UBfmeStringRecord004071F7SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeStringRecord004071F7SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeStringRecord004071F7SetTree::_Link_type UBfmeStringRecord004071F7SetTree::_M_create_node(const UBfmeStringRecord004071F7SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeE16@@U1@U?$_Identity@UBfmeE16@@@_STL@@U?$less@UBfmeE16@@@3@V?$allocator@UBfmeE16@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeE16@@@2@ABUBfmeE16@@@Z
typedef _STL::_Rb_tree<BfmeE16, BfmeE16, _STL::_Identity<BfmeE16>, _STL::less<BfmeE16>, _STL::allocator<BfmeE16> > UBfmeE16SetTree;
namespace _STL {
template <> void _Construct<BfmeE16>(BfmeE16 *, const BfmeE16 &);
}
template <>
UBfmeE16SetTree::_Link_type UBfmeE16SetTree::_M_create_node(const UBfmeE16SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeE16SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeE16SetTree::_Link_type UBfmeE16SetTree::_M_create_node(const UBfmeE16SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod16@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod16@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod16@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod16@@@_STL@@@2@ABU?$pair@$$CBHUBfmePod16@@@2@@Z
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod16>, _STL::_Select1st<_STL::pair<const int, BfmePod16> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod16> > > HUBfmePod16MapTree;
namespace _STL {
template <> void _Construct<_STL::pair<const int, BfmePod16> >(_STL::pair<const int, BfmePod16> *, const _STL::pair<const int, BfmePod16> &);
}
template <>
HUBfmePod16MapTree::_Link_type HUBfmePod16MapTree::_M_create_node(const HUBfmePod16MapTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<HUBfmePod16MapTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template HUBfmePod16MapTree::_Link_type HUBfmePod16MapTree::_M_create_node(const HUBfmePod16MapTree::value_type &);

// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod24@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod24@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod24@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod24@@@_STL@@@2@ABU?$pair@$$CBHUBfmePod24@@@2@@Z
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > HUBfmePod24MapTree;
namespace _STL {
template <> void _Construct<_STL::pair<const int, BfmePod24> >(_STL::pair<const int, BfmePod24> *, const _STL::pair<const int, BfmePod24> &);
}
template <>
HUBfmePod24MapTree::_Link_type HUBfmePod24MapTree::_M_create_node(const HUBfmePod24MapTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<HUBfmePod24MapTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template HUBfmePod24MapTree::_Link_type HUBfmePod24MapTree::_M_create_node(const HUBfmePod24MapTree::value_type &);

// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod52>, _STL::_Select1st<_STL::pair<const int, BfmePod52> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > > HUBfmePod52MapTree;
namespace _STL {
template <> void _Construct<_STL::pair<const int, BfmePod52> >(_STL::pair<const int, BfmePod52> *, const _STL::pair<const int, BfmePod52> &);
}
template <>
HUBfmePod52MapTree::_Link_type HUBfmePod52MapTree::_M_create_node(const HUBfmePod52MapTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<HUBfmePod52MapTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template HUBfmePod52MapTree::_Link_type HUBfmePod52MapTree::_M_create_node(const HUBfmePod52MapTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeStringRecord00448113@@U1@U?$_Identity@UBfmeStringRecord00448113@@@_STL@@U?$less@UBfmeStringRecord00448113@@@3@V?$allocator@UBfmeStringRecord00448113@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord00448113@@@2@ABUBfmeStringRecord00448113@@@Z
typedef _STL::_Rb_tree<BfmeStringRecord00448113, BfmeStringRecord00448113, _STL::_Identity<BfmeStringRecord00448113>, _STL::less<BfmeStringRecord00448113>, _STL::allocator<BfmeStringRecord00448113> > UBfmeStringRecord00448113SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord00448113>(BfmeStringRecord00448113 *, const BfmeStringRecord00448113 &);
}
template <>
UBfmeStringRecord00448113SetTree::_Link_type UBfmeStringRecord00448113SetTree::_M_create_node(const UBfmeStringRecord00448113SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeStringRecord00448113SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeStringRecord00448113SetTree::_Link_type UBfmeStringRecord00448113SetTree::_M_create_node(const UBfmeStringRecord00448113SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@GU?$pair@$$CBGE@_STL@@U?$_Select1st@U?$pair@$$CBGE@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGE@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBGE@_STL@@@2@ABU?$pair@$$CBGE@2@@Z
typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, unsigned char>, _STL::_Select1st<_STL::pair<const unsigned short, unsigned char> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, unsigned char> > > GEMapTree;
namespace _STL {
template <> void _Construct<_STL::pair<const unsigned short, unsigned char> >(_STL::pair<const unsigned short, unsigned char> *, const _STL::pair<const unsigned short, unsigned char> &);
}
template <>
GEMapTree::_Link_type GEMapTree::_M_create_node(const GEMapTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<GEMapTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template GEMapTree::_Link_type GEMapTree::_M_create_node(const GEMapTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmeStringRecord004D05B8@@U1@U?$_Identity@UBfmeStringRecord004D05B8@@@_STL@@U?$less@UBfmeStringRecord004D05B8@@@3@V?$allocator@UBfmeStringRecord004D05B8@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord004D05B8@@@2@ABUBfmeStringRecord004D05B8@@@Z
typedef _STL::_Rb_tree<BfmeStringRecord004D05B8, BfmeStringRecord004D05B8, _STL::_Identity<BfmeStringRecord004D05B8>, _STL::less<BfmeStringRecord004D05B8>, _STL::allocator<BfmeStringRecord004D05B8> > UBfmeStringRecord004D05B8SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord004D05B8>(BfmeStringRecord004D05B8 *, const BfmeStringRecord004D05B8 &);
}
template <>
UBfmeStringRecord004D05B8SetTree::_Link_type UBfmeStringRecord004D05B8SetTree::_M_create_node(const UBfmeStringRecord004D05B8SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmeStringRecord004D05B8SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmeStringRecord004D05B8SetTree::_Link_type UBfmeStringRecord004D05B8SetTree::_M_create_node(const UBfmeStringRecord004D05B8SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@VRva00064640Record@@V1@U?$_Identity@VRva00064640Record@@@_STL@@U?$less@VRva00064640Record@@@3@V?$allocator@VRva00064640Record@@@3@@_STL@@IAEPAU?$_Rb_tree_node@VRva00064640Record@@@2@ABVRva00064640Record@@@Z
typedef _STL::_Rb_tree<Rva00064640Record, Rva00064640Record, _STL::_Identity<Rva00064640Record>, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > VRva00064640RecordSetTree;
namespace _STL {
template <> void _Construct<Rva00064640Record>(Rva00064640Record *, const Rva00064640Record &);
}
template <>
VRva00064640RecordSetTree::_Link_type VRva00064640RecordSetTree::_M_create_node(const VRva00064640RecordSetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<VRva00064640RecordSetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template VRva00064640RecordSetTree::_Link_type VRva00064640RecordSetTree::_M_create_node(const VRva00064640RecordSetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@UBfmePod20@@U1@U?$_Identity@UBfmePod20@@@_STL@@U?$less@UBfmePod20@@@3@V?$allocator@UBfmePod20@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmePod20@@@2@ABUBfmePod20@@@Z
// retail 0x004AF2BC, 34 bytes. _Rb_tree::_M_create_node for a 20-byte set value:
// allocates a 0x24 node (16-byte links plus 20-byte BfmePod20) through the rowed
// byte allocator at 0x307F0, then constructs the value through the rowed
// BfmePod20 _Construct at 0x4FDAEE. Node size fixes the 20-byte value; the
// _Construct call displacement proves the BfmePod20 spelling. Called twice by
// the RespawnRule tree _M_insert at 0x4AF3E6.
typedef _STL::_Rb_tree<BfmePod20, BfmePod20, _STL::_Identity<BfmePod20>, _STL::less<BfmePod20>, _STL::allocator<BfmePod20> > UBfmePod20SetTree;
namespace _STL {
template <> void _Construct<BfmePod20>(BfmePod20 *, const BfmePod20 &);
}
template <>
UBfmePod20SetTree::_Link_type UBfmePod20SetTree::_M_create_node(const UBfmePod20SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UBfmePod20SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template UBfmePod20SetTree::_Link_type UBfmePod20SetTree::_M_create_node(const UBfmePod20SetTree::value_type &);

// ?_M_create_node@?$_Rb_tree@URva00204B12@@U1@U?$_Identity@URva00204B12@@@_STL@@U?$less@URva00204B12@@@3@V?$allocator@URva00204B12@@@3@@_STL@@IAEPAU?$_Rb_tree_node@URva00204B12@@@2@ABURva00204B12@@@Z
// retail 0x00206C10, 34 bytes. _Rb_tree::_M_create_node for a 16-byte set value:
// allocates a 0x20 node (16-byte links plus 16-byte Rva00204B12) through the rowed
// byte allocator at 0x307F0, then constructs the value through the rowed
// Rva00204B12 _Construct at 0x205889. Node size fixes the 16-byte value; the
// _Construct call displacement proves the Rva00204B12 spelling. Called twice by
// the 148B tree _M_insert at 0x207187.
typedef _STL::_Rb_tree<Rva00204B12, Rva00204B12, _STL::_Identity<Rva00204B12>, _STL::less<Rva00204B12>, _STL::allocator<Rva00204B12> > URva00204B12SetTree;
namespace _STL {
template <> void _Construct<Rva00204B12>(Rva00204B12 *, const Rva00204B12 &);
}
template <>
URva00204B12SetTree::_Link_type URva00204B12SetTree::_M_create_node(const URva00204B12SetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<URva00204B12SetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template URva00204B12SetTree::_Link_type URva00204B12SetTree::_M_create_node(const URva00204B12SetTree::value_type &);

// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x00417B9B), _M_clone_node (retail 0x00417DDD)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,BfmePod24>,_STL::_Select1st<_STL::pair<int const ,BfmePod24> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,BfmePod24> > >;

// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x00426016)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,BfmePod52>,_STL::_Select1st<_STL::pair<int const ,BfmePod52> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,BfmePod52> > >;

// ?rva00417DFB@Rva00417DFB@@QAEXPAVINI@@PAX@Z @0x00417DFB 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and its twins. The worker is the rowed
// 0x00417C23 single-token worker; Append, Tok, INI and the empty string
// mirror the prototype TU (undefined externals).
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr00417DFB(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class Rva00417C23
{
public:
	bool rva00417C23(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva00417DFB : public Rva00417C23
{
public:
	void rva00417DFB(INI *ini, void *extra);
	void rva00417DFBAppend(const char *s, Rva0033B84ETok *b);
};

void Rva00417DFB::rva00417DFB(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr00417DFB(part);
				rva00417DFBAppend(s, accum);
				if (!rva00417C23(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva00417DFBAppend(token, accum);
			if (!rva00417C23(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}

class Rva004D0545
{
public:
	~Rva004D0545();
};

class Rva004D0572
{
public:
	~Rva004D0572();
};

class Rva004D1D2D
{
public:
	void rva004D1D2D();
};

void Rva004D1D2D::rva004D1D2D()
{
	((Rva004D0545 *)this)->~Rva004D0545();
}

class Rva004D1D32
{
public:
	void rva004D1D32();
};

void Rva004D1D32::rva004D1D32()
{
	((Rva004D0572 *)this)->~Rva004D0572();
}

