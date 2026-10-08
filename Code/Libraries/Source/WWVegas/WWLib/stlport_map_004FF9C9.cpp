// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native4FF9B6..4FF9C9 and 4FF9C9..4FF9DC are the same int-key lookup
// shape, returning node+28 and node+34 respectively. Both call the independently
// rowed 56-byte int-key _M_find at388F63; it observes no mapped-value payload.
// WB12FFA20 identifies the first role as LWAIWorldInformation::GetHeroArmies;
// the actual mapped and return types remain unknown, so keep the RVA spelling.
// These are partial receiver/call views, not full owner or allocation layouts.
// Directly call the existing provider; do not emit competing <map> helpers.
class Rva004FF9B6;
class Rva004FF9C9;
namespace _STL {
template<class A,class B> struct pair { A first; B second; };
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class T> struct _Rb_tree_node;
template<class K,class V,class S,class C,class A> class _Rb_tree {
 friend class ::Rva004FF9B6;
 friend class ::Rva004FF9C9;
 template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
};
}
typedef _STL::pair<const int,int> IntIntPair;
typedef _STL::_Rb_tree<int,IntIntPair,_STL::_Select1st<IntIntPair>,_STL::less<int>,_STL::allocator<IntIntPair> > IntIntTree;
class Rva004FF9B6 {
 char unknown00[4];
 IntIntTree tree;
public:
 void *rva004FF9B6(int key);
};
void *Rva004FF9B6::rva004FF9B6(int key) {
 return (char*)tree._M_find(key)+0x28;
}
class Rva004FF9C9 {
 char unknown00[4];
 IntIntTree tree;
public:
 void *rva004FF9C9(int key);
};
void *Rva004FF9C9::rva004FF9C9(int key) {
 return (char*)tree._M_find(key)+0x34;
}
