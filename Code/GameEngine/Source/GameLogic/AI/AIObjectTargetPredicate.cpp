// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// ?rva002FE193@AI@@SA_NPAVObject@@0@Z @0x002FE193 478B
// Native2FE193..2FE371478B RET; WB D75230 full757B corresponding unnamed static predicate.
// Donor: BF1 575ba2b Rva0014CA60WeaponTargetPredicate.cpp/712B; its weapon/range/layer/static SiegeDeploy key purpose is the guide.
// BFME2 independently supplies direct source object/six weapon slots, idle3CC, status68, flags115/113 and angular-range helper28F326.
enum NameKeyType {NAMEKEY_INVALID=0};
enum ObjectStatusTypes {OBJECT_STATUS_NONE=0};
enum WeaponSlotType {WEAPON_FIRST=0};
class Object;class Module;
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator*TheNameKeyGenerator;
class Rva002C9400ByteField {public:unsigned char get()const;};
class Weapon {public:bool isWithinAttackRange(const Object*,const Object*,float,int)const;char pad[4];const Rva002C9400ByteField*data;};
class WeaponSet {public:Weapon*getWeaponInWeaponSlot(WeaponSlotType)const;char pad[8];Weapon*slots[6];};
struct AIUpdateInterface {char pad[0x3CC];bool playerIdle;};
struct ThingTemplate {char pad[0x113];unsigned char flags113;char pad114;unsigned char flags115;};
class Rva004C5772CmpBoolField {public:bool get()const;};
class Rva0028F326Owner {public:unsigned char rva0028F326(unsigned,float);};
class Object {public:
 bool testStatus(ObjectStatusTypes)const;int rva0028B511()const;float getVisionRange()const;
 char pad00[4];const ThingTemplate*data;char pad08[0x250-8];void*contain;char pad254[4];AIUpdateInterface*ai;char pad25C[0x330-0x25C];WeaponSet weapons;
protected:
 friend class AI;Module*findModule(NameKeyType)const;
};
class AI {public:static bool rva002FE193(Object*,Object*);};
bool AI::rva002FE193(Object*source,Object*target)
{
 if(!source||!target)return false;
 AIUpdateInterface*ai=source->ai;
 if(!ai)return false;
 bool onGround=false;
 if(source->testStatus((ObjectStatusTypes)68)||ai->playerIdle)onGround=true;
 if(source->data->flags115&0x20){
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
    if(!(target->data->flags113&0x20))continue;
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
