// cl: /O1 /arch:SSE2 /D_STLP_USE_MALLOC /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// platformsdk
// stlport46
// Reference shape: ZH PlayerTemplate's automatic member copy, reconciled
// against target1FE352/957 and PlayerTemplate store/vector476-byte callers.
// Base copy3664DD resets the override links. The native EH map at9114D0
// independently proves37 owned-subobject states, including+1C8 destructor
// 360D26 and+2C root cleanup49B47C; these are target facts, not donor names.
// Field meanings remain neutral. Existing container/handle instantiations
// supply byte-proven constructor ABIs. Coord adapter inherits canonical data.

#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <map>
#include <hash_map>
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <vector>
#include <windows.h>
#include <string.h>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<void*> members otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
unsigned vector<void*>::size() const
{ return (unsigned)(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
// The bucket copy in _M_copy_from inlines const begin() and operator[] as
// retail's does; dllimport+forceinline emits no external copy of either.
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void *const &vector<void *>::operator[](size_t __n) const
{ return *(begin() + __n); }
}
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/Common/Overridable.h"
class Rva003B0E83 {public:Rva003B0E83*rva003B0E83();};
struct S3Handicap {__forceinline S3Handicap(){((Rva003B0E83*)this)->rva003B0E83();} int words[4];};
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;
#include "../../Include/Common/BfmeXfer.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Inlined at every call site; dllimport+forceinline keeps this TU's /O1 copy,
// which differs from retail's kept one, out of the object.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void vector<void *, allocator<void *> >::insert(void **__pos, size_t __n, void *const &__x)
{ _M_fill_insert(__pos, __n, __x); }
}

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}
// Default construction is inlined at every use. Suppress its unused external
// copy, as with the inline-only container adapters below.
class S3Money : public Snapshot { public: int words[2];
 __declspec(dllimport) __forceinline S3Money(){words[0]=0;words[1]=0;}
 __forceinline S3Money(const S3Money&s3Money){words[0]=s3Money.words[0];words[1]=s3Money.words[1];}
 virtual ~S3Money() {}
 virtual void loadPostProcess();
 virtual const char* GetSnapshotName()const;
 virtual void xfer(Xfer*);
};
struct S3Coord { float x,y,z; };
struct Rva004216D3Coord : Coord3D {
 Rva004216D3Coord();
 Rva004216D3Coord(const Rva004216D3Coord &r) {x=r.x;y=r.y;z=r.z;}
 __declspec(noinline) ~Rva004216D3Coord() {}
};
struct Rva001FDCE1Record {Rva001FDCE1Record();Rva001FDCE1Record(const Rva001FDCE1Record&);~Rva001FDCE1Record();Rva001FDCE1Record&operator=(const Rva001FDCE1Record&);char bytes[1];bool operator<(const Rva001FDCE1Record&)const;bool operator==(const Rva001FDCE1Record&)const;};
struct Rva001FDAB0Less {bool operator()(int,int)const;};
// Retail calls the rowed bucket-copy helper at 0x001FDC0F. Keep this
// private container view from emitting another copy with an undefined node
// constructor; its declaration preserves the native member-call ABI.
namespace _STL { template <> void hashtable<pair<const int, Rva001FDCE1Record>, int, hash<int>, _Select1st<pair<const int, Rva001FDCE1Record> >, equal_to<int>, allocator<pair<const int, Rva001FDCE1Record> > >::_M_copy_from(const hashtable &); }
#pragma comment(linker, "/alternatename:?_M_copy_from@?$hashtable@U?$pair@$$CBHURva001FDCE1Record@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva001FDCE1Record@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva001FDCE1Record@@@_STL@@@2@@_STL@@AAEXABV12@@Z=?_M_copy_from@?$hashtable@U?$pair@$$CBHURva001FDC0FRecord@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva001FDC0FRecord@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva001FDC0FRecord@@@_STL@@@2@@_STL@@AAEXABV12@@Z")
namespace _STL { template <> hashtable<pair<const int, Rva001FDCE1Record>, int, hash<int>, _Select1st<pair<const int, Rva001FDCE1Record> >, equal_to<int>, allocator<pair<const int, Rva001FDCE1Record> > >::_Node *hashtable<pair<const int, Rva001FDCE1Record>, int, hash<int>, _Select1st<pair<const int, Rva001FDCE1Record> >, equal_to<int>, allocator<pair<const int, Rva001FDCE1Record> > >::_M_new_node(const pair<const int, Rva001FDCE1Record> &); }
namespace _STL { template <> hashtable<pair<const int, Rva001FDCE1Record>, int, hash<int>, _Select1st<pair<const int, Rva001FDCE1Record> >, equal_to<int>, allocator<pair<const int, Rva001FDCE1Record> > >::~hashtable(); }
namespace _STL { template <> void _Destroy<pair<const int, Rva001FDCE1Record> >(pair<const int, Rva001FDCE1Record> *); }
// bfme link decl-only begin
// With the Rva wrapper copy ctors imported (no local COMDAT) the /O1 chain no
// longer forces _M_clone_node out of line, so the tree _M_copy would inline it
// (a 144B body; retail's copy is the 115B one that calls it). Keep
// _M_clone_node out of line so _M_copy stays the retail shape. Owned by the
// other tree units (identical bodies, no retail address).
namespace _STL { template <> _Rb_tree_node<pair<const int, void*> > * _Rb_tree<int, pair<const int, void*>, _Select1st<pair<const int, void*> >, less<int>, allocator<pair<const int, void*> > >::_M_clone_node(_Rb_tree_node<pair<const int, void*> > *); }
namespace _STL { template <> _Rb_tree_node<pair<const int, void*> > * _Rb_tree<int, pair<const int, void*>, _Select1st<pair<const int, void*> >, Rva001FDAB0Less, allocator<pair<const int, void*> > >::_M_clone_node(_Rb_tree_node<pair<const int, void*> > *); }
// bfme link decl-only end
enum ScienceType { S3ScienceForce=0x7fffffff };
struct Rva0021C21BElement { char bytes[4]; };
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element &)const;bool operator==(const Rva0026F4F4Element &)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}

struct TreeHintPayload003012F0 {unsigned a,b,c;TreeHintPayload003012F0(const TreeHintPayload003012F0 &r):a(r.a),b(r.b),c(r.c){}};
class BfmeFixedStorage0004543D {public:BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&);char data[28];};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
struct Rva003623E5Member {void initFromStorages(BfmeFixedStorage0004543D,BfmeFixedStorage0004543D);};
struct Rva00360D26Member {Rva00360D26Member();~Rva00360D26Member();unsigned word;};
void __cdecl Rva00030830GameFree(void *);
class OpaqueRefCounted {public:virtual ~OpaqueRefCounted();void Release_Ref();long refs;};
struct Rva0010F149Handle {
 __forceinline Rva0010F149Handle():referent(0){}
 __declspec(noinline) __declspec(nothrow) Rva0010F149Handle(const Rva0010F149Handle &r);
 ~Rva0010F149Handle() {if(referent)referent->Release_Ref();}
 OpaqueRefCounted *referent;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0010F149Handle::Rva0010F149Handle(const Rva0010F149Handle &r):referent(r.referent) {if(referent)InterlockedIncrement(&referent->refs);}

// ?bfmeAnchorRva0010F149HandleCtor absent-from-retail
void *bfmeAnchorRva0010F149HandleCtor(void *where, const Rva0010F149Handle &r)
{
	return ::new (where) Rva0010F149Handle(r);
}
// ?Rva001FD42B::Rva001FD42B present-unmatched
struct Rva001FD42B { __forceinline Rva001FD42B(){typedef _STL::map<int,void*> T;((T*)this)->T::map();} __declspec(dllimport) __forceinline Rva001FD42B(const Rva001FD42B &r) {typedef _STL::map<int,void*> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD42B(); void *data[3];};
// ?Rva001FD458::Rva001FD458 present-unmatched
struct Rva001FD458 { __forceinline Rva001FD458(){typedef _STL::map<int,void*,Rva001FDAB0Less> T;((T*)this)->T::map();} __declspec(dllimport) __forceinline Rva001FD458(const Rva001FD458 &r) {typedef _STL::map<int,void*,Rva001FDAB0Less> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD458(); void *data[3];};
// ?Rva000427195::Rva000427195 present-unmatched
struct Rva000427195 { __forceinline Rva000427195(){typedef _STL::hash_map<int,Rva001FDCE1Record> T;((T*)this)->T::hash_map();} __declspec(dllimport) __forceinline Rva000427195(const Rva000427195 &r) {typedef _STL::hash_map<int,Rva001FDCE1Record> T;((T*)this)->T::hash_map(*reinterpret_cast<const T*>(&r));} ~Rva000427195(); void *data[5];};
// The hash_map copy-ctor COMDAT (a matched row, 0x001FDF14/18) was previously
// emitted as a side effect of the Rva000427195 copy ctor above; with that now
// dllimport this anchor keeps the matched external copy emitted.
// ?bfmeAnchorHashmapCopyCtor absent-from-retail
__declspec(noinline) void *bfmeAnchorHashmapCopyCtor(void *where, const Rva000427195 &r)
{
	typedef _STL::hash_map<int,Rva001FDCE1Record> T;
	return ::new (where) T(*reinterpret_cast<const T*>(&r));
}
extern template const unsigned int &_STL::max<unsigned int>(const unsigned int &,const unsigned int &);
namespace _STL {
template<> inline _Vector_base<ScienceType,allocator<ScienceType> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
template<> inline _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
// The constructors inline vector<unsigned>(alloc) and call its nothrow base out of
// line, as retail does; dllimport+forceinline emits no external vector copy.
template <> __declspec(noinline) inline
_Vector_base<unsigned, allocator<unsigned> >::_Vector_base(const allocator<unsigned> &__a) throw()
: _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0) {}
template <> __declspec(dllimport) __forceinline
vector<unsigned, allocator<unsigned> >::vector(const allocator<unsigned> &__a)
: _Vector_base<unsigned, allocator<unsigned> >(__a) {}
}
struct Rva003B0E5DRecord {Rva003B0E5DRecord();AsciiString text;int a,b,c;};
struct BfmeObject476 : Overridable {
 BfmeObject476();
 virtual ~BfmeObject476();
 int unknown10;
 UnicodeString unknown14;
 AsciiString unknown18;
 S3Handicap unknown1c;
 S3Money unknown2c;
 S3Coord unknown38;
 AsciiString unknown44;
 AsciiString unknown48[10];
 Rva004216D3Coord unknown70[10];
 _STL::vector<AsciiString> unknowne8;
 Rva001FD42B unknownf4;
 Rva000427195 unknown100;
 Rva001FD458 unknown114;
 _STL::vector<ScienceType> unknown120,unknown12c;
 AsciiString unknown138,unknown13c,unknown140,unknown144;
 int unknown148;
 AsciiString unknown14c;
 bool unknown150,unknown151;
 Rva003B0E5DRecord unknown154;
 AsciiString unknown164,unknown168,unknown16c,unknown170,unknown174,unknown178,unknown17c;
 _STL::vector<AsciiString> unknown180,unknown18c,unknown198;
 Rva0010F149Handle unknown1a4,unknown1a8,unknown1ac;
 AsciiString unknown1b0,unknown1b4,unknown1b8;
 bool unknown1bc;
 AsciiString unknown1c0,unknown1c4;
 Rva00360D26Member unknown1c8;
 _STL::vector<unsigned int> unknown1cc;
 AsciiString unknown1d8;
};


// Compiler emission witness; no retail body is claimed for this wrapper.
// ?S3CopyConstruct476 absent-from-retail
BfmeObject476 *S3CopyConstruct476(void *where,const BfmeObject476 &src) { return new(where) BfmeObject476(src); }

typedef char BfmeObject476Extent[sizeof(BfmeObject476)==476?1:-1];

BfmeObject476::~BfmeObject476() {}

void S3Money::loadPostProcess() {}
const char *S3Money::GetSnapshotName() const {return "Money";}
void S3Money::xfer(Xfer *xfer) {xfer->Version1();*xfer == *(unsigned int*)&words[0];}

BfmeObject476::BfmeObject476():unknown10(0),unknown148(0),unknown150(false),unknown151(false),unknown1bc(false) {
unknown18="";unknown44="";unknown138="";unknown13c="";unknown140="";unknown144="";unknown14c="";
unknown38.x=unknown38.y=unknown38.z=0;
unknown17c="";unknown164="";unknown168="";unknown16c="";unknown170="";unknown174="";unknown178="";unknown17c="";
unknown180.clear();unknown1b0="";unknown1b4="";unknown1b8="";
((Rva003623E5Member*)&unknown1c8)->initFromStorages(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE),*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
memset(unknown70,0,sizeof(unknown70));}

// Default constructor: target [1FEB8B,1FEEA3) is 792B through RET.
// Same aggregate as the copied476-byte record. The additional16-byte member
// ctor3B0E5D has its own24-byte RET boundary before3B0E75.

// WB-named PlayerTemplate parser uses this actual class lifetime spelling.
// Its476-byte target view is identical to the earlier neutral vector element.
class PlayerTemplate : Overridable {
public:
 PlayerTemplate();
 virtual ~PlayerTemplate();
 int unknown10;
 UnicodeString unknown14;
 AsciiString unknown18;
 S3Handicap unknown1c;
 S3Money unknown2c;
 S3Coord unknown38;
 AsciiString unknown44;
 AsciiString unknown48[10];
 Rva004216D3Coord unknown70[10];
 _STL::vector<AsciiString> unknowne8;
 Rva001FD42B unknownf4;
 Rva000427195 unknown100;
 Rva001FD458 unknown114;
 _STL::vector<ScienceType> unknown120,unknown12c;
 AsciiString unknown138,unknown13c,unknown140,unknown144;
 int unknown148;
 AsciiString unknown14c;
 bool unknown150,unknown151;
 Rva003B0E5DRecord unknown154;
 AsciiString unknown164,unknown168,unknown16c,unknown170,unknown174,unknown178,unknown17c;
 _STL::vector<AsciiString> unknown180,unknown18c,unknown198;
 Rva0010F149Handle unknown1a4,unknown1a8,unknown1ac;
 AsciiString unknown1b0,unknown1b4,unknown1b8;
 bool unknown1bc;
 AsciiString unknown1c0,unknown1c4;
 Rva00360D26Member unknown1c8;
 _STL::vector<unsigned int> unknown1cc;
 AsciiString unknown1d8;
};
PlayerTemplate::PlayerTemplate():unknown10(0),unknown148(0),unknown150(false),unknown151(false),unknown1bc(false) {
unknown18="";unknown44="";unknown138="";unknown13c="";unknown140="";unknown144="";unknown14c="";
unknown38.x=unknown38.y=unknown38.z=0;
unknown17c="";unknown164="";unknown168="";unknown16c="";unknown170="";unknown174="";unknown178="";unknown17c="";
unknown180.clear();unknown1b0="";unknown1b4="";unknown1b8="";
((Rva003623E5Member*)&unknown1c8)->initFromStorages(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE),*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
memset(unknown70,0,sizeof(unknown70));}

PlayerTemplate::~PlayerTemplate() {}
