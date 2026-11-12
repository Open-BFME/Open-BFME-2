// cl: /O1 /arch:SSE /MD /GX /DNDEBUG /I. /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
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
#include "../../../Common/Thing/thing.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
enum CommandSourceType { CMD_FROM_AI=2 };
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
template<int N>class RunSlots:public RunSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class RunSlots<0>{};
enum Relationship{ENEMIES,NEUTRAL,ALLIES};
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
enum NameKeyType{NAMEKEY_INVALID=0};class ClientUpdateModule;
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../../Include/GameClient/DrawableBFME2.h"
class Matrix3D;
struct Rva0087DC00Vec{int x,y,z;};class Rva0087DC00{public:void get(Rva0087DC00Vec*);};
class GeometryInfo {public:bool CollidesWith(const Coord3D&,float,const GeometryInfo&,const Coord3D&,float) const;};
class Player;enum ModelConditionFlagType{MODELCONDITION_INVALID=-1};
class Object {public:Player *getControllingPlayer() const;void setSpecialModelConditionState(ModelConditionFlagType,unsigned);
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const;
 float rva00263763(const void*) const;float rva002C97E8(const Coord3D*,const Coord3D*) const;
 Relationship getRelationship(const Object*) const;int getIndicatorColor() const;
 void removeAttributeModifierFromPool(const AsciiString &);
 char m_pad00[4]; unsigned char *m_data;
 char m_pad08[0x38-8];Coord3D m_position;
 float m_angle;char m_pad48[0x74-0x48];ObjectID m_id;char m_pad78[8];ObjectID m_specialOwner;char m_pad84[0xA8-0x84];GeometryInfo m_geometry;char m_padA9[0x110-0xA9];unsigned int m_modelWord1;
 char m_pad114[0x258-0x114];AIUpdateInterface *m_ai;
 char m_pad25C[0x304-0x25C];void *m_team;
 char m_pad308[0x438-0x308];unsigned char m_deadFlags;unsigned char m_pad439[0x43C-0x439];
 bool isEffectivelyDead() const{return (m_deadFlags&1)!=0;}
};
extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"
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
class Rva00451EAC {public:void killSpecialObjects();void rva00451EAC();};
struct AbilityObjectNode {AbilityObjectNode *next,*previous;ObjectID id;};
class SpecialAbilityUpdate;
class AbilityPrimary {public:virtual void v00();const SpecialAbilityUpdateModuleData *m_data;Object *m_object;};
class AbilityOther {public:virtual void v00();};
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
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
 protected: Object *getObject() const{return m_object;}bool initLaser(Object*,Object*);public:void killSpecialObjects();void rva00451EAC(); bool rva0044F679();void rva0044F6D0();
 UpdateSleepTime rva0044F881();
 char pad20[4];int m_useCount;char pad28[4];unsigned m_expiryFrame;int m_packingState;
 char pad34[0x3C-0x34];unsigned m_prepFrames;int m_targetID;Coord3D m_targetPos;
 char pad50[0x60-0x50];int m_persistenceCount;AbilityObjectNode *m_specialObjects;char pad68[0x70-0x68];float m_captureFlashPhase;bool m_active;
 char pad75[0x80-0x75];bool m_withinStartAbilityRange;char pad81[2];bool m_approached;
 unsigned m_effectFrame;
};
UpdateSleepTime SpecialAbilityUpdate::update()
{
 const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;
 validateSpecialObjects();
 if(m_object->isEffectivelyDead()){onExit(true,true);return rva0044F881();}
 if(m_expiryFrame && m_expiryFrame<TheGameLogic->getFrame())saSlot18();
 if(m_effectFrame && m_effectFrame<TheGameLogic->getFrame()){rva0044EE80();m_effectFrame=0;}
 if(!((Rva0044E7A8*)this)->rva0044E7A8(0)){
  onExit(false,true);
  if(specialAbilityUpdateModuleData->fieldB4&&!specialAbilityUpdateModuleData->field48.isEmpty())m_object->removeAttributeModifierFromPool(specialAbilityUpdateModuleData->field48);
  rva0044F881();return UPDATE_SLEEP_FOREVER;
 }
 if(m_active){
  AIUpdateInterface *ai=m_object->m_ai;
  if(!ai){onExit(false,true);return rva0044F881();}
  if(m_targetID){Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);if(target)m_targetPos=target->m_position;}
  if(ai->vslot143()!=2){onExit(false,true);return rva0044F881();}
  bool shouldAbort=false;
  if(specialAbilityUpdateModuleData->m_specialPowerTemplate->getFO()->m_type==0x2A){
   Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
   if(target&&target->isEffectivelyDead()&&ai->isIdle())shouldAbort=true;
   if(ai->isIdle()&&m_approached)shouldAbort=true;
  }
  if(handlePackingProcessing()&&!shouldAbort)return rva0044F881();
  if(m_targetID){Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
   if(target){int type=specialAbilityUpdateModuleData->m_specialPowerTemplate->getFO()->m_type;
    if(type==0x1D||type==0x1A){
     if(target->m_team==m_object->m_team)shouldAbort=true;
     if(target->isEffectivelyDead() && (!(target->m_data[0x10E]&2)|| !(bool)((target->m_modelWord1>>28)&1)))shouldAbort=true;
    } else if(target->isEffectivelyDead())shouldAbort=true;
   }
  }
  if(shouldAbort&&!specialAbilityUpdateModuleData->fieldB5){((AICommandInterface*)((char*)ai+0x20))->aiIdle(CMD_FROM_AI);onExit(false,true);return rva0044F881();}
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
   if(!specialAbilityUpdateModuleData->fieldC6){
    if(!((Rva0044E655*)this)->rva0044E655() && ((Rva0044E655*)this)->rva0044E689()){((Rva00451EAC*)this)->rva00451EAC();return rva0044F881();}
    if(((Rva0044E655*)this)->rva0044E655() && ((Rva0044E655*)this)->rva0044E689())return rva0044F881();
   }
   if(((Rva0044E5E7*)this)->rva0044E60D()){startUnpacking();return rva0044F881();}
   if(m_packingState==4){startPreparation();if(!m_prepFrames){triggerAbilityEffect();endPreparation();if(((Rva0044E5E7*)this)->rva0044E5E7())startPacking(true);else finishAbility();}}
  } else if(ai->isIdle())approachTarget();
 }
 return rva0044F881();
}

bool SpecialAbilityUpdate::rva0044F679(){if(!m_persistenceCount)return false;const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);if(specialAbilityUpdateModuleData->m_specialPowerTemplate->getFO()->m_type==0x27){
 if(!target && m_useCount<=1)return specialAbilityUpdateModuleData->m_persistentPrepFrames>0;
 if(target && ((target->m_data[0x108]&0x40)||(target->m_data[0x108]&0x40)) && m_useCount<=1)return specialAbilityUpdateModuleData->m_persistentPrepFrames>0;
 return false;
 }
 return specialAbilityUpdateModuleData->m_persistentPrepFrames>0;
}
void SpecialAbilityUpdate::rva0044F6D0()
{
 const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;
 const SpecialPowerTemplate *power=specialAbilityUpdateModuleData->m_specialPowerTemplate;
 Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
 if(m_persistenceCount>0)--m_persistenceCount;
 if(power->getFO()->m_type!=0x27 || (target && ((target=(Object*)target->m_data,((unsigned char*)target)[0x108]&0x40)||((unsigned char*)target)[0x114]&8)))m_prepFrames=specialAbilityUpdateModuleData->m_persistentPrepFrames;
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
 if(m_active || m_data->m_alwaysValidateSpecialObjects || m_expiryFrame)return UPDATE_SLEEP_NONE;
 const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;
 {
   if(specialAbilityUpdateModuleData->m_specialPowerTemplate->getFO()->m_type==0x1D){
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
   if(!specialAbilityUpdateModuleData->fieldA0 && !specialAbilityUpdateModuleData->fieldA4)return UPDATE_SLEEP_FOREVER;
 }
 return UPDATE_SLEEP_NONE;
}


#include "../../../../Include/GameLogic/PartitionFilter.h"
class BfmeFixedStorage0004543D {public:char data[28];};
#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
class Rva0004584D:public Rva000421C8 {public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&) throw();virtual bool allow(Object*);BfmeFixedStorage0004543D a,b;};
// Existing provider ThingIsAnyKindOf.cpp owns this seven-word zero mask.
// The template argument retains its established target ABI spelling.
template<int N>class BitFlags {public:unsigned m_bits[7];};
extern BitFlags<116> KINDOFMASK_NONE;
extern PartitionManager *ThePartitionManager;
#include "../../../../Include/Common/GlobalData.h"
class AbilityAudioEvents:public RunSlots<25>{public:virtual int addAudioEvent(BfmeAudioEventPrefix136*)=0;};
template<int N>class AbilityMiscSlots:public AbilityMiscSlots<N-1>{public:virtual void gapMisc(char(*)[N])=0;};
template<>class AbilityMiscSlots<0>:public AbilityAudioEvents{};
struct BfmeAudioEventPrefix136;
class Xfer;
#include "../../../../Include/Common/GameAudio.h"
#include "../../../../Include/Common/MiscAudioClass.h"
extern AudioManager *TheAudio;
#include "../../../../Include/GameLogic/Module/Rva002D9531.h"
// Primary virtual slot +0x40 at 0x0044FC52..0x0044FEB6 (612B); same
// continuePreparation identity and first two cases as ZH SpecialAbilityUpdate.cpp.
// Native capture FX adds the closest kind50 drawable flash within150 units.
// WB10E3DB0 supplies the corresponding phase/target/audio flow; offsets below
// are native, including capture phase70, ModuleData AF/74 and saturation B54.
// The abort callee is independently established at44F4F7; its real C++ bank
// retains an opening SSE codegen wall and is not compiled in this unit.
bool SpecialAbilityUpdate::continuePreparation()
{
 const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;
 const SpecialPowerTemplate *power=specialAbilityUpdateModuleData->m_specialPowerTemplate;
 if(specialAbilityUpdateModuleData->m_abilityAbortRange<10000000.0f && !isWithinAbilityAbortRange())return false;
 int type=power->getFO()->m_type;
 if(type==0x15){
  Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
  if(!target)return false;
  Relationship r=m_object->getRelationship(target);
  if(r==ALLIES)return false;
  for(AbilityObjectNode *it=m_specialObjects->next;it!=m_specialObjects;it=it->next){
   Object *special=TheGameLogic->findObjectByID(it->id);
   if(special && !initLaser(special,target))return false;
  }
 }else if(type==0x1D || type==0x1A){
  Object *target=TheGameLogic->findObjectByID((ObjectID)m_targetID);
  if(!target)return false;
  Relationship r=m_object->getRelationship(target);
  if(r==ALLIES)return false;
  if(specialAbilityUpdateModuleData->m_doCaptureFX){
   Drawable *draw=((Thing*)target)->getDrawable();
   if(draw){
    bool lastPhase=(int(m_captureFlashPhase)&1)!=0;
    unsigned denom=specialAbilityUpdateModuleData->m_preparationFrames<1?1:specialAbilityUpdateModuleData->m_preparationFrames;
    float denominator=float(denom);
    float increment=1.0f-(float(m_prepFrames)/denominator);
    m_captureFlashPhase+=increment/3.0f;
    bool thisPhase=(int(m_captureFlashPhase)&1)!=0;
    if(lastPhase&&!thisPhase){
     RGBColor houseColor;
     houseColor.setFromInt(m_object->getIndicatorColor());
     draw->saturateRGB(houseColor,TheWritableGlobalData->m_selectionFlashSaturationFactor);
     draw->rva00278C7C((int)&houseColor);
     Rva0004584D filter(*(const BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,0x32),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE);
     const Coord3D *position=&m_object->m_position;
     Object *nearby=ThePartitionManager->getClosestObject(position,150.0f,1,&filter);
     if(nearby){Drawable *nearDraw=((Thing*)nearby)->getDrawable();if(nearDraw)nearDraw->rva00278C7C((int)&houseColor);}
     BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_defectorTimerTickSound,0);
     ((Rva002D9531*)&sound)->rva002D9531(m_targetID);
     TheAudio->addAudioEvent(&sound);
    }
   }
  }
 }
 return true;
}

class LaserUpdate{public:void initLaser(const Object*,const Coord3D*,const Coord3D*,int);};
// ZH SpecialAbilityUpdate::initLaser supplies the bone/geometry/laser flow;
// WB10E3BF0 and game.dat44FB28..44FC52 (RET8) establish target ABI and fields.
// Target LaserUpdate::initLaser has the existing four-argument ABI and receives
// null target plus world-space start/end; target geometry center is copied by
// the already rowed 26B Rva0087DC00::get. Class/type spelling of that opaque
// provider is preserved; it does not assert an original geometry method name.
bool SpecialAbilityUpdate::initLaser(Object *specialObject,Object *target)
{
 const SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData=m_data;
 static NameKeyType key_LaserUpdate=TheNameKeyGenerator->nameToKey("LaserUpdate");
 Drawable *draw=((Thing*)specialObject)->getDrawable();
 if(!draw){killSpecialObjects();return false;}
 LaserUpdate *update=(LaserUpdate*)draw->findClientUpdateModule(key_LaserUpdate);
 if(!update){killSpecialObjects();return false;}
 Coord3D startPos;
 if(!getObject()->getSingleLogicalBonePosition(specialAbilityUpdateModuleData->m_specialObjectAttachToBoneName.str(),&startPos,0)){
  const Coord3D *position=&m_object->m_position;
  startPos.x=position->x;startPos.y=position->y;startPos.z=position->z;
 }
 Coord3D endPos;
 if(target){
  ((Rva0087DC00*)&target->m_geometry)->get((Rva0087DC00Vec*)&endPos);
  endPos.x=target->m_position.x+endPos.x;
  endPos.y=target->m_position.y+endPos.y;
  endPos.z=target->m_position.z+endPos.z;
 }else endPos=startPos;
 update->initLaser(0,&startPos,&endPos,0);
 return true;
}
