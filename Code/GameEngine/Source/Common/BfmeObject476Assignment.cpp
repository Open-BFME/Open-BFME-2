// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// PlayerTemplate store parser1FEFEC copies its override through this provider.
// Target804B [1FE78E,1FEAB2), existing476-byte vector callers and the parser
// establish the aggregate and assignment ABI. ZH PlayerTemplate.h supplies
// the member-family guide; original names of added BFME2 fields stay unknown.
// Base assignment ignores override links. Money-like +2C subobject preserves
// its vptr while copying +30/+34. String/container/handle providers are the
// already-verified owners named below; no new pins or aliases are required.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class Overridable { public: virtual ~Overridable(); Overridable &operator=(const Overridable &); char data[12]; };
struct S3Handicap { int words[4]; };
struct S3Money { virtual ~S3Money(); int words[2]; __forceinline S3Money &operator=(const S3Money &r) { words[0]=r.words[0]; words[1]=r.words[1]; return *this;} };
struct S3Coord { float x,y,z; };
struct Rva001FD42B { Rva001FD42B *rva001FD8DF(const Rva001FD42B &); Rva001FD42B &operator=(const Rva001FD42B &rhs) {rva001FD8DF(rhs);return *this;} char data[12]; };
struct Rva000427195 { Rva000427195 &operator=(const Rva000427195 &); char data[20]; };
struct Rva001FD458 { Rva001FD458 *rva001FD952(const Rva001FD458 &); Rva001FD458 &operator=(const Rva001FD458 &rhs){rva001FD952(rhs);return *this;} char data[12]; };
struct Rva0021C21BElement { char bytes[4]; };
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element &)const;bool operator==(const Rva0026F4F4Element &)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}
struct OpaqueRefElement4 { OpaqueRefElement4 &operator=(const OpaqueRefElement4 &); void *data; };
struct Rva001FD404 { Rva001FD404 *rva001FD404(const Rva001FD404 &); Rva001FD404 &operator=(const Rva001FD404 &rhs){rva001FD404(rhs);return *this;} AsciiString text; int words[3]; };
struct BfmeObject476 : Overridable {
 int unknown10;
 UnicodeString unknown14;
 AsciiString unknown18;
 S3Handicap unknown1c;
 S3Money unknown2c;
 S3Coord unknown38;
 AsciiString unknown44;
 AsciiString unknown48[10];
 S3Coord unknown70[10];
 _STL::vector<AsciiString> unknowne8;
 Rva001FD42B unknownf4;
 Rva000427195 unknown100;
 Rva001FD458 unknown114;
 _STL::vector<Rva0021C21BElement> unknown120,unknown12c;
 AsciiString unknown138,unknown13c,unknown140,unknown144;
 int unknown148;
 AsciiString unknown14c;
 bool unknown150,unknown151;
 Rva001FD404 unknown154;
 AsciiString unknown164,unknown168,unknown16c,unknown170,unknown174,unknown178,unknown17c;
 _STL::vector<AsciiString> unknown180,unknown18c,unknown198;
 OpaqueRefElement4 unknown1a4,unknown1a8,unknown1ac;
 AsciiString unknown1b0,unknown1b4,unknown1b8;
 bool unknown1bc;
 AsciiString unknown1c0,unknown1c4;
 int unknown1c8;
 _STL::vector<Rva0026F4F4Element> unknown1cc;
 AsciiString unknown1d8;
};
// Compiler emission witness; no retail body is claimed for this wrapper.
// ?S3Copy476 absent-from-retail
void S3Copy476(BfmeObject476 &dst,const BfmeObject476 &src) { dst=src; }

typedef char BfmeObject476Extent[sizeof(BfmeObject476)==476?1:-1];
