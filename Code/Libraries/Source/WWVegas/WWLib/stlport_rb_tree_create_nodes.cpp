// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /O1 /arch:SSE /G7
// stlport
// Batch _M_create_node family recovery (generated): one explicit
// specialization per sibling, each proven by its own retail call
// displacement to a rowed _Construct plus the allocate size fixing
// the value size. Custom No-exceptions MALLOC shape from
// stlport_rb_tree_hint_asciistring_set (no allocation-cleanup catch
// path); each _Construct is declared only so its call resolves
// through its own row.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

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
struct BfmeStringRecord004071F7 { public: unsigned char m_data[12]; };
#include "../../../Include/Lib/BfmeE16.h"
struct BfmePod16 { int a[4]; };
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
struct BfmePod52 { int a[13]; };
// The rowed ~_Rb_tree (stlport_map_int_pod52_tree_dtor.cpp, 0x00425FB4) resets the
// EH state before freeing the header; this unit's copy did not. Bind to it.
namespace _STL { template <> _Rb_tree<int, pair<const int, BfmePod52>, _Select1st<pair<const int, BfmePod52> >, less<int>, allocator<pair<const int, BfmePod52> > >::~_Rb_tree(); }
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


// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x00417B9B), _M_clone_node (retail 0x00417DDD)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,BfmePod24>,_STL::_Select1st<_STL::pair<int const ,BfmePod24> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,BfmePod24> > >;

// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x00426016)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,BfmePod52>,_STL::_Select1st<_STL::pair<int const ,BfmePod52> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,BfmePod52> > >;

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeE16, BfmeE16>(BfmeE16 *, BfmeE16 const &); }
namespace _STL { template <> _Rb_tree_base<pair<int const, BfmePod24>, allocator<pair<int const, BfmePod24> > >::_Rb_tree_base(allocator<pair<int const, BfmePod24> > const &); }
// bfme link decl-only end

// ?rva00417DFB@Rva00417DFB@@QAEXPAVINI@@PAX@Z @0x00417DFB 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and its twins. The worker is the rowed
// 0x00417C23 single-token worker.
// The join-append is the shared Rva0049B6AE::append member (rowed, body
// ignores ecx); the string temporaries are the canonical AsciiString.
#include "../../../../GameEngine/Include/Common/INI/INI.h"

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

__forceinline const char *GetStr00417DFB(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
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
};

void Rva00417DFB::rva00417DFB(INI *ini, void *extra)
{
	AsciiString *accum = (AsciiString *)extra;
	if (accum != 0)
		accum->clear();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			AsciiString tmp(token);
			AsciiString part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr00417DFB(part);
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!rva00417C23(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva00417C23(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}

#include "../../../../GameEngine/Include/Common/Rva004D0545.h"

class Rva004D1D2D
{
public:
	void rva004D1D2D();
};

void Rva004D1D2D::rva004D1D2D()
{
	((Rva004D0545 *)this)->~Rva004D0545();
}
