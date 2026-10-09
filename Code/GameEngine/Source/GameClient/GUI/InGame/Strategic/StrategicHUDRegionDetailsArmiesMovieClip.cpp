// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
#include "../../../../Common/RegionArmyIconSlotView.h"
#include "../../../../Common/RegionDetailsArmiesClipImplView.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *,void *,const char *,const char *,int *);
// WB016176D0 and native005EFE87..005EFF5E RET4. Each new slot is the
// recovered64-byte Rva005EEF2F. The shrink call uses the independently
// verified by-value resize view of this same three-pointer handle array.
void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::SetIconSlotCount(int count) {
 _STL::vector<Rva005EFD53Element> *v=&slots;
 if((unsigned)count==v->size()) return;
 Rva0052519DFire(g_bfmeAptWindowManager,(void*)m_level,m_name.str(),"SetIconSlotCount",&count);
 if(v->size()<(unsigned)count) {
  while(v->size()<(unsigned)count) {
   Rva005EFD53Element slot(reinterpret_cast<Rva005EFD53Target *>(new Rva005EEF2F(this,v->size())));
   v->push_back(slot);
  }
 } else reinterpret_cast<_STL::vector<Rva005EFDE9Element,_STL::allocator<Rva005EFDE9Element> > *>(v)->resize(count);
}

class Rva00222A8BTarget;
extern const char *const g_00C78D64[];
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const int &,const char *const &);
// Complete75B native5EF4EF..5EF53A. WB1616AD0 names IconSlot::DoSetState.
// Keep the shared address-derived owner until its whole virtual interface is named.
void Rva005EEF2F::rva005EF4EF(int state) {
 if(state==a)return;
 Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,(void *)owner->level,owner->name.str(),"SetIconSlotState",index,g_00C78D64[state]);
 a=state;
}