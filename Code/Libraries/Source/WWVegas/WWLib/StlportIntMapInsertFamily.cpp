// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 _Rb_tree::insert_unique(value) (134 bytes) and _M_insert
// (136 bytes) for int-keyed maps whose pair sits unclaimed in retail, under
// the flags of stlport_map_int_int_os.cpp.  Neither body depends on the mapped
// type beyond the node it creates, so each tree is instantiated with an
// int-like key and a mapped placeholder named after its insert_unique address;
// _M_create_node is pinned at the address each retail _M_insert calls.  The
// first tree is ScienceStore's map<ScienceType, bool>: its insert_unique sits
// beside the map's constructor 0x001FFA00 and _Rb_tree constructor 0x001FF84B
// (ScienceStoreRootPrereqs.cpp), so it keeps those types.  No other identity
// is claimed, except that three mapped types are the LivingWorld AI records
// GatherWorldInformation (0x0050366B) builds and are spelled with their merged
// address-derived names: Rva00501776 (player record, insert 0x00502D61),
// Rva00501656 (region record, insert 0x0050364E) and Rva00501E3FElement
// (army record, insert 0x00501A0B); only their int footprint is declared here.
//
//   insert_unique  _M_insert   _M_create_node
//   0x001FF875     0x001FF791  0x001FF703
//   0x00439AAA     0x00439A22  0x00439943
//   0x004F90FF     0x004F9077  0x004F8CE0
//   0x00502861     0x005027D9  0x00502645
//   0x00502BCD     0x00502B45  0x005028E7
//   0x00559076     0x00558FEE  0x00558E9C
//
// The 0x0032EB87/0x0032EAD6/0x0032EA7F tree is map<int, vector<vector<BfmeE8> > >,
// rowed under that spelling in SidesListCastleBuildLists.cpp.

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

enum ScienceType
{
	SCIENCE_INVALID = -1
};

// Concrete Science memo providers are already owned by verified units.
// Keep these operations out of line instead of emitting conflicting copies.
typedef _STL::pair<const ScienceType, bool> ScienceMemoValue;
typedef _STL::_Rb_tree_base<ScienceMemoValue, _STL::allocator<ScienceMemoValue> > ScienceMemoBase;
typedef _STL::_Rb_tree<ScienceType, ScienceMemoValue, _STL::_Select1st<ScienceMemoValue>, _STL::less<ScienceType>, _STL::allocator<ScienceMemoValue> > ScienceMemoTree;
namespace _STL {
template <> ScienceMemoBase::_Rb_tree_base(const allocator<ScienceMemoValue> &);
template <> ScienceMemoBase::~_Rb_tree_base();
template <> ScienceMemoTree::~_Rb_tree();
template <> void ScienceMemoTree::clear();
template <> ScienceMemoTree::_Link_type ScienceMemoTree::_M_create_node(const ScienceMemoValue &);
}


// The matched _M_create_node target allocates a 0x24-byte tree node. With a
// 0x10-byte node header and the int key this leaves 0x10 bytes for this mapped
// record. Its meaning and field layout remain unknown.
struct Rva00439AAAMapped { unsigned char m_data[0x10]; };
// Mapped sizes below follow the node allocations of the retail _M_create_node
// bodies each _M_insert calls (0x10-byte node header plus the int key).
struct Rva004F90FFMapped { unsigned char m_data[0x0C]; };
struct Rva00501776 { unsigned char m_data[0x2C]; };
// bfme link decl-only Rva00501776
namespace _STL { template <> pair<int const, Rva00501776>::pair(pair<int const, Rva00501776> const &); }
struct Rva00502BCDMapped { unsigned char m_data[0x0C]; };
struct Rva00559076Mapped { unsigned char m_data[0x548]; };

// The player-record tree lifetime and erase bodies have verified providers.
// This insertion unit must not instantiate alternative copies from its
// limited record view. The established insertion members remain unchanged.
typedef _STL::pair<const int, Rva00501776> PlayerRecordTreeValue;
typedef _STL::_Rb_tree<int, PlayerRecordTreeValue, _STL::_Select1st<PlayerRecordTreeValue>,
 _STL::less<int>, _STL::allocator<PlayerRecordTreeValue> > PlayerRecordTree;
namespace _STL {
template <> PlayerRecordTree::~_Rb_tree();
template <> void PlayerRecordTree::clear();
template <> void PlayerRecordTree::_M_erase(PlayerRecordTree::_Link_type);
}


struct Rva004395EC;
namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
template <> void _Construct<Rva004395EC, Rva004395EC>(Rva004395EC *, const Rva004395EC &);
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00439AAAMapped>,
	_STL::_Select1st<_STL::pair<const int, Rva00439AAAMapped> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > > Rva00439AAATree;

// Target 0x00439943 allocates a 0x24-byte node through the rowed byte
// allocator and calls rowed _Construct<Rva004395EC> 0x004398AB on the value
// storage. Its 34B boundary and the int-keyed _M_insert caller 0x00439A22
// support a 0x10-byte mapped record; the mapped type's name and members remain
// unresolved. The target treats the pair storage as the rowed 20-byte record
// view solely for the already-proven copy operation.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00439AAAMapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@2@ABU?$pair@$$CBHURva00439AAAMapped@@@2@@Z
template <>
Rva00439AAATree::_Link_type Rva00439AAATree::_M_create_node(const Rva00439AAATree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva00439AAATree::value_type>), 0);
	_STL::_Construct((Rva004395EC *)&node->_M_value_field, (const Rva004395EC &)value);
	return node;
}

template Rva00439AAATree::_Link_type Rva00439AAATree::_M_create_node(const Rva00439AAATree::value_type &);

// The other int-keyed trees' node factories have the same 34-byte shape (37 for
// the 0x55C-byte node): byte allocator 0x000307F0, then the rowed copy helper on
// the value storage. Their callees are spelled by their row names.
struct Rva004F868AElement;
struct Rva00502667Element;
struct Rva00557C90Element;
namespace _STL {
template <> void _Construct<Rva004F868AElement, Rva004F868AElement>(Rva004F868AElement *, const Rva004F868AElement &);
template <> void _Construct<Rva00502667Element, Rva00502667Element>(Rva00502667Element *, const Rva00502667Element &);
template <> void _Construct<Rva00557C90Element, Rva00557C90Element>(Rva00557C90Element *, const Rva00557C90Element &);
template <> void _Construct<pair<const int, Rva00501776>, pair<const int, Rva00501776> >(pair<const int, Rva00501776> *, const pair<const int, Rva00501776> &);
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva004F90FFMapped>, _STL::_Select1st<_STL::pair<const int, Rva004F90FFMapped> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004F90FFMapped> > > Rva004F90FFTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00502BCDMapped>, _STL::_Select1st<_STL::pair<const int, Rva00502BCDMapped> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502BCDMapped> > > Rva00502BCDTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00559076Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00559076Mapped> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00559076Mapped> > > Rva00559076Tree;

// 0x00502645: 0x40-byte node, copy helper 0x00502082.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00501776@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501776@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501776@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00501776@@@_STL@@@2@ABU?$pair@$$CBHURva00501776@@@2@@Z
template <>
PlayerRecordTree::_Link_type PlayerRecordTree::_M_create_node(const PlayerRecordTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<PlayerRecordTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}

// 0x004F8CE0: 0x20-byte node, copy helper 0x004F868A.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva004F90FFMapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva004F90FFMapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva004F90FFMapped@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva004F90FFMapped@@@_STL@@@2@ABU?$pair@$$CBHURva004F90FFMapped@@@2@@Z
template <>
Rva004F90FFTree::_Link_type Rva004F90FFTree::_M_create_node(const Rva004F90FFTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva004F90FFTree::value_type>), 0);
	_STL::_Construct((Rva004F868AElement *)&node->_M_value_field, (const Rva004F868AElement &)value);
	return node;
}

// 0x005028E7: 0x20-byte node, copy helper 0x00502667.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00502BCDMapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00502BCDMapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00502BCDMapped@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00502BCDMapped@@@_STL@@@2@ABU?$pair@$$CBHURva00502BCDMapped@@@2@@Z
template <>
Rva00502BCDTree::_Link_type Rva00502BCDTree::_M_create_node(const Rva00502BCDTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva00502BCDTree::value_type>), 0);
	_STL::_Construct((Rva00502667Element *)&node->_M_value_field, (const Rva00502667Element &)value);
	return node;
}

// 0x00558E9C: 0x55C-byte node, copy helper 0x00557C90.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00559076Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@2@ABU?$pair@$$CBHURva00559076Mapped@@@2@@Z
template <>
Rva00559076Tree::_Link_type Rva00559076Tree::_M_create_node(const Rva00559076Tree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva00559076Tree::value_type>), 0);
	_STL::_Construct((Rva00557C90Element *)&node->_M_value_field, (const Rva00557C90Element &)value);
	return node;
}

template class _STL::_Rb_tree<ScienceType, _STL::pair<const ScienceType, bool>, _STL::_Select1st<_STL::pair<const ScienceType, bool> >, _STL::less<ScienceType>, _STL::allocator<_STL::pair<const ScienceType, bool> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00439AAAMapped>, _STL::_Select1st<_STL::pair<const int, Rva00439AAAMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva004F90FFMapped>, _STL::_Select1st<_STL::pair<const int, Rva004F90FFMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004F90FFMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00501776>, _STL::_Select1st<_STL::pair<const int, Rva00501776> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501776> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502BCDMapped>, _STL::_Select1st<_STL::pair<const int, Rva00502BCDMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502BCDMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00559076Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00559076Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00559076Mapped> > >;

// Multimap trees: insert_equal(value) (59 bytes) and insert_equal(hint,
// value) (250 bytes) over the same int-keyed _M_insert shape, three more
// trees whose bodies sit unclaimed; mapped placeholders are named after the
// insert_equal address and _M_create_node is pinned per tree.
//
//   insert_equal  hint        _M_insert   _M_create_node
//   0x002F1DA1    -           0x002F0D4E  0x002EF239
//   0x00501130    0x00501374  0x005010A8  0x00501086
//   0x00502FAE    0x00503554  0x00502F26  0x00502EA4

struct Rva002F1DA1Mapped { int a; };
struct Rva00501E3FElement { int a; };
struct Rva00501656 { unsigned char m_data[0x58]; };
// bfme link decl-only Rva00501656
namespace _STL { template <> pair<int const, Rva00501656>::pair(pair<int const, Rva00501656> const &); }
// Region-tree destruction is owned by the verified destructor-only unit.
typedef _STL::pair<const int, Rva00501656> RegionRecordTreeValue;
typedef _STL::_Rb_tree<int, RegionRecordTreeValue, _STL::_Select1st<RegionRecordTreeValue>,
 _STL::less<int>, _STL::allocator<RegionRecordTreeValue> > RegionRecordTree;
namespace _STL { template <> RegionRecordTree::~_Rb_tree(); }

namespace _STL { template <> void _Construct<pair<const int, Rva00501656>, pair<const int, Rva00501656> >(pair<const int, Rva00501656> *, const pair<const int, Rva00501656> &); }
// 0x00502EA4: 0x6C-byte node, copy helper 0x00502C53.
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00501656@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501656@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501656@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00501656@@@_STL@@@2@ABU?$pair@$$CBHURva00501656@@@2@@Z
template <>
RegionRecordTree::_Link_type RegionRecordTree::_M_create_node(const RegionRecordTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<RegionRecordTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}

// The ScienceType, 0x002F1DA1 and army-record node factories, and the
// army-record tree's copy members, are rowed in their own units (0x001FF703,
// 0x002EF239, 0x00501086; _M_copy 0x00501CFE, pair copy 0x00500856, _Construct
// 0x00500CD1); this unit only calls them. The army-record node allocator folds
// onto the 40-byte allocate 0x000B4039 and its _Rb_tree_base constructor is
// emitted by the copy-constructor units.
typedef _STL::pair<const int, Rva002F1DA1Mapped> Rva002F1DA1Value;
typedef _STL::_Rb_tree<int, Rva002F1DA1Value, _STL::_Select1st<Rva002F1DA1Value>, _STL::less<int>, _STL::allocator<Rva002F1DA1Value> > Rva002F1DA1Tree;
typedef _STL::pair<const int, Rva00501E3FElement> ArmyRecordValue;
typedef _STL::_Rb_tree<int, ArmyRecordValue, _STL::_Select1st<ArmyRecordValue>, _STL::less<int>, _STL::allocator<ArmyRecordValue> > ArmyRecordTree;
namespace _STL {
template <> Rva002F1DA1Tree::_Link_type Rva002F1DA1Tree::_M_create_node(const Rva002F1DA1Value &);
template <> ArmyRecordTree::_Link_type ArmyRecordTree::_M_create_node(const ArmyRecordValue &);
template <> ArmyRecordTree::_Link_type ArmyRecordTree::_M_copy(ArmyRecordTree::_Link_type, ArmyRecordTree::_Link_type);
template <> _Rb_tree_base<ArmyRecordValue, allocator<ArmyRecordValue> >::_Rb_tree_base(const allocator<ArmyRecordValue> &);
template <> _Rb_tree_node<ArmyRecordValue> *allocator<_Rb_tree_node<ArmyRecordValue> >::allocate(size_t, const void *) const;
template <> pair<const int, Rva00501E3FElement>::pair(const pair<const int, Rva00501E3FElement> &);
template <> void _Construct<ArmyRecordValue, ArmyRecordValue>(ArmyRecordValue *, const ArmyRecordValue &);
}

template class _STL::_Rb_tree<int, _STL::pair<const int, Rva002F1DA1Mapped>, _STL::_Select1st<_STL::pair<const int, Rva002F1DA1Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva002F1DA1Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00501E3FElement>, _STL::_Select1st<_STL::pair<const int, Rva00501E3FElement> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501E3FElement> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00501656>, _STL::_Select1st<_STL::pair<const int, Rva00501656> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501656> > >;

// map::insert(hint) forwarders @0x00502D61 and @0x00502F09 (29B) over the insert_unique rows above.
template _STL::map<int, Rva00501776>::iterator _STL::map<int, Rva00501776>::insert(_STL::map<int, Rva00501776>::iterator, const _STL::map<int, Rva00501776>::value_type &);
template _STL::map<int, Rva00502BCDMapped>::iterator _STL::map<int, Rva00502BCDMapped>::insert(_STL::map<int, Rva00502BCDMapped>::iterator, const _STL::map<int, Rva00502BCDMapped>::value_type &);
// multimap::insert(hint) forwarder @0x00501A0B (29B) over the insert_equal row above.
template _STL::multimap<int, Rva00501E3FElement>::iterator _STL::multimap<int, Rva00501E3FElement>::insert(_STL::multimap<int, Rva00501E3FElement>::iterator, const _STL::multimap<int, Rva00501E3FElement>::value_type &);
// map::insert(hint) @0x004F9ED6 and multimap::insert(hint) @0x0050364E (29B each).
template _STL::map<int, Rva004F90FFMapped>::iterator _STL::map<int, Rva004F90FFMapped>::insert(_STL::map<int, Rva004F90FFMapped>::iterator, const _STL::map<int, Rva004F90FFMapped>::value_type &);
template _STL::multimap<int, Rva00501656>::iterator _STL::multimap<int, Rva00501656>::insert(_STL::multimap<int, Rva00501656>::iterator, const _STL::multimap<int, Rva00501656>::value_type &);
// multimap::insert(value) @0x002F3052 (20B): forwards straight to the 0x002F1DA1 insert_equal row above.
template _STL::multimap<int, Rva002F1DA1Mapped>::iterator _STL::multimap<int, Rva002F1DA1Mapped>::insert(const _STL::multimap<int, Rva002F1DA1Mapped>::value_type &);

typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00501776>,

	_STL::_Select1st<_STL::pair<const int, Rva00501776> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501776> > > Rva00501776Tree;

class Rva00502CF9
{
public:
	void rva00502CF9();
};

void Rva00502CF9::rva00502CF9()
{
	((Rva00501776Tree *)this)->Rva00501776Tree::~_Rb_tree();
}

class Rva0050298D
{
public:
	~Rva0050298D();
};

class Rva00502CFE
{
public:
	void rva00502CFE();
};

void Rva00502CFE::rva00502CFE()
{
	((Rva0050298D *)this)->~Rva0050298D();
}

