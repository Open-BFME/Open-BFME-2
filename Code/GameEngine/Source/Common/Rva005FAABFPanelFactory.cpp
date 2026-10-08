// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /EHc- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
// Native005FAABF..005FAB16,87B, RET12 with ECX receiver and hidden
// result at stack8, then two integer inputs atC/10. Creates44B panel via
// actual three-argument constructor005FA89C, using receiver+8 context.
// The output pointer and conditional refcount+4 increment establish a
// one-pointer counted result. Returning that result by value naturally emits
// retail's initial AND[EBP-10],0 (MSVC return-object flag, reused by new).
// Existing canonical BattlePromptArmyPanelView supplies the verified panel
// layout and constructor; original factory/result names remain unknown.
// This replaces the old five-argument fastcall locator with target ABI facts.
// No fabricated pin, naked code or explicit frame-state manipulation.
// stlport
#include "BattlePromptArmyPanelView.h"
void *operator new(unsigned);
struct Rva005FAABFResult {
 Rva005FAF5D *ptr;
 Rva005FAABFResult(Rva005FAF5D *p):ptr(p){if(p)++*(int *)((char *)p+4);}
 ~Rva005FAABFResult();
};
class Rva005FAABF {public:Rva005FAABFResult rva005FAABF(int a,int b);private:char pad[8];Rva005FA89CC context;};
Rva005FAABFResult Rva005FAABF::rva005FAABF(int a,int b) {
 return Rva005FAABFResult(new Rva005FAF5D(a,b,&context));
}
