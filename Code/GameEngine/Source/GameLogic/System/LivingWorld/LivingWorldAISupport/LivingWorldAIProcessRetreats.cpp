// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 0x004FB600..0x004FB7B2 (434B); WB0x131A0F0 names the role
// LivingWorldAI::ProcessRetreats. The target owner's original class name remains
// open. Existing providers establish the filtered pointer-vector ABI, lookup
// result, region membership test and retreat dispatch. Native slot entries at
// +0x1A8 have24B stride with the lookup key at+8; candidate regions use+0x13C.
// Native empty-choice path dispatches the root's+0x2C fallback then returns.
// Four-byte pointer storage uses existing int-vector constructor and canonical
// const-ModuleData pointer push ABI views; neither asserts original element names.
// Scoped throwing free follows the verified LivingWorldRegionManager allocator.
// Reload begin after each iteration and form manager locals before arguments:
// both are needed for native register allocation/scheduling, with all434B exact.
namespace _STL {void __cdecl free(void *block) throw(...);}
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseRetreatStorage(void *storage)
{
	_STL::free(storage);
}
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
class ModuleData;
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int >::deallocate(int* p,size_t n) const { _STLP_ASSERT((p==0)==(n==0)) if(p!=0) releaseRetreatStorage((void*)p); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<int*,int,allocator<int> >::deallocate(int* p,size_t n) { __stl_alloc_rebind(static_cast<allocator<int>&>(*this),(int*)0).deallocate(p,n); }
template<> __declspec(dllimport) __forceinline void allocator<const ModuleData* >::deallocate(const ModuleData** p,size_t n) const { _STLP_ASSERT((p==0)==(n==0)) if(p!=0) releaseRetreatStorage((void*)p); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<const ModuleData**,const ModuleData*,allocator<const ModuleData*> >::deallocate(const ModuleData** p,size_t n) { __stl_alloc_rebind(static_cast<allocator<const ModuleData*>&>(*this),(const ModuleData**)0).deallocate(p,n); }
template<> __declspec(dllimport) __forceinline void vector<const ModuleData*>::_M_clear() { _Destroy(_M_start,_M_finish); _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start); }
}

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002B85ECFilter {char m_pad[0x14];int key;};
#include "../../../../../Include/GameLogic/Rva002BA8F1Logic.h"
struct RetreatEntry {char m_pad[8];int id;char m_rest[12];};
class Rva00318C32Ret {public:char m_pad[0x1a8];_STL::vector<RetreatEntry> entries;};
#include "../../../../../Include/GameLogic/Rva00318C79Owner.h"
class Rva0020E89C {public:char m_pad[0x13c];int m_13c;};
#include "../../../../../Include/GameLogic/Rva0020EAF6View.h"
#include "../../../../../Include/Common/Rva002104B6.h"
#include "../../../../../Include/GameLogic/Rva002E071E.h"
#include "../../../../../Include/Common/Rva002B2702.h"
class LivingWorldLogicView {public:char m_pad[0xb0];Rva0020EAF6View *m_manager;};
int GetGameLogicRandomValue(int,int,char*,int);
class Rva004FB600 {public:void rva004FB600();Rva002B85ECFilter *m_root;};
void Rva004FB600::rva004FB600()
{
 if(!m_root) return;
 _STL::vector<int> armies;
 ((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B85EC(m_root,(_STL::vector<const ModuleData*>*)&armies);
 for(unsigned i=0;i<armies.size();++i) {
  Rva00318C32Ret *slot=((Rva00318C79Owner*)armies[i])->rva00318C32();
  _STL::vector<int> choices;
  RetreatEntry *begin=slot->entries.begin();
  for(unsigned j=0;j<slot->entries.size();++j) {
   Rva0020EAF6View *manager=((LivingWorldLogicView*)TheLivingWorldLogic)->m_manager;
   Rva0020E89C *region=manager->rva0020EAF6(begin[j].id);
   if((unsigned char)((Rva002E071E*)m_root)->rva002E0BC0(region->m_13c)) {
    ((_STL::vector<const ModuleData*>*)&choices)->push_back(reinterpret_cast<const ModuleData* const&>(region));
   }
   begin=slot->entries.begin();
  }
  if(choices.size()) {
   unsigned pick=GetGameLogicRandomValue(0,choices.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAI.cpp",249);
   ((Rva002B2702*)TheLivingWorldLogic)->rva002B2702((void*)armies[i],(void*)choices[pick],choices.size()!=1);
  } else {
   Rva002104B6 *manager=(Rva002104B6*)((LivingWorldLogicView*)TheLivingWorldLogic)->m_manager;
   void *fallback=manager->rva002104B6((char*)m_root+0x2c);
   ((Rva002B2702*)TheLivingWorldLogic)->rva002B2702((void*)armies[i],fallback,0);
   return;
  }
 }
}
