// Native004CDDBA..004CDEED RET4 and WB1278F70 identify the implementation
// as ActivateModuleSpecialPower::SetWakeState; the slot wrappers in
// VslotSmallBodiesAD*.cpp call it through their own views of the class.
// Module data4/owner8, target44, entriesC8 of eight bytes and module interface
// at0C are independent native reads. The class/role is established by the
// existing ActivateModule constructor, wrapper and WB assertion.
// ZH has no ActivateModule counterpart and BFME1 donor575 has no clean body;
// WB supplies the subsystem guide. Slots9/8 return interface pointers and
// their accessed slots take the verified one-word delay / coord-word pair;
// descriptive interface names are structural roles, not recovered ABI names.
// The self-activation error and debug calls remain as they are in retail.
// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/debug.h"
static __forceinline const char*formatText(const Debug::Format&f){return (const char*)&f;}
extern Debug*theDebug;void _bfme_debugRecordCallsite(int);
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
#include "../../../../Include/Common/ThingTemplate.h"
class Object{public:BehaviorModule*rva0028F2C4(int)const;char p0[4];const ThingTemplate*tmpl;char p8[0x38-8];Coord3D position;};
struct WakeEntry{int key,mode;};struct WakeVector{WakeEntry*begin,*end,*capacity;};struct WakeData{char p[0xc8];WakeVector entries;};
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class ActivateModuleSpecialPower:public SpecialAbilityUpdate{public:void SetWakeState(int);virtual void triggerAbilityEffect();};
void ActivateModuleSpecialPower::SetWakeState(int state)
{
 Object*obj=m_object;
 const WakeVector&wakeVector=((const WakeData*)m_moduleData)->entries;
 for(WakeEntry*it=wakeVector.begin;it!=wakeVector.end;++it){
  BehaviorModule*module=obj->rva0028F2C4(it->key);
  if(!module)continue;
  if((void*)this==(void*)module){
   const char*name=obj->tmpl->m_nameString.str();
   _bfme_debugRecordCallsite(1);theDebug->SkipNext();
   Debug&report=theDebug->CrashBegin(0,0,0);
   report<<formatText(Debug::Format("ERROR: ActivateModuleSpecialPower can not be used on it self! Check the INI for Object %s",name));report.CrashDone(1);
  }else{
   UpdateModuleInterface*update=static_cast<BehaviorModuleInterface &>(*module).getUpdate();
   if(update){
    unsigned sleep=0x3fffffff;switch(state){case 0:sleep=1;break;case 1:sleep=update?0x3fffffff:0x3fffffff;break;default:break;}update->rva0044DF8D((UpdateSleepTime)sleep);
   }else if(state==0){
    SpecialPowerModuleInterface*power=static_cast<BehaviorModuleInterface &>(*module).getSpecialPower();
    if(power){Coord3D position;if(it->mode==1)position=obj->position;else position=m_targetPos;power->doSpecialPowerAtLocation(&position,0);}
   }
  }
 }
}

// Existing19B slot17 calls the base and then SetWakeState with state0.
void ActivateModuleSpecialPower::triggerAbilityEffect()
{
 SpecialAbilityUpdate::triggerAbilityEffect();
 SetWakeState(0);
}
