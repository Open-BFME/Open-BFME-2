// cl: /O1 /G7 /MD /arch:SSE /EHsc
// Semantic donor: GeneralsMD InactiveBody.cpp carried at Open-BFME-1
// 575ba2b04743f190f069805fbdc59936123c45da.
// Target constructor 4BD8BD stores the body-interface table VA C5ACC8 at +10.
// Slots 0/1 are damage 4BD92C (78B) and healing 4BD7D4 (41B).
// Its module object is +8, scalar +14 and dieCalled +18; the method bodies
// receive the body-interface subobject, so object is -8 and dieCalled +8.
// WB124F640 names attemptDamage; both callbacks follow the donor behavior.
// Target DamageInfo type is +10, output floats +70/+74, noEffect +78.
// Damage type 7 is healing, type 8 is unresistable in donor and target.
// Only the accessed class/interface prefixes are declared; no vtable emitted.
struct DamageInfo {
 char prefix[0x10]; int damageType;
 char middle[0x70-0x14];
 float actualDamageDealt, actualDamageClipped;
 bool noEffect;
};
class Object {public:void onDie(DamageInfo*);};
class ModuleData;
class ObjectModule {
public:virtual ~ObjectModule();
protected:const ModuleData *moduleData;Object *object;
};
class BehaviorModuleInterface {public:virtual void unknownBehaviorSlot()=0;};
class BodyModuleInterface {
public:virtual void attemptDamage(DamageInfo*)=0;
 virtual void attemptHealing(DamageInfo*)=0;
};
class BodyModule : public ObjectModule,public BehaviorModuleInterface,public BodyModuleInterface {
protected:float damageScalar;
};
class InactiveBody : public BodyModule {
public:virtual void attemptDamage(DamageInfo*);
 virtual void attemptHealing(DamageInfo*);
private:bool dieCalled;
};
void InactiveBody::attemptDamage(DamageInfo *damageInfo){
 if(!damageInfo)return;
 if(damageInfo->damageType==7){attemptHealing(damageInfo);return;}
 damageInfo->actualDamageDealt=0.0f;
 damageInfo->actualDamageClipped=0.0f;
 damageInfo->noEffect=true;
 if(damageInfo->damageType==8){
  damageInfo->noEffect=false;
  if(!dieCalled){object->onDie(damageInfo);dieCalled=true;}
 }
}

void InactiveBody::attemptHealing(DamageInfo *damageInfo){
 if(!damageInfo)return;
 if(damageInfo->damageType!=7){attemptDamage(damageInfo);return;}
 damageInfo->actualDamageDealt=0.0f;
 damageInfo->actualDamageClipped=0.0f;
 damageInfo->noEffect=true;
}
