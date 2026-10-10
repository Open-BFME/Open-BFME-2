// ?Rva00058DC6Xfer@@YAPAVXfer@@PAV1@PAV?$set@VAsciiString@@U?$less@VAsciiString@@@_STL@@V?$allocator@VAsciiString@@@3@@_STL@@@Z
// partial score=0.9913419913419913 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Current isolated whole231B proof has no unresolved names; exactly two bytes differ.
// +0x0C allocates14 instead of0C, +0xB9 addresses result home20 instead of18.
// EHsc/EHs/EHc-/EHc and O2+Os+Ob1/Ob2/G6 preserve this wall; EHa/Og- diverge.
// Genuine iterator constructors and pair copy/no-destructor ABI are retained.
// This is a source-level ABI view of real STLport, still awaiting normal integration.

// Native 00058DC6..00058EAD, WB7B49F0: set<AsciiString> transfer.
// Matched 0005CC28 map serializer and STLport _pair.h are structural guides.
// Save walks tree nodes; load requires empty set, transfers strings and inserts.
// Correct non-POD pair return ABI yields231B; frame remains14 vs native0C.
#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

namespace _STL {
struct _Rb_tree_node_base{int color;_Rb_tree_node_base*parent,*left,*right;};
template<class T>struct _Const_traits;
template<class T,class Traits>struct _Rb_tree_iterator{_Rb_tree_node_base*node; _Rb_tree_iterator(){} _Rb_tree_iterator(_Rb_tree_node_base*n):node(n){} _Rb_tree_iterator(const _Rb_tree_iterator&o):node(o.node){} };
template<class T>struct _Rb_global{static _Rb_tree_node_base*_M_increment(_Rb_tree_node_base*);};
template<class T>struct less;
template<class T>class allocator;
template<class A,class B>struct pair{pair():first(A()),second(B()){} pair(const pair&o):first(o.first),second(o.second){} A first;B second;};
template<class K,class C,class Al>class set{public:typedef _Rb_tree_iterator<K,_Const_traits<K> > iterator;pair<iterator,bool>insert(const K&);_Rb_tree_node_base*header;unsigned count;};
}
typedef _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > AsciiStringSet;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version); // +0x28
	virtual Xfer &xferTypeName(const char *const &name); // +0x2C
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *value); virtual void slot28(); virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value); // +0x78
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

Xfer *Rva00058DC6Xfer(Xfer *xfer, AsciiStringSet *set) {
 XferVersion version;version.m_version=1;version.m_currentVersion=1;
 xfer->xferVersion(&version);
 unsigned count=set->count;
 xfer->xferTypeName("std::set").xferUnsignedInt(&count);
 if(xfer->isSaving()) {
  _STL::_Rb_tree_node_base*last=set->header;
  for(_STL::_Rb_tree_node_base*cur=last->left;cur!=last;cur=_STL::_Rb_global<bool>::_M_increment(cur))
   xfer->xferAsciiString((AsciiString*)(cur+1));
 } else {
  if(set->count)throw XferException(4,"Set must be empty on load");
  AsciiString item;
  while(count--) {xfer->xferAsciiString(&item);set->insert(item);}
 }
 return xfer;
}
