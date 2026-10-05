// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?Rva00422D1CGet@@YGHH@Z retail 0x00422D1C 34B.
// Global map<int,int> lookup: find key via rowed _M_find 0x00388F63,
// return mapped value at node+0x14 or -1 when iterator equals end.
// Evidence: retail lea eax [esp+4] push eax mov ecx <global> call _M_find,
// cmp eax [global] je or -1 else mov eax [eax+0x14] ret 4; caller 0x0037FAC6.
// Link: minimal _STL view (no <map>) emits only the row; the full header also
// emitted find/end/operator!=/less COMDATs that lost (first copy is the
// speed-built stlport_map_int_int.obj). Direct _M_find plus header compare
// reproduces retail's inlined find (!= end) shape (Rva005D62E8 precedent).
int __stdcall Rva00422D1CGet(int key);
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
	friend int __stdcall ::Rva00422D1CGet(int);
	typedef _Rb_tree_node<V> *_Link_type;
private:
	template <class KT> _Link_type _M_find(const KT &) const;
};
template <class K, class T, class C = less<K>, class A = allocator<pair<const K, T> > > class map;
}
typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;

extern _STL::map<int, int> g_00E0319C;

int __stdcall Rva00422D1CGet(int key)
{
	MapIntIntTree *t = (MapIntIntTree *)&g_00E0319C;
	_STL::_Rb_tree_node<IntIntPair> *node = t->_M_find(key);
	if ((void *)node != *(void * *)t)
		return *(int *)((char *)node + 0x14);
	return -1;
}
