// StringIntListMapSubscript
// partial score=0.94 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Ob2 /EHs /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Reference STLport4.5.3 pair and map subscript algorithms.
#include "ascii_string.h"
namespace _STL {
template<class T> class allocator {
public:
 allocator() throw() {}
 allocator(const allocator&) throw() {}
 template<class U> allocator(const allocator<U>&) throw() {}
 ~allocator() throw() {}
};
template<class T,class A> class _List_base {
 void *m_node;
public:
 _List_base(const A&);
 ~_List_base();
};
template<class T,class A> class list : public _List_base<T,A> {
public:
 __forceinline list(const A& a=A()) : _List_base<T,A>(a) {}
 list(const list&);
 ~list() {}
};
template<class K,class V> struct pair {
 K first; V second;
 pair(const K& a,const V& b) : first(a),second(b) {}
 ~pair() {}
};
template<class T> struct less {};
template<class T> struct _Select1st {};
template<class T> struct _Nonconst_traits {};
struct _Rb_tree_node_base {
 unsigned char color; char pad[3];
 _Rb_tree_node_base *parent,*left,*right;
};
template<class V> struct _Rb_tree_node : _Rb_tree_node_base { V value; };
struct _Rb_tree_base_iterator { _Rb_tree_node_base *_M_node; };
template<class V,class Traits> struct _Rb_tree_iterator : _Rb_tree_base_iterator {
 _Rb_tree_iterator(_Rb_tree_node_base *n) { _M_node=n; }
 _Rb_tree_iterator(const _Rb_tree_iterator& x) { _M_node=x._M_node; }
};
template<class K,class V,class KO,class C,class A> class _Rb_tree {
 template<class K2,class V2,class C2,class A2> friend class map;
private:
 _Rb_tree_node<V> *_M_lower_bound(const K&) const;
};
template<class K,class V,class C,class A> class map {
 _Rb_tree_node_base *m_header;
 unsigned int m_count;
 char m_comparatorStorage[4];
public:
 typedef pair<const K,V> value_type;
 typedef _Rb_tree_iterator<value_type,_Nonconst_traits<value_type> > iterator;
 V& operator[](const K&);
 iterator insert(iterator,const value_type&);
};
}
bool operator<(const AsciiString&,const AsciiString&);
struct TreeHintRef00217D4C {void *m_ptr;};
struct TreeHintOpaque002A484A {void *m_ptr;};
struct TreeHintOpaque005CA7ED {void *m_ptr;};
typedef _STL::pair<const AsciiString,TreeHintRef00217D4C> LowerPair;
typedef _STL::_Rb_tree<AsciiString,LowerPair,_STL::_Select1st<LowerPair>,_STL::less<AsciiString>,_STL::allocator<LowerPair> > LowerTree;
typedef _STL::list<int,_STL::allocator<int> > IntList;
typedef _STL::list<AsciiString,_STL::allocator<AsciiString> > AsciiList;
typedef _STL::pair<const AsciiString,IntList> IntPair;
typedef _STL::pair<const AsciiString,AsciiList> AsciiPair;
typedef _STL::map<AsciiString,IntList,_STL::less<AsciiString>,_STL::allocator<IntPair> > IntMap;
typedef _STL::map<AsciiString,AsciiList,_STL::less<AsciiString>,_STL::allocator<AsciiPair> > AsciiMap;
typedef _STL::pair<const AsciiString,TreeHintOpaque002A484A> OpaqueIntPair;
typedef _STL::map<AsciiString,TreeHintOpaque002A484A,_STL::less<AsciiString>,_STL::allocator<OpaqueIntPair> > OpaqueIntMap;
typedef _STL::pair<const AsciiString,TreeHintOpaque005CA7ED> OpaqueAsciiPair;
typedef _STL::map<AsciiString,TreeHintOpaque005CA7ED,_STL::less<AsciiString>,_STL::allocator<OpaqueAsciiPair> > OpaqueAsciiMap;
template<class V> struct NativeHintMap;
template<> struct NativeHintMap<IntList> { typedef OpaqueIntMap type; };
template<> struct NativeHintMap<AsciiList> { typedef OpaqueAsciiMap type; };
namespace _STL {
template<class K,class V,class C,class A>
V& map<K,V,C,A>::operator[](const K& key) {
 typedef typename NativeHintMap<V>::type NativeMap;
 typename NativeMap::iterator i(((_Rb_tree_node_base*)((LowerTree*)this)->_M_lower_bound(key)));
 if(i._M_node==m_header || operator<(key,((_Rb_tree_node<value_type>*)i._M_node)->value.first))
 {
  i=((NativeMap*)this)->insert(i,
      (const typename NativeMap::value_type&)value_type(key,V()));
 }
 return ((_Rb_tree_node<value_type>*)i._M_node)->value.second;
}
}
template IntPair::pair(const AsciiString&,const IntList&);
template AsciiPair::pair(const AsciiString&,const AsciiList&);
template IntList& IntMap::operator[](const AsciiString&);
template AsciiList& AsciiMap::operator[](const AsciiString&);
template IntPair::~pair();
