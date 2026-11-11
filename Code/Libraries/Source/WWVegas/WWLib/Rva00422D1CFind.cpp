// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00422D1C@FormationAssistant@@QAEHH@Z retail 0x00422D1C 34B.
// Native caller 0037FAC6 loads TheFormationAssistant into ECX before this
// RET4 call. The receiver is unused by the global-map body, but the function
// is a member; the former free stdcall spelling lost that caller ABI.
// Global map<int,int> lookup: find key via rowed _M_find 0x00388F63,
// return mapped value at node+0x14 or -1 when iterator equals end.
// Evidence: retail lea eax [esp+4] push eax mov ecx <global> call _M_find,
// cmp eax [global] je or -1 else mov eax [eax+0x14] ret 4; caller 0x0037FAC6.
// Link: minimal _STL view (no <map>) emits only the row; the full header also
// emitted find/end/operator!=/less COMDATs that lost (first copy is the
// speed-built stlport_map_int_int.obj). Direct _M_find plus header compare
// reproduces retail's inlined find (!= end) shape (Rva005D62E8 precedent).
#include "FormationAssistant.h"
namespace _STL {
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class T> class allocator
{
};
template <class V> struct _Rb_tree_node;
template <class K, class V, class KOV, class Cmp, class Alloc> class _Rb_tree
{
	friend int ::FormationAssistant::rva00422D1C(int);
	typedef _Rb_tree_node<V> *_Link_type;
private:
	template <class KT> _Link_type _M_find(const KT &) const;
};
template <class K, class T, class C = less<K>, class A = allocator<pair<const K, T> > > class map;
}
typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;

// The map is retail 0x00A0319C, defined as raw storage g_Va00E0319C in
// FormationSelectionCriteriaRva00424185.cpp (constructed by the 0x007B02C3 initializer).
extern unsigned int g_Va00E0319C[3];

int FormationAssistant::rva00422D1C(int key)
{
	MapIntIntTree *mapIntIntTree = (MapIntIntTree *)g_Va00E0319C;
	_STL::_Rb_tree_node<IntIntPair> *node = mapIntIntTree->_M_find(key);
	if ((void *)node != *(void * *)mapIntIntTree)
		return *(int *)((char *)node + 0x14);
	return -1;
}
