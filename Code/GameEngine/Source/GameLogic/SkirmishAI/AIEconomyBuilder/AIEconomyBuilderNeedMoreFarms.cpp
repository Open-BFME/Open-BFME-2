// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/GameEngine/Source/Common
// WB1381C20 names needMoreFarms and asserts myAI/army definition at135/141.
// Native4EA046..4EA124 RET4 independently supplies unsigned elapsed frames,
// AI record160/16C, definition40/44/48/50 and player money94. The explicit
// positive delay test preserves native unordered behavior as well as codegen.
// Existing shared builder storage supplies player14/farms18/production1C/20.
#include "GameLogicObjectLookupView.h"
#include "AIEconomyBuilderFarmLibrary.h"
struct EconomyArmyDefinition {
 char unknown00[0x40];
 unsigned minimum, limit, perFarm;
 char unknown4c[4];
 float delay;
};
struct Rva002A8AB1Record {
 char unknown00[0x160];
 EconomyArmyDefinition *army;
 char unknown164[8];
 int need;
};
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
struct EconomyPlayerMoneyView { char unknown00[0x94]; unsigned money; };
bool AIEconomyBuilder::needMoreFarms(int *priority) {
 Rva002A8AB1Record *myAI=g_00DFEEF8->rva002A8AB1(m_14);
 unsigned elapsed=TheGameLogic->getFrame()-value20;
 if(myAI->need>0 || value20==-1 || elapsed>g_Va00DBA4E4*myAI->army->delay) {
  unsigned limit=myAI->army->limit;
  unsigned minimum=myAI->army->minimum;
  unsigned perFarm=myAI->army->perFarm;
  *priority=2000;
  unsigned total=value18+count1c;
  if(total<minimum) return true;
  if(myAI->need>0 && count1c==0) {
   *priority=1;
   bool affordable=static_cast<EconomyPlayerMoneyView *>(m_14)->money+total*perFarm<=limit;
   if(affordable || elapsed>g_Va00DBA4E4*40.0f) return true;
  }
 }
 return false;
}
