// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005CE804..005CE874,112B: six-argument constructor called by
// unrowed005759A5. Address-derived identity retained from prior attempt;
// WB015C2480 is unnamed and confirms the base call, two vptrs, argument2
// unused, members C/10/14/18 and owned holder1C. No donor name inferred.
// Structural sibling: StrategicInGameUIPlanningPhaseBuildingSelectionCtor.cpp,
// current master with BFME1 revision575ba2b04743f190f069805fbdc59936123c45da.
// Target builds base5E67FE at0 and observer at8 (BED658), then installs
// C75184/C7517C. A nontrivial owned member1C accounts for EH state2 before
// rowed5E683E forward(region->1C,region); native unwind7A1709 and the
// independently rowed destructor5CE874 both clear member1C through5CE7EA.
// The +8 observer's own vftable BED658 is not LivingWorldBuildingObserver's
// C77F44 (the four-slot building listener the LivingWorldLogic ctor/dtor and
// the sibling ctor 5CE5B3 install), so it keeps a TU-scoped address name.
class Rva005E67FE { public: Rva005E67FE(void *); virtual ~Rva005E67FE(); void *held; };
#include "../../../../Include/GameClient/Rva005E683EMid.h"
class Rva005CE804Observer { public: virtual ~Rva005CE804Observer() {} virtual void onBuildingChanged() = 0; };
// Use the complete owning destructor provided by ThrowingNewHelpers.cpp.
// Its 26-byte retail body at5CE7EA matches this member's target unwind call.
class Rva005E8F50;
#include "../../../../Include/Common/Rva005CEA51.h"
typedef char Rva005CEA51SizeCheck[(sizeof(Rva005CEA51)==4)?1:-1];
struct FwdArg { char pad[0x1c]; int id; };
// The inline dtor compiles to the 76 bytes of the rowed ??1Rva005CE874 at
// 0x005CE874 (both vptrs, member +1C through 0x005CE7EA, observer vptr
// BED658, base dtor 0x005E6810), which its deleting dtor 0x005CE8C0 calls.
class Rva005CE804 : public Rva005E67FE, public Rva005CE804Observer {
 public: Rva005CE804(void*,int,int,int,int,FwdArg*); virtual ~Rva005CE804() {} virtual void onBuildingChanged() = 0;
 private: int a; int b; int c; FwdArg *region; Rva005CEA51 owned;
};
Rva005CE804::Rva005CE804(void *owner,int context,int unused,int ui,int extra,FwdArg *fwdArg):Rva005E67FE(owner),a(context),b(ui),c(extra),region(fwdArg) {
 ((Rva005E683EMid*)this)->fwd(region->id,(int)region);
}
