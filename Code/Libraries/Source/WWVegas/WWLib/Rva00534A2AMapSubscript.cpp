// cl: /O1 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// Native534A2A..534AAC (132B) uses unsigned outer keys and a twelve-byte
// owning tree value. Pair5346BC copies first4 then calls tree534581; default
// construction33C432 and both teardown554FA are independently rowed.
// These template declarations are callable ABI views of existing providers.
// No mapped application type or pointer-value identity is inferred from the
// int/void* spelling on the shared empty-map constructor or insertion wrapper.
// A direct default-map temporary preserves constructor EAX for pair creation;
// forwarding through a storage constructor needlessly recomputes its address.
struct Rva00053DC5 { ~Rva00053DC5(); };
namespace _STL {
template<class T> class allocator;
template<class T> struct less;
template<class T> struct _Select1st;
template<class T> struct _Nonconst_traits;
template<class A,class B> struct pair;
struct _Rb_tree_node_base {int color;_Rb_tree_node_base *parent,*left,*right;};
template<class T> struct _Rb_tree_node : _Rb_tree_node_base {};
template<class T,class Trait> struct _Rb_tree_iterator {
 _Rb_tree_node_base *_M_node;typedef _Rb_tree_node<T>* _Link_type;
 _Rb_tree_iterator(_Link_type n):_M_node(n){}
 _Rb_tree_iterator(const _Rb_tree_iterator& n):_M_node(n._M_node){}
};
template<class K,class V,class S,class C,class A> class _Rb_tree {
public:typedef _Rb_tree_node<V>* _Link_type;
private:_Link_type _M_lower_bound(const K&)const;
public:
 _Rb_tree_iterator<V,_Nonconst_traits<V> > lower_bound(const K&key){return _Rb_tree_iterator<V,_Nonconst_traits<V> >(_M_lower_bound(key));}
};
template<class K,class V,class C,class A> class map {
 void *header;unsigned int count;int comparator;
public:
 typedef pair<const K,V> value_type;
 typedef _Rb_tree_iterator<value_type,_Nonconst_traits<value_type> > iterator;
 map();__forceinline ~map(){reinterpret_cast<Rva00053DC5*>(this)->~Rva00053DC5();}
 iterator insert(iterator,const value_type&);
};
}
typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > IntTree;
typedef _STL::map<int,void*,_STL::less<int>,_STL::allocator<_STL::pair<const int,void*> > > EmptyMap;
struct TreeStorage534 {
 unsigned int words[3];
 ~TreeStorage534(){reinterpret_cast<Rva00053DC5*>(this)->~Rva00053DC5();}
};
struct Rva005344C0 {
 int first;TreeStorage534 second;
 Rva005344C0(const int *,const IntTree &);
};
typedef _STL::map<unsigned int,void*,_STL::less<unsigned int>,_STL::allocator<_STL::pair<const unsigned int,void*> > > InsertMap;
namespace _STL {template<> InsertMap::iterator InsertMap::insert(InsertMap::iterator,const InsertMap::value_type&);}
typedef _STL::_Rb_tree<unsigned int,_STL::pair<const unsigned int,void*>,_STL::_Select1st<_STL::pair<const unsigned int,void*> >,_STL::less<unsigned int>,_STL::allocator<_STL::pair<const unsigned int,void*> > > BoundTree;
namespace _STL {template<> BoundTree::_Link_type BoundTree::_M_lower_bound(const unsigned int&) const;}
class Rva00534A2A {
 _STL::_Rb_tree_node_base *head;
public:TreeStorage534 &subscript(const unsigned int&);
};
TreeStorage534 &Rva00534A2A::subscript(const unsigned int &key) {
 _STL::_Rb_tree_node_base *node=reinterpret_cast<BoundTree*>(this)->lower_bound(key)._M_node;
 if(node==head || key<*reinterpret_cast<unsigned int*>((char*)node+16)) {
  node=reinterpret_cast<InsertMap*>(this)->insert(InsertMap::iterator(static_cast<InsertMap::iterator::_Link_type>(node)),reinterpret_cast<const InsertMap::value_type&>(Rva005344C0(reinterpret_cast<const int*>(&key),reinterpret_cast<const IntTree&>(EmptyMap()))))._M_node;
 }
 return *reinterpret_cast<TreeStorage534*>((char*)node+20);
}
