// ?rva0052BFE1@Rva0052BFE1@@QAEPAURva005657FEElement@@ABV?$StringBase@D@@PBURva005657FEHolder@@@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Native52BFE1..52C036 85B. Full-width EAX from real5657FE is tested
// and returned without normalization; old bool/int locator is not supported.
// Existing5657FE provider proves StringBase<char> key, holder pointer and
// returned record pointer. Target outer rangeC/10 steps184-byte owner slots.
// New bank84B: all loop/count/call/return logic aligns; remaining receiver
// load ECX+ADD versus target EAX+LEA is one-byte extent difference.
// Volatile begin access preserves the target's per-iteration reload; this
// is an emission view, not a claim about original source qualifiers.
// /G7/SSE leaves same failed shape: stop two unchanged shapes, no Code edit.
// stlport
#include "string_base.h"
struct Rva005657FEElement;
struct Rva005657FEHolder;
class Rva005657FEOwner {public:Rva005657FEElement *rva005657FE(const StringBase<char>&, const Rva005657FEHolder*) const;};
struct Stride184Owner {char data[184];};
struct Stride184Range {Stride184Owner *begin,*end;};
class Rva0052BFE1 {public:Rva005657FEElement *rva0052BFE1(const StringBase<char>&key,const Rva005657FEHolder *holder);private:char pad[12];Stride184Owner *begin,*end;};
Rva005657FEElement *Rva0052BFE1::rva0052BFE1(const StringBase<char>&key,const Rva005657FEHolder *holder) {
 for(unsigned i=0;i<(unsigned)(end-begin);++i) {
  Rva005657FEElement *found=((Rva005657FEOwner *)(((const volatile Stride184Range *)&begin)->begin+i))->rva005657FE(key,holder);
  if(found)return found;
 }
 return 0;
}
