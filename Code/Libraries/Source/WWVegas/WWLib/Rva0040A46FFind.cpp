// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Native40A46F..40A530 is the owning one-string predicate variant of the
// recovered4x-unrolled pointer-range find. Comparison40A424 only null-checks
// its argument and invokes the nonallocating case-insensitive string compare;
// its nothrow contract explains the absence of an EH-state transition before
// the loop. Predicate storage is4B as independently observed by release36410.
// Functor spelling is address-derived; no original application name inferred.
#include "ascii_string.h"
class CreateAHeroData;
class Rva0040A424 {
 AsciiString text;
public: bool rva0040A424(CreateAHeroData*) throw();
 __forceinline bool operator()(CreateAHeroData*p){return rva0040A424(p);}
};
CreateAHeroData** Rva0040A46FFind(CreateAHeroData** first,CreateAHeroData** last,Rva0040A424 pred) {
 int trip=(last-first)>>2;
 for(;trip>0;--trip) {
  if(pred.rva0040A424(*first))return first;
  ++first;
  if(pred.rva0040A424(*first))return first;
  ++first;
  if(pred.rva0040A424(*first))return first;
  ++first;
  if(pred.rva0040A424(*first))return first;
  ++first;
 }
 switch(last-first) {
 case 3: if(pred.rva0040A424(*first))return first; ++first;
 case 2: if(pred.rva0040A424(*first))return first; ++first;
 case 1: if(pred.rva0040A424(*first))return first;
 default: return last;
 }
}
