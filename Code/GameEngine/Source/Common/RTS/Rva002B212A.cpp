// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 2B212A..2B21EF (197B), RET8: search the receiver's 36-byte
// records for name and two ranges; increment/refresh a hit or append a
// level-one record. Each field offset and call is target evidence.
// Existing constructor2AF581 and refresh2AABEE independently establish
// string0/count4/value-range8/tag-range14/value20. The legacy unsigned
// vector declaration is an emitter view of the float range's four-byte
// words, as in the verified constructor; the original record name is open.
// The STL vector algorithm comes from vendored STLport4.5.3 at BFME1
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d. ZH Player.cpp has no matching
// named level-record operation; its Player identity is not asserted here.
// The provider's int comparators return only0/1; a byte cast preserves
// those results and reproduces retail's AL tests without retyping providers.
// The owning wrapper gives the constructed ABI record its already-proved
// teardown2AF1EC. Force-inlining construction removes a forwarding call.
#include "ascii_string.h"
#include <vector>
struct Rva002AAC9ERange {float const *begin,*end;};
struct AsciiRange002ADD75 {AsciiString const *begin,*end;};
int Rva002AAC9EEqual(const Rva002AAC9ERange *,const Rva002AAC9ERange *);
int Rva002ADD75Equal(const AsciiRange002ADD75 *,const AsciiRange002ADD75 *);
class Rva002AABEE {public:
 Rva002AABEE(AsciiString,unsigned,const _STL::vector<unsigned>&,const _STL::vector<AsciiString>&);
 void rva002AABEE();
 char opaque[36];
};
struct Rva002AF6C5Element {~Rva002AF6C5Element();};
struct Rva002B212AOwned {
 Rva002AABEE value;
 __forceinline Rva002B212AOwned(const AsciiString &name,const _STL::vector<unsigned>& values,const _STL::vector<AsciiString>& tags):value(name,1,values,tags) {}
 ~Rva002B212AOwned(){reinterpret_cast<Rva002AF6C5Element*>(&value)->~Rva002AF6C5Element();}
};
struct BfmeVectorRecord002AF478 {char opaque[36];};
namespace _STL {template <> void vector<BfmeVectorRecord002AF478>::push_back(const BfmeVectorRecord002AF478 &);}
struct Rva002B212AArg {char prefix[0x11C];_STL::vector<unsigned> values;char gap[8];_STL::vector<AsciiString> tags;};
class Rva002B212A {public:
 char prefix[0x3B0];_STL::vector<BfmeVectorRecord002AF478> records;
 void rva002B212A(Rva002B212AArg *,const AsciiString &);
};
void Rva002B212A::rva002B212A(Rva002B212AArg *arg,const AsciiString &name) {
 for(BfmeVectorRecord002AF478 *it=records.begin();it!=records.end();++it) {
  if(reinterpret_cast<AsciiString*>(it)->compare(name)==0 &&
     (unsigned char)Rva002AAC9EEqual(reinterpret_cast<Rva002AAC9ERange*>((char*)it+8),reinterpret_cast<Rva002AAC9ERange*>(&arg->values)) &&
     (unsigned char)Rva002ADD75Equal(reinterpret_cast<AsciiRange002ADD75*>((char*)it+0x14),reinterpret_cast<AsciiRange002ADD75*>(&arg->tags))) {
    ++*reinterpret_cast<unsigned*>((char*)it+4);
    reinterpret_cast<Rva002AABEE*>(it)->rva002AABEE();
    return;
  }
 }
 Rva002B212AOwned fresh(name,arg->values,arg->tags);
 records.push_back(*reinterpret_cast<BfmeVectorRecord002AF478*>(&fresh.value));
}
