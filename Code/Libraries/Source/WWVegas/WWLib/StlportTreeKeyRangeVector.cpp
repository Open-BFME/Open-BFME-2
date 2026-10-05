// cl: /O1 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 range constructor and initializer from BFME1 reference
// 6583b3c1ff21db4a561285717028fdafc780b7db inputs/vendor/stlport/stl/_vector.h.
// Native5E60D1..5E6110 RET12 constructs vector<int> from two4B node cursors
// and allocator. 5E5F43 counts tree nodes then copies their offset16 values.
// The opaque iterator projects keys only: original set/map and payload unknown.
// Native40B5E59FC retains the null placement guard, unlike this header's
// __copy optimization. Its specialization independently matches every byte;
// frame omission affects that leaf only. The existing Rva005E59FCCopy owns
// these same40B, so its explicit folded alias contributes zero unique bytes.
#include <vector>
#include <map>
#include <new>
struct Rva005E59FCKeyIterator {
 typedef _STL::bidirectional_iterator_tag iterator_category;
 typedef int value_type;
 typedef int difference_type;
 typedef int *pointer;
 typedef int &reference;
 _STL::_Rb_tree_node_base *node;
 int &operator*() const {return *(int*)((char*)node+16);}
 Rva005E59FCKeyIterator &operator++(){node=_STL::_Rb_global<bool>::_M_increment(node);return *this;}
 Rva005E59FCKeyIterator &operator--(){node=_STL::_Rb_global<bool>::_M_decrement(node);return *this;}
 bool operator==(const Rva005E59FCKeyIterator&b)const{return node==b.node;}
 bool operator!=(const Rva005E59FCKeyIterator&b)const{return node!=b.node;}
};
namespace _STL {
#pragma optimize("y", on)
template<> __declspec(noinline) int *__uninitialized_copy(Rva005E59FCKeyIterator first, Rva005E59FCKeyIterator last,int *result,const __true_type&) {
 _Rb_tree_node_base *n=first.node;
 int *d=result;
 for(;n!=last.node;n=_Rb_global<bool>::_M_increment(n),++d) {if(d) *d=*(int*)((char*)n+16);}
 return d;
}
#pragma optimize("", on)
}
// The non-owning key copy is already supplied by Rva005F4F59Copy (27B),
// whose copy_aux29B and tree traversal37B providers are fully rowed.
// Both interfaces pass the same two4B node addresses and int destination;
// the opaque cursor has no ctor/dtor or hidden state. No template owner or
// application payload identity is inferred from this ABI-compatible view.
namespace _STL {
template<> int *copy(Rva005E59FCKeyIterator,Rva005E59FCKeyIterator,int *);
}
#pragma comment(linker, "/alternatename:??$copy@URva005E59FCKeyIterator@@PAH@_STL@@YAPAHURva005E59FCKeyIterator@@0PAH@Z=?Rva005F4F59Copy@@YAPAHPAU_Rb_tree_node_base@_STL@@0PAH@Z")
// ?rvaKeyRangeAnchor absent-from-retail
void rvaKeyRangeAnchor(void *memory, Rva005E59FCKeyIterator first, Rva005E59FCKeyIterator last,const _STL::allocator<int>& a) {
 new(memory) _STL::vector<int>(first,last,a);
}

// ?rvaKeyAssignAnchor absent-from-retail
void rvaKeyAssignAnchor(_STL::vector<int> *v, Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last,const _STL::forward_iterator_tag&t) {
 v->_M_assign_aux(first,last,t);
}

// Force-emit assign false-type dispatch (22B ret 0xC @0x005F50A3) and public
// assign (22B ret 8 @0x005F50D3); both forward to matched _M_assign_aux @0x005F4F74.
template void _STL::vector<int>::_M_assign_dispatch(Rva005E59FCKeyIterator, Rva005E59FCKeyIterator, const _STL::__false_type&);
// ?rvaKeyAssignPublic absent-from-retail
void rvaKeyAssignPublic(_STL::vector<int> *v, Rva005E59FCKeyIterator first, Rva005E59FCKeyIterator last) {
  v->assign(first, last);
}
