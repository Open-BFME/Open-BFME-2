// cl: /O1 /Oy- /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native0033D3E8..0033D433 RET8 (75B), called by matched Drawable274CD8.
// Existing receiver spelling Rva00239435 is retained. Native accesses prove
// map388, node key10/value14 and an eight-byte returned shared-reference record.
// Original receiver and application value names remain unknown.
// Reuses the target-based reference-record and key-only tree views in
// UpgradeSoundSelectorDataFindName.cpp (its getter4CB2FB is already verified).
// Empty keys and map misses construct the existing10B default; hits call the
// existing29B copy2390CB. These constructors cannot throw, so no EH frame.
// Canonical StringBase<char>::isEmpty supplies the native direct20B call;
// AsciiString's inline isEmpty would change the body. The78B tree lookup's
// AsciiString mapped type is unused by this key-only algorithm. No new pins.
#include "ascii_string.h"
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva002390CB {
public:
 __declspec(nothrow) Rva002390CB();
 __declspec(nothrow) Rva002390CB(const Rva002390CB &);
 ~Rva002390CB() { if (ref) ref->Release_Ref(); }
 int id; OpaqueRefCounted *ref;
};
class Rva00239435;
namespace _STL {
template<class A,class B> struct pair {};
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class T> struct _Rb_tree_node;
template<class K,class V,class KeyOfValue,class Compare,class Alloc> class _Rb_tree {
 friend class Rva00239435;
 template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
};
}
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,AsciiString>,_STL::_Select1st<_STL::pair<const AsciiString,AsciiString> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,AsciiString> > > FindTree;
struct NativeTree { void *header; unsigned count; unsigned comparator; };
class Rva00239435 {public:Rva002390CB rva0033D3E8(const AsciiString&);char pad[0x388];NativeTree map;};
Rva002390CB Rva00239435::rva0033D3E8(const AsciiString&name){
 if(((const StringBase<char>*)&name)->isEmpty())return Rva002390CB();
 void*node=((const FindTree*)&map)->_M_find<AsciiString>(name);
 if(node==map.header)return Rva002390CB();
 return *(const Rva002390CB*)((char*)node+0x14);
}
