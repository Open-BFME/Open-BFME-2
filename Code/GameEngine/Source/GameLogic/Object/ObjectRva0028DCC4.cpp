// Native 0x0028DCC4..0x0028DDE0, 284 bytes, RET0. WB CDAD80 agrees
// with the template guards and registration sequence; no original method name.
// Shroud, partition and collision handles are Object subobjects at 0x64/0x6C/0x70.
// Native data reads prove template kind words 0x108..0x114, Object flag 0x454,
// partition data 0x4C4 and AI data 0x18 / enable flag 0xB9. The boolean read
// uses the first byte of the existing address-named global g_Va00DFE7A8;
// its purpose remains unknown. Existing provider ABI spellings are retained.
// Reference lead: ZH Object.cpp registration and kind-of exclusion semantics;
// the split ShroudManager/CollisionManager and Lua registrations are BFME2.
// cl: /O1 /G7 /arch:SSE /MD
class Object;
class Rva00739750 {public: void rva00739750(void*);};
class PartitionData {public:void makeDirty();};
#include "../../Common/PartitionRangeQueryCallView.h"
struct Rva009A29A0Window;
class Rva00758230 {public:void rva00758230(Rva009A29A0Window*);};
struct Rva00287C21Other;
class FireLogicSystem {public:void RegisterObject(Rva00287C21Other*);};
class LuaDrawableState {public:void rva00333E5B(Object*);};
class Rva002A8F24 {public:void rva002A9365(Object*);};
class ShroudManager;
extern ShroudManager *TheShroudManager;
extern PartitionManager *ThePartitionManager;
class CollisionManager;
extern CollisionManager *TheCollisionManager;
extern FireLogicSystem *TheFireLogic;
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
class SkirmishAIManager;
extern SkirmishAIManager *TheSkirmishAIManager;
extern unsigned g_Va00DFE7A8;
class AIData {public:char pad[0xb9];bool enabled;};
class AI {public:char pad[0x18];AIData *data;};
extern AI *TheAI;
class ThingTemplate {public:char pad[0x108];unsigned kind[4];};
class Object {public:void rva0028DCC4();
 char pad[4];ThingTemplate *type; char pad8[0x64-8];char shroud[8];char partition[4];char collision[4];char pad74[0x454-0x74];bool flag454;char pad455[0x4c4-0x455];PartitionData *partitionData;
};
void Object::rva0028DCC4(){
 if(type->kind[2] & (1u<<25)){
  if(type->kind[3] & (1u<<25)){
   if(TheShroudManager && !partitionData){((Rva00739750*)TheShroudManager)->rva00739750(shroud);flag454=true;}
   if(partitionData)partitionData->makeDirty();
  }
 }else{
  if(!(type->kind[0] & (1u<<25))){
   if(TheShroudManager && !partitionData)((Rva00739750*)TheShroudManager)->rva00739750(shroud);
   if(partitionData)partitionData->makeDirty();
   if(ThePartitionManager)ThePartitionManager->rva00625320(partition);
   TheFireLogic->RegisterObject((Rva00287C21Other*)this);
  }
  bool eligible = !(type->kind[0] & (1u<<30));
  if(*(bool*)&g_Va00DFE7A8) eligible=false;
  if((type->kind[3] & (1u<<13)) && !TheAI->data->enabled)eligible=false;
  if(eligible && TheCollisionManager)((Rva00758230*)TheCollisionManager)->rva00758230((Rva009A29A0Window*)collision);
  if(TheLuaScriptEngine)((LuaDrawableState*)TheLuaScriptEngine)->rva00333E5B(this);
  ((Rva002A8F24*)TheSkirmishAIManager)->rva002A9365(this);
  flag454=true;
 }
}
