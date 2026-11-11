// cl: /D_STLP_USE_MALLOC /O1 /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0050024C@Rva004FF8DA@@QAEPAXHH@Z retail 0x0050024C 379B (RET8, EH).
// WB 0x012FCAC0 names it LivingWorldAIBuildingTypes::GetUnitToFightType
// (LivingWorldAIInformation.cpp, asserts 265..318); the address-derived
// owner spelling of the rowed siblings (stlport_map_004FF8DA.cpp,
// LivingWorldAIHasUnitToFightType.cpp) is kept. It walks the same +0x44
// inner multimap as HasUnitToFightType (rowed/pinned STLport vector, find,
// upper-bound, count and equal_range providers; lines 0x123/0x12A draws) and
// returns the chosen entry's mapped value (node+0x14), else the first
// non-empty 88-byte unit list of the +0x38 map's eight vectors (the
// 0x004FF910 tail). The range pair is default-constructed, assigned from the
// inline multimap equal_range and stepped in place, as the WB twin shows.
// The key/element types of the inner map and the vector stay opaque: the
// call views use the existing rowed (ICF-folded) instantiations.
#include <cstdlib>
#include <vector>
// max<unsigned> inlines everywhere here; keep it inline-only so this unit
// emits no copy against retail's 0x00013740 (body verbatim).
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b)
{ return __a < __b ? __b : __a; }
}

class Rva004FF8DA;
class ModuleData;

namespace _STL {
template<class T> struct _Select1st {};
template<class T> struct less {};

struct _Rb_tree_node_base
{
	int color;
	_Rb_tree_node_base *parent, *left, *right;
};

template<class T> struct _Rb_tree_node : _Rb_tree_node_base { T value; };

template<class T, class Traits> struct _Rb_tree_iterator { _Rb_tree_node_base *_M_node; };

template<class D> class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};

template<class K, class V, class S, class C, class A> class _Rb_tree
{
	friend class ::Rva004FF8DA;
	template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
	_Rb_tree_node<V> *_M_upper_bound(const K &) const;

public:
	_Rb_tree_node_base *header;
	char unknown04[8];
	unsigned count(const K &) const;
	pair<_Rb_tree_iterator<V, _Const_traits<V> >, _Rb_tree_iterator<V, _Const_traits<V> > > equal_range(const K &) const;
};
}

typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>,
	_STL::less<int>, _STL::allocator<IntIntPair> > IntIntTree;
typedef _STL::pair<const int, void *> IntPtrPair;
typedef _STL::_Rb_tree<int, IntPtrPair, _STL::_Select1st<IntPtrPair>,
	_STL::less<int>, _STL::allocator<IntPtrPair> > IntPtrTree;
typedef _STL::pair<const unsigned, void *> UIntPtrPair;
typedef _STL::_Rb_tree<unsigned, UIntPtrPair, _STL::_Select1st<UIntPtrPair>,
	_STL::less<unsigned>, _STL::allocator<UIntPtrPair> > UIntPtrTree;
typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > PointerVector;
typedef _STL::_Rb_tree_iterator<IntPtrPair, _STL::_Const_traits<IntPtrPair> > IntPtrCIt;

// The multimap wrapper: its equal_range forwards to the tree's.
struct IntPtrMulti
{
	IntPtrTree _M_t;
	_STL::pair<IntPtrCIt, IntPtrCIt> equal_range(const int &k) const { return _M_t.equal_range(k); }
};

struct BfmePod88 { int a[22]; };
struct UnitArray
{
	BfmePod88 *first, *last, *limit;
	unsigned size() const { return (unsigned)(last - first); }
	BfmePod88 &operator[](int i) { return first[i]; }
};

struct Out00418CC8 { int m_lo, m_hi; };

#include "../../../../../Include/GameLogic/LivingWorldAutoResolveCombatChain.h"

class Rva004FF8DA
{
	char pad[0x38];
	IntIntTree tree;
	IntIntTree fightTree;

public:
	void *rva0050024C(int unitType, int key);
};

int GetGameLogicRandomValue(int, int, char *, int);

// ?rva0050024C@Rva004FF8DA@@QAEPAXHH@Z
void *Rva004FF8DA::rva0050024C(int unitType, int key)
{
	_STL::_Rb_tree_node<IntIntPair> *node = tree._M_find(key);
	UnitArray *&arr = *(UnitArray **)((char *)node + 0x14);
	if (unitType < 8) {
		PointerVector keys;
		keys.clear();
		_STL::_Rb_tree_node<IntIntPair> *outer = fightTree._M_find(key);
		UIntPtrTree &inner = *(UIntPtrTree *)((char *)outer + 0x14);
		for (_STL::_Rb_tree_node_base *n = inner.header->left; n != inner.header; ) {
			key = *(int *)((char *)n + 0x10);
			Out00418CC8 out = { 7, 0 };
			((LivingWorldAutoResolveCombatChain *)key)->getHighestPriorityTarget(&out);
			if (out.m_lo == unitType)
				keys.push_back(*(const ModuleData **)&key);
			n = inner._M_upper_bound(*(unsigned *)&key);
		}
		if (keys.size() > 0) {
			int chosen = GetGameLogicRandomValue(0, keys.size() - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp", 0x123);
			const int &selected = *(const int *)&keys[chosen];
			key = ((IntPtrTree *)&inner)->count(selected);
			if ((unsigned)key > 0) {
				_STL::pair<IntPtrCIt, IntPtrCIt> range;
				range = ((IntPtrMulti *)&inner)->equal_range(selected);
				int steps = GetGameLogicRandomValue(0, key - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp", 0x12a);
				for (int i = 0; i < steps; ++i)
					range.first._M_node = _STL::_Rb_global<bool>::_M_increment(range.first._M_node);
				return (char *)range.first._M_node + 0x14;
			}
		}
	}
	for (unsigned i = 0; i < 8; ++i) {
		if (arr[i].size() > 0)
			return &arr[i][0];
	}
	return &arr[0][0];
}
