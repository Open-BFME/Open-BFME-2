// ?rva004EA420@Rva004EA3B8@@QAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /ICode/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder /ICode/Libraries/Include/Lib
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include "AIEconomyBuilderFarmLibrary.h"
#include "Coord3D.h"
void *__cdecl operator new(unsigned);
class ModuleData;
namespace _STL { template<class T> class allocator {}; template<class T,class A=allocator<T> > class vector { public: void reserve(unsigned); void push_back(const T &); }; }
extern GameLogic *TheGameLogic;
extern unsigned g_Va00E04490;
int Rva004EA2C5Get();
struct EconomyObjectTemplate { char unknown00[0x64]; StringBase<char> name; };
struct EconomyObjectView {
 EconomyObjectTemplate *getTemplate() const { return type; } char unknown00[4]; EconomyObjectTemplate *type;
 char unknown08[0x38-8]; Coord3D position; float orientation;
 char unknown48[0x8C-0x48]; Object *next;
};
class Rva00573A00 { public: void rva00573A00(const Coord3D *); };
class Rva00596F18 {
public: Rva00596F18(void *); virtual ~Rva00596F18();
 char unknown04[0x3C-4]; float orientation; char unknown40[0x74-0x40];
};
struct EconomyFarmView { char unknown00[0x3C]; float orientation; };
class Rva004EA3B8 { public: void rva004EA420(); };
void Rva004EA3B8::rva004EA420() {
 if(AIEconomyBuilder::m_farmList.first==AIEconomyBuilder::m_farmList.finish) {
  int count=Rva004EA2C5Get();
  if(count>0) {
   _STL::vector<const ModuleData *> &farms=reinterpret_cast<_STL::vector<const ModuleData *> &>(AIEconomyBuilder::m_farmList);
   farms.reserve(count);
   int index=0;
   for(Object *obj=TheGameLogic->getFirstObject();obj;obj=reinterpret_cast<EconomyObjectView *>(obj)->next) {
    EconomyObjectView *view=reinterpret_cast<EconomyObjectView *>(obj);
    if(!view->getTemplate()->name.compare(reinterpret_cast<const StringBase<char> &>(g_Va00E04490))) {
     Rva00596F18 *selected=new Rva00596F18(reinterpret_cast<void *>(index++));
     EconomyFarmView *farm=reinterpret_cast<EconomyFarmView *>(selected);
     reinterpret_cast<Rva00573A00 *>(farm)->rva00573A00(&view->position);
     farm->orientation=view->orientation;
     farms.push_back(reinterpret_cast<const ModuleData *const &>(selected));
    }
   }
  }
 }
}
