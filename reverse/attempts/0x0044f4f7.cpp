// ?isWithinAbilityAbortRange@SpecialAbilityUpdate@@IBE_NXZ
// partial score=0.91222459 date=2026-10-09
// cl: /O1 /arch:SSE /MD /GX /DNDEBUG /I. /Ireference/shims/bfme2_ascii
// BFME1 semantic donor: revision 9cbfb551; clean SpecialAbilityUpdate_update.cpp
// supplies the phase machine. Target 0x00451FA2..0x004522F0 proves this+0x10
// update receiver; native destructor/interface slots and neighboring bodies prove
// SpecialAbilityUpdate identity. Every member offset and extra target check below
// comes from game.dat; the WB update pairing is unrelated and was not used.
// Readiness definitions retain their existing address-derived identities and are
// rehomed here so cl sees their actual register preservation, as retail requires.
// Native calls from update prove the three address-named persistence/sleep helpers.
// WB 0x010E39D0 and 0x010E8210 corroborate their control flow; original names remain
// inferred from the donor, so the target rows retain address-derived spellings.
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
__forceinline float abilityMax(float a,float b){return a>b?a:b;}
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
enum CommandSourceType { CMD_FROM_AI=2 };
class AICommandInterface {public:void aiIdle(CommandSourceType);};
template<int N>class RunSlots:public RunSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class RunSlots<0>{};
class AIUpdateInterface:public RunSlots<110>{public:virtual bool isIdle();
virtual void aiGap111();
virtual void aiGap112();
virtual void aiGap113();
virtual void aiGap114();
virtual void aiGap115();
virtual void aiGap116();
virtual void aiGap117();
virtual void aiGap118();
virtual void aiGap119();
virtual void aiGap120();
virtual void aiGap121();
virtual void aiGap122();
virtual void aiGap123();
virtual void aiGap124();
virtual void aiGap125();
virtual void aiGap126();
virtual void aiGap127();
virtual void aiGap128();
virtual void aiGap129();
virtual void aiGap130();
virtual void aiGap131();
virtual void aiGap132();
virtual void aiGap133();
virtual void aiGap134();
virtual void aiGap135();
virtual void aiGap136();
virtual void aiGap137();
virtual void aiGap138();
virtual void aiGap139();
virtual void aiGap140();
virtual void aiGap141();
virtual void aiGap142();
virtual int getLastCommandSource();};
class GeometryInfo {public:bool bfmeIntersects(const Coord3D&,float,const GeometryInfo&,const Coord3D&,float) const;};
class Player;enum ModelConditionFlagType{MODELCONDITION_INVALID=-1};
class Object {public:Player *getControllingPlayer() const;void setSpecialModelConditionState(ModelConditionFlagType,unsigned);
 float rva00263763(const void*) const;float rva002C97E8(const Coord3D*,const Coord3D*) const;
 void removeAttributeModifierFromPool(const AsciiString &);
 char m_pad00[4]; unsigned char *m_data;
 char m_pad08[0x38-8];Coord3D m_position;
 float m_angle;char m_pad48[0x74-0x48];ObjectID m_id;char m_pad78[8];ObjectID m_specialOwner;char m_pad84[0xA8-0x84];GeometryInfo m_geometry;char m_padA9[0x110-0xA9];unsigned int m_modelWord1;
 char m_pad114[0x258-0x114];AIUpdateInterface *m_ai;
 char m_pad25C[0x304-0x25C];void *m_team;
 char m_pad308[0x438-0x308];unsigned int m_deadFlags;
 bool isEffectivelyDead() const{return (m_deadFlags&1)!=0;}
};
extern GameLogic *TheGameLogic;
class Overridable {public:const Overridable*friend_getFinalOverride() const;char m_pad00[0x1C];int m_type;};
struct SpecialAbilityUpdateModuleData {
 char pad00[0x38];Overridable *m_specialPower;
 char pad3C[0x48-0x3C];AsciiString m_modifier;
 float m_startRange,m_abortRange;char pad54[0x78-0x54];unsigned m_persistenceFrames;char pad7C[0xA0-0x7C];int m_minPause,m_maxPause;char padA8[0xAE-0xA8];bool m_alwaysValidate;char padAF[0xB4-0xAF];bool m_removeModifierOnAbort;bool m_continueOnAbort;
 char padB6[0xC6-0xB6];bool m_ignoreFacing;
};
class Rva0044E7A8 {public:bool rva0044E7A8(int);};
class Sub0044E5E7
{
public:
	char m_pad00[0x84];
	int m_84;
	int m_88;
	char m_pad8C[0xA8 - 0x8C];
	unsigned char m_a8;
};

class Rva0044E5E7
{
public:
	bool rva0044E5E7();
	bool rva0044E60D();
private:
	char m_pad00[4];
	Sub0044E5E7 *m_ptr04;
	char m_pad08[0x30 - 0x08];
	int m_30;
	char m_pad34[0x7D - 0x34];
	unsigned char m_7D;
};

bool Rva0044E5E7::rva0044E5E7()
{
	Sub0044E5E7 *sub = m_ptr04;
	if (m_30 != 4)
		goto fail;
	if (sub->m_a8 != 0)
	{
		if (m_7D != 0)
			goto fail;
	}
	if (sub->m_84 != 0)
		return true;
fail:
	return false;
}

// ?rva0044E60D@Rva0044E5E7@@QAE_NXZ @0x0044E60D 38B
// Sibling of 0x0044E5E7 in the same TU: +0x30==3 (vs 4) and sub +0x88!=0
// (vs +0x84); same +0x7D gate and +0xA8 check. Evidence: unlock lane;
// caller at 0x0045227F in 0x00451FA2; abuts prev 0x0044E5E7.
bool Rva0044E5E7::rva0044E60D()
{
	Sub0044E5E7 *sub = m_ptr04;
	if (m_30 != 3)
		goto fail;
	if (sub->m_a8 != 0)
	{
		if (m_7D != 0)
			goto fail;
	}
	if (sub->m_88 != 0)
		return true;
fail:
	return false;
}

class Rva0044E655 {public:bool rva0044E655();bool rva0044E689();
 char pad00[8];Object *m_object;char pad0C[0x7E-0xC];unsigned char m_7E,m_7F;
};
bool Rva0044E655::rva0044E689(){if(m_object->m_ai==0)return false;return m_7E==0||m_7F==0;}
class Rva00451EAC {public:void rva00451EAC();};
class SpecialAbilityUpdate;
class AbilityPrimary {public:virtual void v00();const SpecialAbilityUpdateModuleData *m_data;Object *m_object;};
class AbilityOther {public:virtual void v00();};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class AbilityInterfacePad {public:char pad04[0xC];};
class SpecialAbilityUpdate:public AbilityPrimary,public AbilityOther,public UpdateModuleInterface,public AbilityInterfacePad {
public:
virtual void saSlot1();
virtual void saSlot2();
virtual void saSlot3();
virtual void saSlot4();
virtual void saSlot5();
virtual void saSlot6();
virtual void saSlot7();
virtual void saSlot8();
virtual void saSlot9();
virtual void saSlot10();
virtual void saSlot11();
virtual void saSlot12();
virtual void onExit(bool,bool);
 virtual bool approachTarget();
 virtual void startPreparation();
 virtual bool continuePreparation();
 virtual void triggerAbilityEffect();
 virtual void saSlot18();
 virtual void finishAbility();
 virtual bool handlePackingProcessing();
 virtual void startPacking(bool);
 virtual void startUnpacking();
 virtual UpdateSleepTime update();
 protected: void validateSpecialObjects();void endPreparation(); public: void rva0044EE80();
 protected: bool isWithinAbilityAbortRange() const;bool isWithinStartAbilityRange(); public:
 void rva00451EAC(); bool rva0044F679();void rva0044F6D0();
 UpdateSleepTime rva0044F881();
 char pad20[4];int m_useCount;char pad28[4];unsigned m_expiryFrame;int m_packingState;
 char pad34[0x3C-0x34];unsigned m_prepFrames;int m_targetID;Coord3D m_targetPos;
 char pad50[0x60-0x50];int m_persistenceCount;char pad64[0x74-0x64];bool m_active;
 char pad75[0x80-0x75];bool m_withinStartAbilityRange;char pad81[2];bool m_approached;
 unsigned m_effectFrame;
};
UpdateSleepTime SpecialAbilityUpdate::update()
{
 const SpecialAbilityUpdateModuleData *d=m_data;
 validateSpecialObjects();
 if(m_object->isEffectivelyDead()){onExit(true,true);return rva0044F881();}
 if(m_expiryFrame && m_expiryFrame<TheGameLogic->getFrame())saSlot18();
 if(m_effectFrame && m_effectFrame<TheGameLogic->getFrame()){rva0044EE80();m_effectFrame=0;}
 if(!((Rva0044E7A8*)this)->rva0044E7A8(0)){
  onExit(false,true);
  if(d->m_removeModifierOnAbort&&!d->m_modifier.isEmpty())m_object->removeAttributeModifierFromPool(d->m_modifier);
  rva0044F881();return UPDATE_SLEEP_FOREVER;
 }
 if(m_active){
  AIUpdateInterface *ai=m_object->m_ai;
  if(!ai){onExit(false,true);return rva0044F881();}
  if(m_targetID){Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);if(target)m_targetPos=target->m_position;}
  if(ai->getLastCommandSource()!=2){onExit(false,true);return rva0044F881();}
  bool shouldAbort=false;
  if(d->m_specialPower->friend_getFinalOverride()->m_type==0x2A){
   Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
   if(target&&target->isEffectivelyDead()&&ai->isIdle())shouldAbort=true;
   if(ai->isIdle()&&m_approached)shouldAbort=true;
  }
  if(handlePackingProcessing()&&!shouldAbort)return rva0044F881();
  if(m_targetID){Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
   if(target){int type=d->m_specialPower->friend_getFinalOverride()->m_type;
    if(type==0x1D||type==0x1A){
     if(target->m_team==m_object->m_team)shouldAbort=true;
     if(target->isEffectivelyDead() && (!(target->m_data[0x10E]&2)|| !(bool)((target->m_modelWord1>>28)&1)))shouldAbort=true;
    } else if(target->isEffectivelyDead())shouldAbort=true;
   }
  }
  if(shouldAbort&&!d->m_continueOnAbort){((AICommandInterface*)((char*)ai+0x20))->aiIdle(CMD_FROM_AI);onExit(false,true);return rva0044F881();}
  if(m_prepFrames){
   --m_prepFrames;
   if(!m_prepFrames){triggerAbilityEffect();
    if(rva0044F679())rva0044F6D0();
    else {endPreparation();if(((Rva0044E5E7*)this)->rva0044E5E7())startPacking(true);else finishAbility();}
   }else if(!continuePreparation()){
    endPreparation();if(((Rva0044E5E7*)this)->rva0044E5E7())startPacking(false);else finishAbility();
   }
  } else if(isWithinStartAbilityRange()){
   m_withinStartAbilityRange=true;
   if(!d->m_ignoreFacing){
    if(!((Rva0044E655*)this)->rva0044E655() && ((Rva0044E655*)this)->rva0044E689()){((Rva00451EAC*)this)->rva00451EAC();return rva0044F881();}
    if(((Rva0044E655*)this)->rva0044E655() && ((Rva0044E655*)this)->rva0044E689())return rva0044F881();
   }
   if(((Rva0044E5E7*)this)->rva0044E60D()){startUnpacking();return rva0044F881();}
   if(m_packingState==4){startPreparation();if(!m_prepFrames){triggerAbilityEffect();endPreparation();if(((Rva0044E5E7*)this)->rva0044E5E7())startPacking(true);else finishAbility();}}
  } else if(ai->isIdle())approachTarget();
 }
 return rva0044F881();
}

bool SpecialAbilityUpdate::rva0044F679(){if(!m_persistenceCount)return false;const SpecialAbilityUpdateModuleData *d=m_data;Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);if(d->m_specialPower->friend_getFinalOverride()->m_type==0x27){
 if(!target && m_useCount<=1)return d->m_persistenceFrames>0;
 if(target && ((target->m_data[0x108]&0x40)||(target->m_data[0x108]&0x40)) && m_useCount<=1)return d->m_persistenceFrames>0;
 return false;
 }
 return d->m_persistenceFrames>0;
}
void SpecialAbilityUpdate::rva0044F6D0()
{
 const SpecialAbilityUpdateModuleData *d=m_data;
 Overridable *power=d->m_specialPower;
 Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
 if(m_persistenceCount>0)--m_persistenceCount;
 if(power->friend_getFinalOverride()->m_type!=0x27 || (target && ((target=(Object*)target->m_data,((unsigned char*)target)[0x108]&0x40)||((unsigned char*)target)[0x114]&8)))m_prepFrames=d->m_persistenceFrames;
 else m_prepFrames=0;
}

class Rva0028F59A {public:Rva0028F59A(int,int);unsigned m_bits[19];};
class Rva001E42F2 {public:void rva001E42F2(const int*);};
class Rva001E431E {public:void rva001E431E(const int*);};
// Existing signed frame-rate global; data ledger RVA 0x00A033D0 and
// Rva007ABC6FFrameRateInits.cpp establish the binding and declaration.
extern int g_00E033D0;
UpdateSleepTime SpecialAbilityUpdate::rva0044F881()
{
 if(m_active || m_data->m_alwaysValidate || m_expiryFrame)return UPDATE_SLEEP_NONE;
 const SpecialAbilityUpdateModuleData *d=m_data;
 {
   if(d->m_specialPower->friend_getFinalOverride()->m_type==0x1D){
    Object *self=m_object;
    Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
    if(self && target){
     bool changed=false;
     if(self->getControllingPlayer()==target->getControllingPlayer()){
      ((Rva001E431E*)target)->rva001E431E((const int*)&Rva0028F59A(0,0x77));
      changed=true;
     }else if(target->m_specialOwner==m_object->m_id){
      target->setSpecialModelConditionState((ModelConditionFlagType)0x6F,g_00E033D0);
      changed=true;
     }
     ((Rva001E42F2*)self)->rva001E42F2((const int*)&Rva0028F59A(0,0x70));
     if(changed){
      ((Rva001E42F2*)target)->rva001E42F2((const int*)&Rva0028F59A(0,0x6E));
      target->m_specialOwner=INVALID_OBJECT_ID;
     }
    }
   }
   if(!d->m_minPause && !d->m_maxPause)return UPDATE_SLEEP_FOREVER;
 }
 return UPDATE_SLEEP_NONE;
}

// ?isWithinAbilityAbortRange@SpecialAbilityUpdate@@IBE_NXZ present-unmatched
bool SpecialAbilityUpdate::isWithinAbilityAbortRange() const
{
 const SpecialAbilityUpdateModuleData *d=m_data;
 const Overridable *power=d->m_specialPower;
 const Object *self=m_object;
 float range=abilityMax(0.0f,d->m_startRange-2.5f);
 float distance=0.0f;
 Object *target=0;
 if(m_targetID){target=TheGameLogic->findObjectByID((ObjectID)m_targetID);if(target)distance=self->rva00263763(target);}
 else if(m_targetPos.x || m_targetPos.y || m_targetPos.z){
  distance=self->rva002C97E8(&self->m_position,&m_targetPos);
  if(power->friend_getFinalOverride()->m_type==0x27)distance-=400.0f;
 }else return true;
 float abortSquared=d->m_abortRange*d->m_abortRange;
 if(distance<=abortSquared){
  if(range==0.0f && m_targetID){
   if(!target)return false;
   if(!self->m_geometry.bfmeIntersects(self->m_position,0.0f,target->m_geometry,target->m_position,target->m_angle))return false;
  }
  return true;
 }
 return false;
}
