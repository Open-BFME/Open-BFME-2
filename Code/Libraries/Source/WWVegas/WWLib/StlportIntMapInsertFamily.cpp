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
// is claimed.
//
//   insert_unique  _M_insert   _M_create_node
//   0x001FF875     0x001FF791  0x001FF703
//   0x0032EB87     0x0032EAD6  0x0032EA7F
//   0x00439AAA     0x00439A22  0x00439943
//   0x004F90FF     0x004F9077  0x004F8CE0
//   0x00502861     0x005027D9  0x00502645
//   0x00502BCD     0x00502B45  0x005028E7
//   0x00559076     0x00558FEE  0x00558E9C

#include <map>

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
}


struct Rva0032EB87Mapped { int a; };
// The matched _M_create_node target allocates a 0x24-byte tree node. With a
// 0x10-byte node header and the int key this leaves 0x10 bytes for this mapped
// record. Its meaning and field layout remain unknown.
struct Rva00439AAAMapped { unsigned char m_data[0x10]; };
struct Rva004F90FFMapped { int a; };
struct Rva00502861Mapped { int a; };
struct Rva00502BCDMapped { int a; };
struct Rva00559076Mapped { int a; };

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

template class _STL::_Rb_tree<ScienceType, _STL::pair<const ScienceType, bool>, _STL::_Select1st<_STL::pair<const ScienceType, bool> >, _STL::less<ScienceType>, _STL::allocator<_STL::pair<const ScienceType, bool> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva0032EB87Mapped>, _STL::_Select1st<_STL::pair<const int, Rva0032EB87Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva0032EB87Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00439AAAMapped>, _STL::_Select1st<_STL::pair<const int, Rva00439AAAMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva004F90FFMapped>, _STL::_Select1st<_STL::pair<const int, Rva004F90FFMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004F90FFMapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502861Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00502861Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502861Mapped> > >;
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
struct Rva00501130Mapped { int a; };
struct Rva00502FAEMapped { int a; };
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva002F1DA1Mapped>, _STL::_Select1st<_STL::pair<const int, Rva002F1DA1Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva002F1DA1Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00501130Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00501130Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501130Mapped> > >;
template class _STL::_Rb_tree<int, _STL::pair<const int, Rva00502FAEMapped>, _STL::_Select1st<_STL::pair<const int, Rva00502FAEMapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00502FAEMapped> > >;

// map::insert(hint) forwarders @0x00502D61 and @0x00502F09 (29B) over the insert_unique rows above.
template _STL::map<int, Rva00502861Mapped>::iterator _STL::map<int, Rva00502861Mapped>::insert(_STL::map<int, Rva00502861Mapped>::iterator, const _STL::map<int, Rva00502861Mapped>::value_type &);
template _STL::map<int, Rva00502BCDMapped>::iterator _STL::map<int, Rva00502BCDMapped>::insert(_STL::map<int, Rva00502BCDMapped>::iterator, const _STL::map<int, Rva00502BCDMapped>::value_type &);
// multimap::insert(hint) forwarder @0x00501A0B (29B) over the insert_equal row above.
template _STL::multimap<int, Rva00501130Mapped>::iterator _STL::multimap<int, Rva00501130Mapped>::insert(_STL::multimap<int, Rva00501130Mapped>::iterator, const _STL::multimap<int, Rva00501130Mapped>::value_type &);
// map::insert(hint) @0x004F9ED6 and multimap::insert(hint) @0x0050364E (29B each).
template _STL::map<int, Rva004F90FFMapped>::iterator _STL::map<int, Rva004F90FFMapped>::insert(_STL::map<int, Rva004F90FFMapped>::iterator, const _STL::map<int, Rva004F90FFMapped>::value_type &);
template _STL::multimap<int, Rva00502FAEMapped>::iterator _STL::multimap<int, Rva00502FAEMapped>::insert(_STL::multimap<int, Rva00502FAEMapped>::iterator, const _STL::multimap<int, Rva00502FAEMapped>::value_type &);

struct Rva00501776 { int a; };
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

