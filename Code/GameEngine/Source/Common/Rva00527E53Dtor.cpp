// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Target Ghidra [527E53,527EAB),88B RET0. Rowed owning-pointer reset527F88
// and deleting wrapper527F6C independently establish the address-scoped dtor.
// Native cleanup consumes AsciiString at+4 and full47B Rva0052413E at+C.
// Kind+8 values1/2 trigger the full38B singleton getter102215; nonnull result
// calls full64B deferred promotion102284. Application class identity unknown.
// Structural guide is the verified Rva005FFBCB cleanup family; offsets and
// conditional calls above come independently from this target.
#include "ascii_string.h"
class Rva0052413E {public:~Rva0052413E();private:char fields[12];};
class Rva001021F7;
Rva001021F7* Rva00102215Get();
class Rva0010225F {public:void rva00102284();};
class Rva00527E53 {
public:~Rva00527E53();
private: int unknown00; AsciiString text04; int kind08; Rva0052413E owned0C;
};
Rva00527E53::~Rva00527E53() {
 if(kind08==1 || kind08==2) {
  Rva001021F7*p=Rva00102215Get();
  if(p) ((Rva0010225F*)p)->rva00102284();
 }
}
