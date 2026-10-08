// ??A?$map@HURva004FA168Value@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva004FA168Value@@@_STL@@@3@@_STL@@QAEAAURva004FA168Value@@ABH@Z
// partial score=0.95 date=2026-10-08
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
// retail 0x001EA05B (153 bytes).
//
// LocomotorSetType to template-vector map subscript (AIUpdate parse
// cluster). Miss path builds a default vector temp through the rowed
// _Vector_base 0x211E58, pairs it with the key through 0x796CB, and
// hint-inserts through the rowed wrapper 0x1E9066. /EHs (not /EHsc)
// keeps the post-insert EH state stores; the explicit-spec rvalue pair
// keeps the pair address in eax (no re-lea) and homes the hidden
// insert-result temp at [ebp-0x10].

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;

template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType& __k)
{
	BfmeLocomotorSetMap::iterator __i = lower_bound(__k);
	if (__i == end() || key_comp()(__k, (*__i).first)) {
		BfmeLocomotorTemplateVector __tmp;
		__i = insert(__i, BfmeLocomotorSetMap::value_type(__k, __tmp));
	}
	return (*__i).second;
}

template class _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > >;

// Native 0x0021E063 has the same scoped-vector expression as 0x001EA05B.
// Its insertion goes to the independently rowed int/vector<unsigned> map
// wrapper 0x0021DB74. The lower-bound walk, empty vector header and pair
// constructor are folded helpers; no Locomotor application identity is claimed
// for this integer-keyed specialization.
typedef _STL::vector<unsigned int> BfmeIntegerMapVector;
typedef _STL::map<int, BfmeIntegerMapVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmeIntegerMapVector> > > BfmeIntegerVectorMap;

template<> BfmeIntegerMapVector &BfmeIntegerVectorMap::operator[](const int &key)
{
 BfmeIntegerVectorMap::iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  BfmeIntegerMapVector value;
  it = insert(it, BfmeIntegerVectorMap::value_type(key, value));
 }
 return (*it).second;
}

template class _STL::map<int, BfmeIntegerMapVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmeIntegerMapVector> > >;

// Native 0x0007A26E orders keys unsigned and uses the same twelve-byte
// vector header and four-byte trivial element copy. Unsigned storage names
// those observed bits; the application's element identity remains unknown.
// The formerly missing 0x00079ED4 forwarder is now independently rowed under
// its opaque-record view. Reuse that established iterator/pair ABI without
// adding a second pin or asserting its inferred signed key as a target fact.
typedef _STL::map<unsigned int, BfmeIntegerMapVector, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, BfmeIntegerMapVector> > > BfmeUnsignedVectorMap;
struct Rva00079ED4Record { char bytes[1]; };
typedef _STL::map<int, Rva00079ED4Record, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00079ED4Record> > > Rva0007A26EInsertMap;
namespace _STL {
template <> Rva0007A26EInsertMap::iterator Rva0007A26EInsertMap::insert(Rva0007A26EInsertMap::iterator, const Rva0007A26EInsertMap::value_type &);
}

template<> BfmeIntegerMapVector &BfmeUnsignedVectorMap::operator[](const unsigned int &key)
{
 BfmeUnsignedVectorMap::iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  BfmeIntegerMapVector value;
  it = BfmeUnsignedVectorMap::iterator(reinterpret_cast<BfmeUnsignedVectorMap::iterator::_Link_type>(
    reinterpret_cast<Rva0007A26EInsertMap *>(this)->insert(
     Rva0007A26EInsertMap::iterator(reinterpret_cast<Rva0007A26EInsertMap::iterator::_Link_type>(it._M_node)),
     reinterpret_cast<const Rva0007A26EInsertMap::value_type &>(BfmeUnsignedVectorMap::value_type(key, value)))._M_node));
 }
 return (*it).second;
}

template class _STL::map<unsigned int, BfmeIntegerMapVector, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, BfmeIntegerMapVector> > >;

// Native 0x004FA168 uses a twelve-byte vector header with nontrivial
// four-byte elements: copy 0x004F69D6 and destructor 0x004F7D7F.
// Keep their existing opaque ABI views rather than assigning an application
// type from the BFME 1 ObjectCreationList donor. Default construction shares
// the independently verified empty vector-header constructor 0x00211E58.
struct Rva004F69D6Record { ~Rva004F69D6Record(); char bytes[4]; };
struct Rva004F7D7FRecord { Rva004F7D7FRecord(); Rva004F7D7FRecord(const Rva004F7D7FRecord&); ~Rva004F7D7FRecord(); Rva004F7D7FRecord&operator=(const Rva004F7D7FRecord&); char bytes[1]; };
typedef _STL::vector<Rva004F69D6Record> Rva004FA168CopyVector;
typedef _STL::vector<Rva004F7D7FRecord> Rva004FA168DestroyVector;
namespace _STL {
template<> Rva004FA168CopyVector::vector(const Rva004FA168CopyVector &);
template<> Rva004FA168DestroyVector::~vector();
}
struct Rva004FA168Value
{
 unsigned int header[3];
 __forceinline Rva004FA168Value() { new (this) BfmeIntegerMapVector; }
 __forceinline Rva004FA168Value(const Rva004FA168Value &other) {
  new (this) Rva004FA168CopyVector(reinterpret_cast<const Rva004FA168CopyVector &>(other));
 }
 __forceinline ~Rva004FA168Value() { reinterpret_cast<Rva004FA168DestroyVector *>(this)->~vector(); }
};
typedef _STL::map<int, Rva004FA168Value, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004FA168Value> > > Rva004FA168Map;
struct Rva004F90FFMapped { int a; };
typedef _STL::map<int, Rva004F90FFMapped> Rva004FA168InsertMap;
namespace _STL {
template<> Rva004FA168InsertMap::iterator Rva004FA168InsertMap::insert(Rva004FA168InsertMap::iterator, const Rva004FA168InsertMap::value_type &);
}
template<> Rva004FA168Value &Rva004FA168Map::operator[](const int &key)
{
 iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  Rva004FA168Value value;
  it = iterator(reinterpret_cast<iterator::_Link_type>(
   reinterpret_cast<Rva004FA168InsertMap *>(this)->insert(
    Rva004FA168InsertMap::iterator(reinterpret_cast<Rva004FA168InsertMap::iterator::_Link_type>(it._M_node)),
    reinterpret_cast<const Rva004FA168InsertMap::value_type &>(value_type(key, value)))._M_node));
 }
 return (*it).second;
}
template class _STL::map<int, Rva004FA168Value, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva004FA168Value> > >;
