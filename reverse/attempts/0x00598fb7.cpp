// ?UnRegister@AIUnitUpgrader@@QAEXPAVObject@@@Z
// partial score=0.93 date=2026-10-08
// cl: /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
#include <vector>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva00506FE9Hit { public: void rva0055ADBA(void *); };
struct UnitUpgradeRecordView {
 virtual void *destroy(int);
 float delay; ObjectID object;
};
class AIUnitUpgrader {
 char pad[8];
 _STL::vector<void *> waiting;
 _STL::vector<void *> upgrading;
 _STL::vector<void *> completed;
 void *owner;
public:
 void UnRegister(Object *object);
};
void AIUnitUpgrader::UnRegister(Object *object)
{
 _STL::vector<void *>::iterator i=upgrading.begin();
 while (i!=upgrading.end()) {
   UnitUpgradeRecordView *item=(UnitUpgradeRecordView *)*i;
   if (TheGameLogic->findObjectByID(item->object)==object) {
     operator delete(item->destroy(0));
     i=upgrading.erase(i);
   } else ++i;
 }
 _STL::vector<void *>::iterator j=completed.begin();
 while (j!=completed.end()) {
   UnitUpgradeRecordView *item=(UnitUpgradeRecordView *)*j;
   if (TheGameLogic->findObjectByID(item->object)==object) {
     ((Rva00506FE9Hit *)item)->rva0055ADBA(owner);
     operator delete(item->destroy(0));
     j=completed.erase(j);
   } else ++j;
 }
}


