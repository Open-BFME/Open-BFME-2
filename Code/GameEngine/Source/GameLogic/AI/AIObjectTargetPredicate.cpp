// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// ?rva002FE193@AI@@SA_NPAVObject@@0@Z @0x002FE193 478B
// Native2FE193..2FE371478B RET; WB D75230 full757B corresponding unnamed static predicate.
// Donor: BF1 575ba2b Rva0014CA60WeaponTargetPredicate.cpp/712B; its weapon/range/layer/static SiegeDeploy key purpose is the guide.
// BFME2 independently supplies direct source object/six weapon slots, idle3CC, status68, flags115/113 and angular-range helper28F326.
// Retail handler B790A9 names FuncInfo D21430: its sole unwind entry at
// D21428 is {-1,B7909C}. The compiler emits this 13B guard reset beside
// this parent, sharing its private initialization guard at DFF100.
enum NameKeyType {NAMEKEY_INVALID=0};
enum ObjectStatusTypes {OBJECT_STATUS_NONE=0};
enum WeaponSlotType {WEAPON_FIRST=0};
class Object;class Module;
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
#include "../../../Include/Common/Rva002C9400ByteField.h"
class Weapon {public:bool isWithinAttackRange(const Object*,const Object*,float,int)const;char pad[4];const Rva002C9400ByteField*data;};
#include "../../../Include/GameLogic/WeaponSetClass.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/Common/ThingTemplate.h"
#include "../../../Include/GameLogic/Rva004C5772CmpBoolField.h"
#include "../../../Include/GameLogic/Module/Rva0028F326Owner.h"
class Object {public:
 bool testStatus(ObjectStatusTypes)const;int rva0028B511()const;float getVisionRange()const;
 char pad00[4];const ThingTemplate*data;char pad08[0x250-8];void*contain;char pad254[4];AIUpdateInterface*ai;char pad25C[0x330-0x25C];WeaponSet weapons;
protected:
 friend class AI;Module*findModule(NameKeyType)const;
};
#include "../../../Include/GameLogic/AI.h"
bool AI::rva002FE193(Object*source,Object*target)
{
 if(!source||!target)return false;
 AIUpdateInterface*ai=source->ai;
 if(!ai)return false;
 bool onGround=false;
 if(source->testStatus((ObjectStatusTypes)68)||ai->m_field3CC)onGround=true;
 if(source->data->m_kindof[3] & 0x2000U){
  if(!source->contain)return false;
  for(int slot=0;slot<6;++slot){
   Weapon*weapon=source->weapons.getWeaponInWeaponSlot((WeaponSlotType)slot);
   if(!weapon)continue;
   if(weapon->isWithinAttackRange(source,target,0.0f,1))return true;
   if(!weapon->data->get())continue;
   if(onGround)return false;
   int sourceLayer=source->rva0028B511();
   bool sameLayer=target->rva0028B511()==sourceLayer;
   if(!sameLayer){
    if(!(target->data->m_kindof[2] & 0x20000000U))continue;
    static NameKeyType siegeDeploySpecialPowerKey=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
    Module*module=target->findModule(siegeDeploySpecialPowerKey);
    if(!module||!((Rva004C5772CmpBoolField*)module)->get())continue;
   }
   if(((Rva0028F326Owner*)source)->rva0028F326((unsigned)target,source->getVisionRange()))return true;
  }
  return false;
 }
 for(int slot=0;slot<6;++slot){
  Weapon*weapon=source->weapons.getWeaponInWeaponSlot((WeaponSlotType)slot);
  if(!weapon)continue;
  if(weapon->isWithinAttackRange(source,target,0.0f,1))return true;
  if(!weapon->data->get())continue;
  if(onGround)return false;
  int sourceLayer=source->rva0028B511();
  if(target->rva0028B511()!=sourceLayer)continue;
  if(((Rva0028F326Owner*)source)->rva0028F326((unsigned)target,source->getVisionRange()))return true;
 }
 return false;
}
