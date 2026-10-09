// cl: /O1 /arch:SSE2 /D_STLP_USE_MALLOC /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference shape: ZH PlayerTemplate's automatic member copy, reconciled
// against target1FE352/957 and PlayerTemplate store/vector476-byte callers.
// Base copy3664DD resets the override links. The native EH map at9114D0
// independently proves37 owned-subobject states, including+1C8 destructor
// 360D26 and+2C root cleanup49B47C; these are target facts, not donor names.
// Field meanings remain neutral. Existing container/handle instantiations
// supply byte-proven constructor ABIs. Coord adapter inherits canonical data.

#include <map>
#include <hash_map>
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class Rva001E3624 {public: virtual ~Rva001E3624(); Rva001E3624(const Rva001E3624 &); char data[12]; };
struct S3Handicap { int words[4]; };
class NestedInlineBase {public:
 // ?NestedInlineBase::~NestedInlineBase present-unmatched
 virtual ~NestedInlineBase() {}};
struct S3Money : NestedInlineBase { int words[2];
 // ?S3Money::S3Money present-unmatched
 __forceinline S3Money(const S3Money &r) {words[0]=r.words[0];words[1]=r.words[1];}
 };
struct S3Coord { float x,y,z; };
struct Rva004216D3Coord : Coord3D {
 Rva004216D3Coord(const Rva004216D3Coord &r) {x=r.x;y=r.y;z=r.z;}
 __declspec(noinline) ~Rva004216D3Coord() {}
};
struct Rva001FDCE1Record {Rva001FDCE1Record();Rva001FDCE1Record(const Rva001FDCE1Record&);~Rva001FDCE1Record();Rva001FDCE1Record&operator=(const Rva001FDCE1Record&);char bytes[1];bool operator<(const Rva001FDCE1Record&)const;bool operator==(const Rva001FDCE1Record&)const;};
struct Rva001FDAB0Less {bool operator()(int,int)const;};
enum ScienceType { S3ScienceForce=0x7fffffff };
struct Rva0021C21BElement { char bytes[4]; };
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element &)const;bool operator==(const Rva0026F4F4Element &)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}

struct TreeHintPayload003012F0 {unsigned a,b,c;TreeHintPayload003012F0(const TreeHintPayload003012F0 &r):a(r.a),b(r.b),c(r.c){}};
struct Rva00360D26Member {~Rva00360D26Member();unsigned word;};
void __cdecl Rva00030830GameFree(void *);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {public:virtual ~OpaqueRefCounted();void Release_Ref();long refs;};
struct Rva0010F149Handle {
 __declspec(noinline) __declspec(nothrow) Rva0010F149Handle(const Rva0010F149Handle &r);
 ~Rva0010F149Handle() {if(referent)referent->Release_Ref();}
 OpaqueRefCounted *referent;
};
Rva0010F149Handle::Rva0010F149Handle(const Rva0010F149Handle &r):referent(r.referent) {if(referent)InterlockedIncrement(&referent->refs);}
// ?Rva001FD42B::Rva001FD42B present-unmatched
struct Rva001FD42B { __forceinline Rva001FD42B(const Rva001FD42B &r) {typedef _STL::map<int,void*> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD42B(); void *data[3];};
// ?Rva001FD458::Rva001FD458 present-unmatched
struct Rva001FD458 { __forceinline Rva001FD458(const Rva001FD458 &r) {typedef _STL::map<int,void*,Rva001FDAB0Less> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD458(); void *data[3];};
// ?Rva000427195::Rva000427195 present-unmatched
struct Rva000427195 { __forceinline Rva000427195(const Rva000427195 &r) {typedef _STL::hash_map<int,Rva001FDCE1Record> T;((T*)this)->T::hash_map(*reinterpret_cast<const T*>(&r));} ~Rva000427195(); void *data[5];};
extern template const unsigned int &_STL::max<unsigned int>(const unsigned int &,const unsigned int &);
namespace _STL {
template<> inline _Vector_base<ScienceType,allocator<ScienceType> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
template<> inline _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
}
struct BfmeObject476 : Rva001E3624 {
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
 _STL::pair<const AsciiString,TreeHintPayload003012F0> unknown154;
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
