// ?rva0060147B@Rva0060126D@@QAEAAV?$_Rb_tree@URva00600A40Element@@U1@U?$_Identity@URva00600A40Element@@@_STL@@U?$less@URva00600A40Element@@@3@V?$allocator@URva00600A40Element@@@3@@_STL@@PBD@Z
// partial score=0.9 date=2026-10-07
// Native 0x0060147B-0x00601522 167B: strcmp lookup; intern missing key
// through 0x006054AF at VA 0x00E06E60; construct empty nested tree;
// make/copy key-tree pair and insert; three nested-tree cleanups.
// Original application owner and nested element semantics are unknown.
// Default constructor uses the pre-existing folded AsciiString set ctor
// as a receiver ABI view only; cleanup is the proven primitive-tree dtor.
// cl: /O1 /EHsc /MD
// Native constructors copy a four-byte key then construct the twelve-byte
// tree at +4. Their call is to the full tree-copy entry 0x00600A40;
// EDX is unused. The prior fastcall/mid-entry interpretation was incorrect.
class AsciiString;
class Rva006007A5 { public: ~Rva006007A5(); };
void * __cdecl operator new(unsigned int,void *p) { return p; }
namespace _STL {
template<class K,class C,class A> class set { public: set(); };
template<class T> struct _Identity {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K,class V,class KeyOfValue,class Compare,class Alloc> class _Rb_tree {
public:
 _Rb_tree(const _Rb_tree &);
 __forceinline _Rb_tree() { new(this) set<AsciiString,less<AsciiString>,allocator<AsciiString> >; }
 __forceinline ~_Rb_tree() { reinterpret_cast<Rva006007A5 *>(this)->~Rva006007A5(); }
 void *header; int count; char comparator; char pad[3];
};
}
struct Rva00600A40Element;
typedef _STL::_Rb_tree<Rva00600A40Element,Rva00600A40Element,_STL::_Identity<Rva00600A40Element>,_STL::less<Rva00600A40Element>,_STL::allocator<Rva00600A40Element> > NativeNestedTree;
struct Rva00600F9CElement {
 __forceinline ~Rva00600F9CElement() {}
 const char *key;
 NativeNestedTree tree;
 Rva00600F9CElement(const Rva00600F9CElement &);
 Rva00600F9CElement(const char *const &,const NativeNestedTree &);
};
Rva00600F9CElement __cdecl Rva00600F5B(const char *const &k,const NativeNestedTree &t);

namespace _STL {
template<class A,class B> struct pair {};
template<class T> struct _Select1st {};
}
struct Rva00603A00Mapped { unsigned word; };
struct Rva006038D4Less {};
struct Rva0060126D;
namespace _STL { template<class T> struct _Rb_tree_node; }
namespace _STL {
template<> class _Rb_tree<const char*,pair<const char *const,Rva00603A00Mapped>,_Select1st<pair<const char *const,Rva00603A00Mapped> >,Rva006038D4Less,allocator<pair<const char *const,Rva00603A00Mapped> > > {
 friend struct ::Rva0060126D;
private:
 template<class K> _Rb_tree_node<pair<const char *const,Rva00603A00Mapped> > *_M_find(const K&) const;
};
}
typedef _STL::_Rb_tree<const char*,_STL::pair<const char *const,Rva00603A00Mapped>,_STL::_Select1st<_STL::pair<const char *const,Rva00603A00Mapped> >,Rva006038D4Less,_STL::allocator<_STL::pair<const char *const,Rva00603A00Mapped> > > FindTree;
struct Rva006013B7Pair { void *first; bool second; Rva006013B7Pair(void *p,bool b) : first(p),second(b) {} };
struct Rva006054AF { void *rva006054AF(const char *); };
struct Rva0060126D {
 void *header;
 Rva006013B7Pair rva006013B7(const Rva00600F9CElement &);
 NativeNestedTree &rva0060147B(const char *name);
};
__forceinline const Rva00600F9CElement &KeepPair(const Rva00600F9CElement &v) { return v; }
NativeNestedTree &Rva0060126D::rva0060147B(const char *name) {
 void *node=reinterpret_cast<const FindTree *>(this)->_M_find<const char *>(name);
 if (node==header) {
  name=(const char *)reinterpret_cast<Rva006054AF *>(0x00E06E60)->rva006054AF(name);
  node=rva006013B7(Rva00600F9CElement(KeepPair(Rva00600F5B(name,NativeNestedTree())))).first;
 }
 return *reinterpret_cast<NativeNestedTree *>((char *)node+0x14);
}
