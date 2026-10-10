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
#define free _STL::free
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#undef free
class ModuleData;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002B85ECFilter {char m_pad[0x14];int key;};
class Rva002BA8F1Logic {public: void rva002B85EC(Rva002B85ECFilter*,_STL::vector<const ModuleData*>*);};
struct RetreatEntry {char m_pad[8];int id;char m_rest[12];};
class Rva00318C32Ret {public:char m_pad[0x1a8];_STL::vector<RetreatEntry> entries;};
class Rva00318C79Owner {public:Rva00318C32Ret *rva00318C32();};
class Rva0020E89C {public:char m_pad[0x13c];int m_13c;};
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
class Rva002104B6 {public:void *rva002104B6(void*);};
class Rva002E071E {public:int rva002E0BC0(int);};
class Rva002B2702 {public:void rva002B2702(void*,void*,int);};
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
