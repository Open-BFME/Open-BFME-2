// cl: /D_STLP_USE_MALLOC /O1 /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0050010D@Rva004FF8DA@@QAE_NHH@Z retail 0x0050010D 319B (RET8, EH).
// WB 0x012FC560 names it LivingWorldAIBuildingTypes::HasUnitToFightType
// (LivingWorldAIInformation.cpp, asserts 192..224); the address-derived
// owner spelling of the rowed siblings 0x004FF8DA/0x004FF910
// (stlport_map_004FF8DA.cpp) is kept. Target facts: a local pointer vector
// (rowed/pinned STLport push_back 0x004DFCB0, erase 0x0031BD55, base ctor
// 0x00211E58), the int-key find 0x00388F63 on the +0x44 map, an inner
// multimap at node+0x14 walked with the folded upper-bound 0x004FF539,
// count 0x004FF8B1 and equal_range 0x004FF752, two GetGameLogicRandomValue
// draws (lines 217, 224) and _M_increment 0x00024250 steps.
// WB shape carried into the source: the range pair is default-constructed,
// then assigned from the container's (inline) equal_range, and its first
// iterator is stepped in place; that assignment is retail's
// second-then-first copy out of the call's return slot.
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

#include "../../../../../Include/Common/Out00418CC8.h"

#include "../../../../../Include/GameLogic/LivingWorldAutoResolveCombatChain.h"

#include "../../../../../Include/Common/Rva004FF8DA.h"

int GetGameLogicRandomValue(int, int, char *, int);

// ?rva0050010D@Rva004FF8DA@@QAE_NHH@Z
bool Rva004FF8DA::rva0050010D(int unitType, int key)
{
	if (unitType < 8) {
		PointerVector keys;
		keys.clear();
		_STL::_Rb_tree_node<IntIntPair> *outer = fightTree._M_find(key);
		UIntPtrTree &inner = *(UIntPtrTree *)((char *)outer + 0x14);
		for (_STL::_Rb_tree_node_base *n = inner.header->left; n != inner.header; ) {
			const ModuleData *entry = *(const ModuleData **)((char *)n + 0x10);
			Out00418CC8 out = { 7, 0 };
			((LivingWorldAutoResolveCombatChain *)entry)->getHighestPriorityTarget(&out);
			if (out.m_lo == unitType)
				keys.push_back(entry);
			n = inner._M_upper_bound(*(unsigned *)&entry);
		}
		if (keys.size() > 0) {
			int chosen = GetGameLogicRandomValue(0, keys.size() - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp", 217);
			const int &selected = *(const int *)&keys[chosen];
			unsigned count = ((IntPtrTree *)&inner)->count(selected);
			if (count > 0) {
				_STL::pair<IntPtrCIt, IntPtrCIt> range;
				range = ((IntPtrMulti *)&inner)->equal_range(selected);
				int steps = GetGameLogicRandomValue(0, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp", 224);
				for (int i = 0; i < steps; ++i)
					range.first._M_node = _STL::_Rb_global<bool>::_M_increment(range.first._M_node);
				return true;
			}
		}
	}
	return false;
}
