// cl: /O1 /arch:SSE2 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
class NestedInlineBase {public: virtual ~NestedInlineBase();};
struct S3Money : NestedInlineBase { int words[2];
 // ?S3Money::S3Money present-unmatched
 __forceinline S3Money(const S3Money &r) {words[0]=r.words[0];words[1]=r.words[1];}
 };
struct S3Coord { float x,y,z; };
struct Rva004216D3Coord : Coord3D {
 Rva004216D3Coord(const Rva004216D3Coord &r) {x=r.x;y=r.y;z=r.z;}
 ~Rva004216D3Coord() {}
};
struct Rva001FDCE1Record {Rva001FDCE1Record();Rva001FDCE1Record(const Rva001FDCE1Record&);~Rva001FDCE1Record();Rva001FDCE1Record&operator=(const Rva001FDCE1Record&);char bytes[1];bool operator<(const Rva001FDCE1Record&)const;bool operator==(const Rva001FDCE1Record&)const;};
struct Rva001FDAB0Less {bool operator()(int,int)const;};
enum ScienceType { S3ScienceForce=0x7fffffff };
struct Rva0021C21BElement { char bytes[4]; };
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element &)const;bool operator==(const Rva0026F4F4Element &)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}
class Rva0036CA00Str {public:__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);~Rva0036CA00Str();void *data;};
struct TreeHintPayload003012F0 {unsigned a,b,c;TreeHintPayload003012F0(const TreeHintPayload003012F0 &r):a(r.a),b(r.b),c(r.c){}};
struct Rva00360D26Member {~Rva00360D26Member();unsigned word;};
struct BfmeObject476 : Rva001E3624 {
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
 _STL::map<int,void*> unknownf4;
 _STL::hash_map<int,Rva001FDCE1Record> unknown100;
 _STL::map<int,void*,Rva001FDAB0Less> unknown114;
 _STL::vector<ScienceType> unknown120,unknown12c;
 AsciiString unknown138,unknown13c,unknown140,unknown144;
 int unknown148;
 AsciiString unknown14c;
 bool unknown150,unknown151;
 _STL::pair<const AsciiString,TreeHintPayload003012F0> unknown154;
 AsciiString unknown164,unknown168,unknown16c,unknown170,unknown174,unknown178,unknown17c;
 _STL::vector<AsciiString> unknown180,unknown18c,unknown198;
 Rva0036CA00Str unknown1a4,unknown1a8,unknown1ac;
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
