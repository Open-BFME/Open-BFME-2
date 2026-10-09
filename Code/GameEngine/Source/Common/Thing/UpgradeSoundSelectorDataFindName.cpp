// cl: /O1 /Oy- /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native4CB2FB..4CB33356B and WB1272D40187B prove named sound lookup.
// Existing selector slot4CB48A proves the entry extent384 and 8-byte result.
// Target facts: map370; node key10/value14; absent id=-1/ref=0 and found
// id/reference copy with atomic AddRef. Rva002390CB owns the byte-verified
// 10B default initializer4CEE6E and29B copy2390CB; both cannot throw.
// Rva002C99FB is the established caller return-carrier name. Its composed
// member is a TU ABI view of those independently proven eight-byte values;
// original concrete value type and entry class name remain unknown.
// The mapped type is unused by78B AsciiString _M_find; this narrow lookup
// view reuses its owned instantiation rather than assigning a second pin.
#include "ascii_string.h"
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva002390CB {
public:
 __declspec(nothrow) Rva002390CB();
 __declspec(nothrow) Rva002390CB(const Rva002390CB &);
 ~Rva002390CB() { if (ref) ref->Release_Ref(); }
 int id; OpaqueRefCounted *ref;
};
struct Rva002C99FB {
 Rva002390CB value;
 __forceinline Rva002C99FB() {}
 __forceinline Rva002C99FB(const Rva002C99FB &v):value(v.value) {}
};
struct Rva004CB51CEntry;
namespace _STL {
template<class A,class B> struct pair {};
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class T> struct _Rb_tree_node;
template<class K,class V,class KeyOfValue,class Compare,class Alloc> class _Rb_tree {
 friend struct ::Rva004CB51CEntry;
 template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
};
}
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,AsciiString>,_STL::_Select1st<_STL::pair<const AsciiString,AsciiString> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,AsciiString> > > FindTree;
struct NativeTree { void *header; unsigned count; unsigned comparator; };
struct Rva004CB51CEntry {
 Rva002C99FB rva004CB2FB(const AsciiString &);
 char unknown[0x370]; NativeTree map;
};
Rva002C99FB Rva004CB51CEntry::rva004CB2FB(const AsciiString &name) {
 void *node=reinterpret_cast<const FindTree *>(&map)->_M_find<AsciiString>(name);
 if(node!=map.header) return *reinterpret_cast<const Rva002C99FB *>((char *)node+0x14);
 return Rva002C99FB();
}
