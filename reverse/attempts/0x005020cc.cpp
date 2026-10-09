// ?rva005020CC@Rva005020CC@@QAEXXZ
// partial score=0.86 date=2026-10-10
// NEAR (score ~0.86): ?Rva005020CCBuildRegionDistances@@YAXXZ retail 0x005020CC 447 bytes.
// Remaining: frame 0x7C vs 0x78 (global insert return temp gets its own slot
// instead of sharing the inner insert_unique slot -0x24) which shifts every
// object below -0x24 by 4; getRegions null test emits mov edi/add edi where
// retail keeps the manager in eax and uses lea edi; inner insert pair stores
// scheduled before the begin() load. Needs pins ??0Rva0050055D@@QAE@XZ=0x004FFE41
// and FindShortestPath (log name) =0x003EFA0A. Callback vtable 0x00863B40 has
// no ledger name. Target file would be
// Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva005020CCRegionDistances.cpp
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
enum ObjectID {};

namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class Pair> struct _Select1st;
template <class T> struct _Nonconst_traits;

template <class T1, class T2>
struct pair
{
	__forceinline pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	T1 first;
	T2 second;
};

template <class T1, class T2>
__forceinline pair<T1, T2> make_pair(const T1 &a, const T2 &b) { return pair<T1, T2>(a, b); }

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
	iterator insert(iterator position, const value_type &x) { return _M_t.insert_unique(position, x); }
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
	iterator insert(iterator position, const value_type &x) { return _M_t.insert_equal(position, x); }
	_Rep_type _M_t;
};

template <class T>
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

struct Rva00500839Element : public Rva002B82D5
{
};

namespace _STL
{
template <>
struct pair<const int, Rva00500839Element>
{
	pair(const pair &other);
	const int first;
	Rva00500839Element second;
};
}

typedef _STL::pair<const int, AsciiString> GlobalValue;
typedef _STL::_Rb_tree<int, GlobalValue, _STL::_Select1st<GlobalValue>, _STL::less<int>, _STL::allocator<GlobalValue> > GlobalTree;
typedef _STL::pair<const int, Rva00500839Element> DistanceEntry;

class Rva005020CCDistanceTable
{
public:
	unsigned int size() const { return _M_t.size(); }
	GlobalTree::iterator begin() { return _M_t.begin(); }
	GlobalTree::iterator insert(const GlobalTree::iterator &position, const GlobalValue &x)
	{
		return _M_t.insert_unique_00501587(position, x);
	}
	GlobalTree _M_t;
};

extern unsigned int g_Va00E04544;

class LivingWorldSearchCallback
{
public:
	virtual float slot0(int *a, int *b);
	virtual float slot1(int a, int b);
};

class Rva005020CCSearchCallback : public LivingWorldSearchCallback
{
public:
	Rva005020CCSearchCallback() {}
	virtual float slot0(int *a, int *b);
	virtual float slot1(int a, int b);
};

class LivingWorldPathFinder
{
public:
	int FindShortestPath(LivingWorldSearchCallback *callback, int a, int from, int to, _STL::vector<ObjectID> *path, int b);
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
	LivingWorldPathFinder *m_pathFinder;	// +0x4C
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
		LivingWorldRegionManager *m = m_campaign->m_regionManager;
		if (m)
			return &m->m_regions;
		return 0;
	}
	__forceinline LivingWorldPathFinder *getPathFinder()
	{
		LivingWorldRegionManager *m = m_campaign->m_regionManager;
		return m ? m->m_pathFinder : 0;
	}
	__forceinline int findShortestPath(LivingWorldSearchCallback *callback, int a, int from, int to, _STL::vector<ObjectID> *path, int b)
	{
		return getPathFinder()->FindShortestPath(callback, a, from, to, path, b);
	}
	char m_pad00[0xB0];
	LivingWorldCampaign *m_campaign;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

void Rva005020CCBuildRegionDistances()
{
	Rva005020CCDistanceTable *table = reinterpret_cast<Rva005020CCDistanceTable *>(&g_Va00E04544);
	if (table->size() != 0)
		return;
	_STL::vector<LivingWorldRegion *> *regions = TheLivingWorldLogic->getRegions();
	for (unsigned int i = 0; i < regions->size(); ++i) {
		Rva0050055D distances;
		LivingWorldRegion *region = (*regions)[i];
		if (region->m_1A2) {
			for (unsigned int j = 0; j < regions->size(); ++j) {
				LivingWorldRegion *other = (*regions)[j];
				Rva005020CCSearchCallback callback;
				int distance = TheLivingWorldLogic->findShortestPath(&callback, -1, region->m_id, other->m_id, 0, 0);
				if (distance >= 0) {
					int otherID = other->m_id;
					distances.m_byDistance.insert(distances.m_byDistance.begin(), IntIntValue(distance, otherID));
					distances.m_byRegion.insert(distances.m_byRegion.begin(), IntIntValue(otherID, distance));
				}
			}
			_STL::pair<int, Rva0050055D> value(region->m_id, distances);
			DistanceEntry entry(reinterpret_cast<const DistanceEntry &>(value));
			table->insert(table->begin(), reinterpret_cast<const GlobalValue &>(entry));
		}
	}
}
