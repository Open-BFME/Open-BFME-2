// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 005020CC..0050228B, free RET0, whole 447-byte region distance builder.
// WB 012FCF60 and callers 002BC5D3/00502FE9 confirm the role; the original
// source name remains unknown. Layouts below are target access views.
// The global entry has a 4-byte region key and two 12-byte trees. AsciiString
// is the pre-existing insertion provider's mangled ABI carrier, not its payload.
// The four-slot callback table at VA 00C63B40 supplies cost/estimate, a no-op
// visit, and pointer equality. Its two overrides are whole-body ICF twins.
// Pair and result storage express the native temporary lifetimes. Constructing
// the pair with its hint inside insertBuilt lets MSVC schedule the pair writes
// after the outgoing hint and reuse the dead second result for global insertion.
#include "ascii_string.h"
enum ObjectID {};

struct LocalPlacement
{
	void *where;
	LocalPlacement(void *address) : where(address) {}
};
__forceinline void *operator new(unsigned int,LocalPlacement p) throw() {return p.where;}
namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class Pair> struct _Select1st;
template <class T> struct _Nonconst_traits;

template <class T1, class T2>
struct pair
{
	// Retail has no out-of-line copy; dllimport keeps this one inline-only.
	__declspec(dllimport) __forceinline pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	T1 first;
	T2 second;
};

template <class T1, class T2>
__forceinline pair<T1, T2> make_pair(const T1 &firstValue, const T2 &secondValue) { return pair<T1, T2>(firstValue, secondValue); }

struct _Rb_tree_node_base
{
	char _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

struct _Rb_tree_base_iterator
{
	_Rb_tree_node_base *_M_node;
};

template <class Value, class Traits>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator
{
	// Build the hint and its associated pair in the same inline context.
	__forceinline _Rb_tree_iterator(_Rb_tree_node_base *node, Value *value, int firstValue, int secondValue)
	{
		_M_node = node;
		new(LocalPlacement(value)) Value(firstValue, secondValue);
	}
	_Rb_tree_iterator(_Rb_tree_node_base *node) { _M_node = node; }
	_Rb_tree_iterator(const _Rb_tree_iterator &other) { _M_node = other._M_node; }
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef Value value_type;
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
	iterator begin() { return iterator(_M_header->_M_left); }
	unsigned int size() const { return _M_node_count; }
	iterator insert_equal(iterator position, const value_type &v);
	iterator insert_unique(iterator position, const value_type &v);
	iterator insert_unique_00501587(iterator position, const value_type &v);
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	int _M_key_compare;
};

template <class Key, class T>
class map
{
public:
	typedef pair<const Key, T> value_type;
	typedef _Rb_tree<Key, value_type, _Select1st<value_type>, less<Key>, allocator<value_type> > _Rep_type;
	typedef typename _Rep_type::iterator iterator;
	iterator begin() { return _M_t.begin(); }
	unsigned int size() const { return _M_t.size(); }
	__forceinline iterator insert(iterator position, const value_type &x) { return _M_t.insert_unique(position, x); }
__forceinline iterator insertBuilt(_Rb_tree_node_base *node, int keyValue, int mappedValue, void *storage)
	{
		return _M_t.insert_unique(iterator(node, (value_type *)storage, keyValue, mappedValue),
			*(value_type *)storage);
	}
	_Rep_type _M_t;
};

template <class Key, class T>
class multimap
{
public:
	typedef pair<const Key, T> value_type;
	typedef _Rb_tree<Key, value_type, _Select1st<value_type>, less<Key>, allocator<value_type> > _Rep_type;
	typedef typename _Rep_type::iterator iterator;
	iterator begin() { return _M_t.begin(); }
	__forceinline iterator insert(iterator position, const value_type &x) { return _M_t.insert_equal(position, x); }
__forceinline iterator insertBuilt(_Rb_tree_node_base *node, int keyValue, int mappedValue, void *storage)
	{
		return _M_t.insert_equal(iterator(node, (value_type *)storage, keyValue, mappedValue),
			*(value_type *)storage);
	}
	_Rep_type _M_t;
};

template <class T,class A=allocator<T> >
class vector
{
public:
	unsigned int size() const { return _M_finish - _M_start; }
	T &operator[](unsigned int n) { return _M_start[n]; }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

typedef _STL::pair<const int, int> IntIntValue;
typedef _STL::_Rb_tree<int, IntIntValue, _STL::_Select1st<IntIntValue>, _STL::less<int>, _STL::allocator<IntIntValue> > IntIntTree;

class Rva002B82D5
{
public:
	~Rva002B82D5();
	_STL::multimap<int, int> m_byDistance;
	_STL::map<int, int> m_byRegion;
};

class Rva0050055D : public Rva002B82D5
{
public:
	Rva0050055D();
	Rva0050055D(const Rva0050055D &other);
};

namespace _STL
{
template <>
struct pair<const int, Rva0050055D>
{
	pair(const pair &other);
	const int first;
	Rva0050055D second;
};
}

typedef _STL::pair<const int, AsciiString> GlobalValue;
typedef _STL::_Rb_tree<int, GlobalValue, _STL::_Select1st<GlobalValue>, _STL::less<int>, _STL::allocator<GlobalValue> > GlobalTree;
typedef _STL::pair<const int, Rva0050055D> DistancePair;
// The provider owns DistancePair's copy constructor. Keep ownership of this
// local placement lifetime here so no competing implicit pair destructor is
// emitted. Only the two-tree member has nontrivial destruction.
struct DistanceEntry
{
    __declspec(align(4)) char storage[sizeof(DistancePair)];
    __forceinline DistanceEntry(const DistancePair &source)
    {
        new(LocalPlacement(storage)) DistancePair(source);
    }
    __forceinline ~DistanceEntry()
    {
        reinterpret_cast<Rva002B82D5 *>(storage + 4)->~Rva002B82D5();
    }
};

class Rva005020CCDistanceTable
{
public:
	unsigned int size() const { return _M_t.size(); }
	GlobalTree::iterator begin() { return _M_t.begin(); }
	__forceinline GlobalTree::iterator insert(const GlobalTree::iterator &position, const GlobalValue &globalValue)
	{
		return _M_t.insert_unique_00501587(position, globalValue);
	}
	GlobalTree _M_t;
};

extern unsigned int g_Va00E04544;

class LivingWorldSearchCallback;
struct Rva003F71D4Point {char prefix[16];float x,y;};
class __declspec(novtable) Rva003F71D4Metric {public:__declspec(dllimport) Rva003F71D4Metric() {} virtual float v00(const Rva003F71D4Point*,const Rva003F71D4Point*);virtual float v01(const Rva003F71D4Point*,const Rva003F71D4Point*);virtual void v02(const Rva003F71D4Point*);virtual bool v03(int,int);};
class Rva004FF33DCallback:public Rva003F71D4Metric {public:virtual float v00(const Rva003F71D4Point*,const Rva003F71D4Point*);virtual float v01(const Rva003F71D4Point*,const Rva003F71D4Point*);};
class Rva003EF8E1
{
public:
	int FindShortestPath(LivingWorldSearchCallback *callback, int a, int from, int to, _STL::vector<ObjectID> *path, bool b);
};

class LivingWorldRegion
{
public:
	char m_pad00[0x12C];
	int m_id;			// +0x12C
	char m_pad130[0x1A2 - 0x130];
	bool m_1A2;			// +0x1A2
};

class LivingWorldRegionManager
{
public:
	char m_pad00[0x2C];
	_STL::vector<LivingWorldRegion *> m_regions;	// +0x2C
	char m_pad38[0x4C - 0x38];
	Rva003EF8E1 *m_pathFinder;	// +0x4C
};

class LivingWorldCampaign
{
public:
	char m_pad00[8];
	LivingWorldRegionManager *m_regionManager;	// +0x08
};

class LivingWorldLogic
{
public:
	__forceinline _STL::vector<LivingWorldRegion *> *getRegions()
	{
		LivingWorldCampaign *livingWorldCampaign = m_campaign;
		if (livingWorldCampaign->m_regionManager)
			return &livingWorldCampaign->m_regionManager->m_regions;
		return 0;
	}
	__forceinline Rva003EF8E1 *getPathFinder()
	{
		LivingWorldRegionManager *livingWorldRegionManager = m_campaign->m_regionManager;
		return livingWorldRegionManager ? livingWorldRegionManager->m_pathFinder : 0;
	}
	__forceinline int findShortestPath(LivingWorldSearchCallback *callback, int a, int from, int to, _STL::vector<ObjectID> *path, bool b)
	{
		return getPathFinder()->FindShortestPath(callback, a, from, to, path, b);
	}
	char m_pad00[0xB0];
	LivingWorldCampaign *m_campaign;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

void Rva005020CCBuildRegionDistances()
{
	struct __declspec(align(4)) InsertScratch
	{
		char regionPair[8], distancePair[8], second[4], first[4];
	};
	InsertScratch scratch;
	Rva005020CCDistanceTable *table = reinterpret_cast<Rva005020CCDistanceTable *>(&g_Va00E04544);
	if (table->size() != 0)
		return;
	_STL::vector<LivingWorldRegion *> *regions = TheLivingWorldLogic->getRegions();
	for (unsigned int regionIndex = 0; regionIndex < regions->size(); ++regionIndex) {
		Rva0050055D distances;
		LivingWorldRegion *region = (*regions)[regionIndex];
		if (region->m_1A2) {
			for (unsigned int otherRegionIndex = 0; otherRegionIndex < regions->size(); ++otherRegionIndex) {
				LivingWorldRegion *other = (*regions)[otherRegionIndex];
				Rva004FF33DCallback callback;
				int distance = TheLivingWorldLogic->findShortestPath((LivingWorldSearchCallback*)&callback, -1, region->m_id, other->m_id, 0, 0);
				if (distance >= 0) {
					IntIntTree::iterator hintDistance = distances.m_byDistance.begin();
					int otherID = other->m_id;
					new(LocalPlacement(scratch.first)) IntIntTree::iterator(
						distances.m_byDistance.insertBuilt(hintDistance._M_node, distance, otherID, scratch.distancePair));
					IntIntTree::iterator hintRegion = distances.m_byRegion.begin();
					new(LocalPlacement(scratch.second)) IntIntTree::iterator(
						distances.m_byRegion.insertBuilt(hintRegion._M_node, otherID, distance, scratch.regionPair));
				}
			}
			_STL::pair<int, Rva0050055D> value(region->m_id, distances);
			DistanceEntry entry(reinterpret_cast<const DistancePair &>(value));
			new(LocalPlacement(scratch.second)) GlobalTree::iterator(table->insert(table->begin(), reinterpret_cast<const GlobalValue &>(entry)));
		}
	}
}

__declspec(noinline) float Rva004FF33DCallback::v00(const Rva003F71D4Point*a,const Rva003F71D4Point*b){return(*(const int*)a==*(const int*)b)?0.0f:1.0f;}
__declspec(noinline) float Rva004FF33DCallback::v01(const Rva003F71D4Point*,const Rva003F71D4Point*){return 1.0f;}
