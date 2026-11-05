// Native 0x0028DCC4..0x0028DDE0, 284 bytes, RET0. WB CDAD80 agrees
// with the template guards and registration sequence; no original method name.
// Shroud, partition and collision handles are Object subobjects at 0x64/0x6C/0x70.
// Native data reads prove template kind words 0x108..0x114, Object flag 0x454,
// partition data 0x4C4 and AI data 0x18 / enable flag 0xB9. The boolean read
// reads the timing-log enable byte g_00DFE7A8 (owned by Rva003B9EC4.cpp);
// its role here remains unknown. Existing provider ABI spellings are retained.
// Reference lead: ZH Object.cpp registration and kind-of exclusion semantics;
// the split ShroudManager/CollisionManager and Lua registrations are BFME2.
// cl: /O1 /G7 /arch:SSE /MD
class Object;
class Rva00739750 {public: void rva00739750(void*);};
#include "../../../Include/GameLogic/PartitionData.h"
#include "../../Common/PartitionRangeQueryCallView.h"
struct Rva009A29A0Window;
class Rva00758230 {public:void rva00758230(Rva009A29A0Window*);};
struct Rva00287C21Other;
#include "../../../Include/GameLogic/FireLogicSystem.h"
class LuaDrawableState {public:void rva00333E5B(Object*);};
#include "../../../Include/GameLogic/Rva002A8F24.h"
class ShroudManager;
// TheShroudManager is only an alias of the owned global TheShroudManager (ledger names column); this unit reads the owner through its own view type.
extern class PartitionManager *TheShroudManager;
#define TheShroudManager (*(ShroudManager * *)&TheShroudManager)
extern PartitionManager *ThePartitionManager;
class CollisionManager;
extern CollisionManager *TheCollisionManager;
extern class Rva002872BA *TheTriggerManager;
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
// Sole data-ledger owner of the registry pointer at VA 0x00DFEEF8.
extern Rva002A8F24 *TheSkirmishAIManager;
// The timing-log enable byte (VA 0x00DFE7A8), defined by Rva003B9EC4.cpp.
extern unsigned char g_00DFE7A8;
#include "../../../Include/GameLogic/TAiData.h"
#include "../../../Include/GameLogic/AI.h"
#include "../../../Include/Common/ThingTemplate.h"
class Object {public:void rva0028DCC4();
 char pad[4];ThingTemplate *type; char pad8[0x64-8];char shroud[8];char partition[4];char collision[4];char pad74[0x454-0x74];bool flag454;char pad455[0x4c4-0x455];PartitionData *partitionData;
};
void Object::rva0028DCC4(){
 if(type->m_kindof[2] & (1u<<25)){
  if(type->m_kindof[3] & (1u<<25)){
   if(TheShroudManager && !partitionData){((Rva00739750*)TheShroudManager)->rva00739750(shroud);flag454=true;}
   if(partitionData)partitionData->makeDirty();
  }
 }else{
  if(!(type->m_kindof[0] & (1u<<25))){
   if(TheShroudManager && !partitionData)((Rva00739750*)TheShroudManager)->rva00739750(shroud);
   if(partitionData)partitionData->makeDirty();
   if(ThePartitionManager)ThePartitionManager->rva00625320(partition);
   (*(FireLogicSystem **)&TheTriggerManager)->RegisterObject((Rva00287C21Other*)this);
  }
  bool eligible = !(type->m_kindof[0] & (1u<<30));
  if(g_00DFE7A8) eligible=false;
  if((type->m_kindof[3] & (1u<<13)) && !TheAI->m_aiData->m_hordesWaitForHordes)eligible=false;
  if(eligible && TheCollisionManager)((Rva00758230*)TheCollisionManager)->rva00758230((Rva009A29A0Window*)collision);
  if(TheLuaScriptEngine)((LuaDrawableState*)TheLuaScriptEngine)->rva00333E5B(this);
  TheSkirmishAIManager->rva002A9365(this);
  flag454=true;
 }
}
