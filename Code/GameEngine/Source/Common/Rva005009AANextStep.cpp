// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005009AA@@YAHHH@Z, retail 0x005009AA (223 bytes). Cdecl, two int keys.
// Reads the int-key map at 0x00E04544 whose 24-byte values (copy
// constructor 0x0050055D, destructor 0x002B82D5) hold an int multimap at +0
// and an int-to-int map at +0x0C, as the rowed rva0050059A/rva00500606 in
// Rva00500606EqualRange.cpp do. Copies the first key's value, reads its
// +0x0C entry for the second key, then walks its +0 entries under key 1
// (rowed equal_range 0x002F1C89): for each listed key present in the
// global map it copies that key's value and returns the listed key when
// its +0x0C entry for the second key is exactly one less. Returns the
// first key when none is. Callers 0x0059C102 and 0x0059C90F. Map ownership
// and key meaning are not established so the name stays address-derived.

#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

extern unsigned int g_Va00E04544;

typedef _STL::map<int, int> Rva005009AAIntMap;
typedef _STL::pair<const int, int> Rva005009AAIntValue;
typedef _STL::_Rb_tree<int, Rva005009AAIntValue, _STL::_Select1st<Rva005009AAIntValue>,
	_STL::less<int>, _STL::allocator<Rva005009AAIntValue> > Rva005009AAIntTree;
typedef _STL::pair<Rva005009AAIntTree::iterator, Rva005009AAIntTree::iterator> Rva005009AARange;

// The value's copy constructor and destructor carry different ledger names:
// the copy runs as the base of the destroyed type, so both the scope exits
// and the unwind funclets call the destructor directly.
class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);
	char m_data[24];
};

class Rva002B82D5 : public Rva0050055D
{
public:
	Rva002B82D5(const Rva0050055D &other) : Rva0050055D(other) {}
	~Rva002B82D5();
};

int __cdecl rva005009AA(int from, int to)
{
	Rva005009AAIntMap *map = (Rva005009AAIntMap *)&g_Va00E04544;
	Rva002B82D5 fromValue(*(const Rva0050055D *)&map->find(from)->second);
	int fromDistance = ((Rva005009AAIntMap *)((char *)&fromValue + 0x0C))->find(to)->second;
	Rva005009AARange range = ((Rva005009AAIntTree *)&fromValue)->equal_range(1);
	for (Rva005009AAIntTree::iterator it = range.first; it != range.second; ++it)
	{
		if (map->find((*it).second) != map->end())
		{
			Rva002B82D5 stepValue(*(const Rva0050055D *)&map->find((*it).second)->second);
			if (fromDistance - ((Rva005009AAIntMap *)((char *)&stepValue + 0x0C))->find(to)->second == 1)
				return (*it).second;
		}
	}
	return from;
}

// Native00502381..0050243F (190B), WB01300010: clear output army records,
// scan the receiver's player buckets and append matching IDs whose distance
// from the supplied key is <= limit. The third argument is const int*, as
// proved by its unchanged PUSH into the rowed _M_find(const int&) worker.
// Receiver map4, bucket records at node28/2C, record id0 and pointer10 are
// target evidence. Record20 has an empty12B tree at4 and an uninitialized
// opaque last word; its original names and element meanings remain open.
// Use the already-owned tree destructor solely as an empty-tree destruction
// view, without assigning Locomotor semantics to the record. Its constructor
// is the rowed int/pointer-map25B provider. Vector55B push and51B erase are
// declared under their existing record spelling, preserving providers.
// The existing global declaration above is reused, not newly pinned.
#include <vector>
enum LocomotorSetType { LOCOMOTORSET_INVALID=-1 };
class LocomotorTemplate;
typedef _STL::vector<const LocomotorTemplate*> NativeVector;
typedef _STL::_Rb_tree<LocomotorSetType,_STL::pair<const LocomotorSetType,NativeVector>,_STL::_Select1st<_STL::pair<const LocomotorSetType,NativeVector> >,_STL::less<LocomotorSetType>,_STL::allocator<_STL::pair<const LocomotorSetType,NativeVector> > > NativeTree;
namespace _STL { template<> NativeTree::~_Rb_tree(); }
typedef _STL::map<int,void*> MapPtr;
namespace _STL { template<> MapPtr::map(); }
struct Rva00501E3FElement {
 int id; char map[12]; void *opaque;
 __forceinline Rva00501E3FElement(){reinterpret_cast<MapPtr*>(map)->MapPtr::map();}
 __forceinline ~Rva00501E3FElement(){reinterpret_cast<NativeTree*>(map)->NativeTree::~_Rb_tree();}
};
namespace _STL {
 template<> vector<Rva00501E3FElement>::iterator vector<Rva00501E3FElement>::erase(iterator,iterator);
 template<> void vector<Rva00501E3FElement>::push_back(const Rva00501E3FElement &);
}
typedef _STL::vector<Rva00501E3FElement> RecordVector;
struct QueryBucket {char prefix[20]; RecordVector records;char tail[12];};
typedef _STL::multimap<int,QueryBucket> QueryMap;
typedef _STL::map<int,int> IntMap;
struct Rva00502381 {char prefix[4]; QueryMap values;void rva00502381(int,int,const int*,RecordVector*);};
void Rva00502381::rva00502381(int who,int limit,const int*key,RecordVector*out){
 IntMap*global=reinterpret_cast<IntMap*>(&g_Va00E04544);
 IntMap::iterator found=global->find(*key);
 out->erase(out->begin(),out->end());
 for(QueryMap::iterator it=values.begin();it!=values.end();++it) {
  if(who==it->first) {
   for(RecordVector::iterator r=it->second.records.begin();r!=it->second.records.end();++r) {
    int current=*reinterpret_cast<int*>(r->opaque);
    IntMap*inner=reinterpret_cast<IntMap*>(reinterpret_cast<char*>(&found->second)+12);
    if(inner->find(current)->second<=limit) {
     Rva00501E3FElement temp;
     temp.id=r->id;
     out->push_back(temp);
    }
   }
  }
 }
}
