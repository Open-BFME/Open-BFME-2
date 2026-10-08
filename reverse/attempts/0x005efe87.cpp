// ?SetIconSlotCount@Impl@RegionDetailsArmiesMovieClip@StrategicHUD@@QAEXH@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// WB016176D0 SetIconSlotCount; native005EFE87..005EFF5E RET4.
// Unlanded: ctor005EF669 absent; vector one-argument resize is misnamed Q3SortElem4.
#include "ascii_string.h"
struct TargetRef00217D4C { void *vptr; int refs; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
namespace StrategicHUD { class RegionDetailsArmiesMovieClip { public: class Impl; }; }
class Rva005EF669 {
public: Rva005EF669(StrategicHUD::RegionDetailsArmiesMovieClip::Impl *,int);
private: int head00; TargetRef00217D4C ref04; char tail0c[0x34];
public: void retain() { ++ref04.refs; } void release() { ReleaseTreeHintRef00217D4C(&ref04); }
};
struct Rva005EFD53Element {
private: Rva005EF669 *ptr;
public:
 Rva005EFD53Element(Rva005EF669 *p=0):ptr(p) { if(ptr)ptr->retain(); }
 ~Rva005EFD53Element() { if(ptr)ptr->release(); }
};
#include <vector>
extern void *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *,void *,const char *,const char *,int *);
class StrategicHUD::RegionDetailsArmiesMovieClip::Impl {
 unsigned level; AsciiString name; char unknown08[0x1c];
 _STL::vector<Rva005EFD53Element> slots;
public: void SetIconSlotCount(int count);
};
void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::SetIconSlotCount(int count) {
 _STL::vector<Rva005EFD53Element> *v=&slots;
 if((unsigned)count==v->size()) return;
 Rva0052519DFire(g_bfmeAptWindowManager,(void*)level,name.str(),"SetIconSlotCount",&count);
 if(v->size()<(unsigned)count) {
  while(v->size()<(unsigned)count) {
   Rva005EFD53Element slot(new Rva005EF669(this,v->size()));
   v->push_back(slot);
  }
 } else v->resize(count);
}
