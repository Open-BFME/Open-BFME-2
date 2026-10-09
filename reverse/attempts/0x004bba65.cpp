// ?onCollide@SquishCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Reference: GeneralsMD SquishCollide.cpp at BFME1 donor874e38488;
// original SquishCollide identity comes from rowed ctor4BB9CF, factory250FE6,
// name getter4BB962 and the native CollideModuleInterface vtable.
// Native boundary4BBA65..4BBEDD RET12: crushable/crusher levels; moving
// toward victim; geom copy5C/5.0 radii/intersection; damage7C; native
// damage impulse10.0/1.0 and lethal999999.0. Additional BFME2 branches
// are target facts, not extrapolated ZH behavior. Unknown fields retain
// offset names. Two target-observed Object calls remain unpinned:2929F9
// 848B void(Object*) and28F44C112B bool(Object*), both thiscall RET4.
// Codegen wall: compiled1148B/104-frame versus1144B/104 retail; compiler
// caches adjusted receiver inESI early, self inEDI; retail spills both
// pointers atEBP-14/-10 and saves ESI/EDI after the level comparison.
// Hierarchy/getter relocation, condition splitting, const, aggregate
// context and O1/O2/G6/Ob1/Op trials do not close that allocation wall.
struct Coord3D { float x,y,z;void normalize(); };
class Object;
class GeometryInfo {
public: GeometryInfo(const GeometryInfo&);virtual ~GeometryInfo();
 void rva004BBA15(float);void rva004BBA3D(float);
 bool bfmeIntersects(const Coord3D&,float,const GeometryInfo&,const Coord3D&,float)const;
private: char unknown04[0x58];
};
class DamageInfo {
public: DamageInfo();
 char unknown00[8];int sourceID;int unknown0C;int damageType;char unknown14[8];int deathType;float amount;
 char unknown24[0x10];Coord3D direction;float magnitude;float unknown44;float unknown48;float unknown4C;char unknown50[0x2C];
};
class Weapon {
public: bool rva002C969D(const void*,int);bool rva002CE6C5(const Object*,int,const Object*,int*);
};
enum ObjectStatusTypes {STATUS32=0x32,STATUS39=0x39};
enum KindOfType {KIND84=0x84};
enum Relationship {ENEMIES=0,NEUTRAL=1,ALLIES=2};
enum NameKeyType {NK_UNKNOWN=0};
enum WeaponSlotType {SLOT_PRIMARY=0};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class StateMachine {public:Object* getGoalObject();};
class AIUpdateInterface {
public:
 virtual void unknown00();
 virtual void unknown01();
 virtual void unknown02();
 virtual void unknown03();
 virtual void unknown04();
 virtual void unknown05();
 virtual void unknown06();
 virtual void unknown07();
 virtual void unknown08();
 virtual void unknown09();
 virtual void unknown0A();
 virtual void unknown0B();
 virtual void unknown0C();
 virtual void unknown0D();
 virtual void unknown0E();
 virtual void unknown0F();
 virtual void unknown10();
 virtual void unknown11();
 virtual void unknown12();
 virtual void unknown13();
 virtual void unknown14();
 virtual void unknown15();
 virtual void unknown16();
 virtual void unknown17();
 virtual void unknown18();
 virtual void unknown19();
 virtual void unknown1A();
 virtual void unknown1B();
 virtual void unknown1C();
 virtual void unknown1D();
 virtual void unknown1E();
 virtual void unknown1F();
 virtual void unknown20();
 virtual void unknown21();
 virtual void unknown22();
 virtual void unknown23();
 virtual void unknown24();
 virtual void unknown25();
 virtual void unknown26();
 virtual void unknown27();
 virtual void unknown28();
 virtual void unknown29();
 virtual void unknown2A();
 virtual void unknown2B();
 virtual void unknown2C();
 virtual void unknown2D();
 virtual void unknown2E();
 virtual void unknown2F();
 virtual void unknown30();
 virtual void unknown31();
 virtual void unknown32();
 virtual void unknown33();
 virtual void unknown34();
 virtual void unknown35();
 virtual void unknown36();
 virtual void unknown37();
 virtual void unknown38();
 virtual void unknown39();
 virtual void unknown3A();
 virtual void unknown3B();
 virtual void unknown3C();
 virtual void unknown3D();
 virtual void unknown3E();
 virtual void unknown3F();
 virtual void unknown40();
 virtual void unknown41();
 virtual void unknown42();
 virtual void unknown43();
 virtual void unknown44();
 virtual void unknown45();
 virtual void unknown46();
 virtual void unknown47();
 virtual void unknown48();
 virtual void unknown49();
 virtual void unknown4A();
 virtual void unknown4B();
 virtual void unknown4C();
 virtual void unknown4D();
 virtual void unknown4E();
 virtual void unknown4F();
 virtual void unknown50();
 virtual void unknown51();
 virtual void unknown52();
 virtual void unknown53();
 virtual void unknown54();
 virtual void unknown55();
 virtual void unknown56();
 virtual void unknown57();
 virtual void unknown58();
 virtual void unknown59();
 virtual void unknown5A();
 virtual void unknown5B();
 virtual void unknown5C();
 virtual void unknown5D();
 virtual void unknown5E();
 virtual void unknown5F();
 virtual void unknown60();
 virtual void unknown61();
 virtual Object* targetObject();
 char pad04[0x2C];StateMachine *machine;
};
class BodyModuleInterface {
public:
 virtual void unknown00();
 virtual void unknown01();
 virtual void unknown02();
 virtual void unknown03();
 virtual void unknown04();
 virtual void unknown05();
 virtual void unknown06();
 virtual void unknown07();
 virtual void unknown08();
 virtual void unknown09();
 virtual void unknown0A();
 virtual void unknown0B();
 virtual void unknown0C();
 virtual void unknown0D();
 virtual void unknown0E();
 virtual void unknown0F();
 virtual void unknown10();
 virtual void unknown11();
 virtual void unknown12();
 virtual void unknown13();
 virtual void unknown14();
 virtual void unknown15();
 virtual void unknown16();
 virtual void unknown17();
 virtual void unknown18();
 virtual void unknown19();
 virtual void unknown1A();
 virtual void unknown1B();
 virtual void unknown1C();
 virtual void unknown1D();
 virtual void unknown1E();
 virtual void unknown1F();
 virtual void unknown20();
 virtual void unknown21();
 virtual void unknown22();
 virtual void unknown23();
 virtual void unknown24();
 virtual void unknown25();
 virtual bool permitsCrushing(Object*);
};
class ActiveAbilityView {public:virtual void unknown0();virtual void unknown4();virtual bool isActive();};
class SpecialAbilityUpdate {public:char unknown00[0x20];ActiveAbilityView active;};
class ExperienceView {public:char unknown00[0x5C];bool dead;};
class ThingTemplate {
public:char unknown00[0x114];unsigned int flags;char unknown118[0x608-0x118];float crushMagnitude;float crushExtra;char unknown610[4];bool crushAllies;
};
class Thing {
public:
 void getUnitDirectionVector2D(Coord3D&)const;
 const Coord3D*getPosition()const{return &position;}
 float getOrientation()const{return orientation;}
 char unknown00[4];ThingTemplate *tmplate;char unknown08[0x30];Coord3D position;float orientation;
};
class Object: public Thing {
public:
 signed char rva0028CE7B()const;
 char rva00294815();
 const Weapon*getCurrentWeapon(WeaponSlotType*)const;
 bool testStatus(ObjectStatusTypes)const;
 bool isKindOf(KindOfType)const;
 Relationship getRelationship(const Object*)const;
 Module*findModule(NameKeyType)const;
 void *rva0028BD92(int);
 void rva00295FA9(Object*);
 void rva002929F9(Object*);
 bool rva0028F44C(Object*);
 void attemptDamage(DamageInfo*);
 void rva0028AC34(bool);
 GeometryInfo const&getGeometryInfo()const{return geometry;}
 int getID()const{return id;}
 bool destroyed()const{return (flags438&1)!=0;}
 char unknown48[0x2C];int id;char unknown78[0x30];GeometryInfo geometry;
 char unknown104[0x150];BodyModuleInterface *body;AIUpdateInterface *ai;ExperienceView *experience;
 char unknown260[0x13C];Weapon*crushWeapon;Weapon*crushedWeapon;char unknown3A4[0x94];unsigned char flags438;
 char unknown439[0x87];int targetID4C0;
};
class Rva0028E8D4 {public:void rva0028E8D4(float*)const;};
class Rva0028CECFOwner {public:bool rva0028CECF();};
class ModuleData;
class Module {public:virtual ~Module();protected:const ModuleData*m_data;};
class ObjectModule:public Module {protected:Object*m_object;Object*getObject()const{return m_object;}};
class BehaviorModule:public ObjectModule {};
class BehaviorModuleInterface {public:virtual void anchor();};
class CollideModuleInterface {public:virtual void onCollide(Object*,const Coord3D*,const Coord3D*)=0;};
class CollideModule:public BehaviorModule,public BehaviorModuleInterface,public CollideModuleInterface {

};
class SquishCollide: public CollideModule {
public:virtual void onCollide(Object*,const Coord3D*,const Coord3D*);
};

void SquishCollide::onCollide(Object *other,const Coord3D *loc,const Coord3D *normal)
{
 if(!other || other->destroyed() || (other->tmplate->flags&0x2000))return;
 Object*self=getObject();
 if(self->destroyed() || self->experience->dead)return;
 signed char crushable=self->rva0028CE7B();
 if(other->rva00294815()<=crushable)return;
 AIUpdateInterface*otherAI=other->ai;
 if(otherAI){
  Object*target=otherAI->targetObject();
  if(target){if(target->targetID4C0==self->getID())return;}
  else if(otherAI->machine->getGoalObject()==self && other->getCurrentWeapon(0) && ((Weapon*)other->getCurrentWeapon(0))->rva002C969D(other,(int)self))return;
 }
 Coord3D direction;other->getUnitDirectionVector2D(direction);
 Coord3D actualPosition;((Rva0028E8D4*)other)->rva0028E8D4(&actualPosition.x);
 const Coord3D*myPos=getObject()->getPosition();
 Coord3D to;
 to.x=myPos->x-other->getPosition()->x;
 to.y=myPos->y-other->getPosition()->y;
 if(to.x*direction.x+to.y*direction.y<0.0f){
  to=*myPos;
  to.x-=actualPosition.x;to.y-=actualPosition.y;
  if(to.x*direction.x+to.y*direction.y<0.0f)return;
 }
 if(!other->testStatus(STATUS39) && !other->testStatus(STATUS32) && !other->isKindOf(KIND84) && !other->tmplate->crushAllies && other->getRelationship(getObject())!=ENEMIES)return;
 AIUpdateInterface *ai=self->ai;
 if(ai && ai->machine->getGoalObject()==other){
  static NameKeyType key_HijackerUpdate=TheNameKeyGenerator->nameToKey("HijackerUpdate");
  if(self->findModule(key_HijackerUpdate))return;
  SpecialAbilityUpdate *ability=(SpecialAbilityUpdate*)self->rva0028BD92(0x19);
  if(ability && ability->active.isActive())return;
 }
 GeometryInfo myGeom=self->getGeometryInfo();
 myGeom.rva004BBA15(5.0f);myGeom.rva004BBA3D(5.0f);
 if(!other->getGeometryInfo().bfmeIntersects(*other->getPosition(),other->getOrientation(),myGeom,*self->getPosition(),self->getOrientation()))return;
 if(!((Rva0028CECFOwner*)other)->rva0028CECF()){
  other->rva00295FA9(getObject());return;
 }
 BodyModuleInterface *body=getObject()->body;
 if(body && !body->permitsCrushing(other))return;
 DamageInfo damageInfo;
 other->rva002929F9(getObject());
 if(other->tmplate->crushMagnitude>0.0f){
  to.x=self->getPosition()->x-other->getPosition()->x;
  to.y=self->getPosition()->y-other->getPosition()->y;
  to.z=self->getPosition()->z-other->getPosition()->z;
  to.normalize();
  damageInfo.direction=to;
  damageInfo.magnitude=other->tmplate->crushMagnitude;
  damageInfo.unknown4C=other->tmplate->crushExtra;
  damageInfo.deathType=0;
  damageInfo.unknown44=10.0f;
  damageInfo.unknown48=1.0f;
  damageInfo.sourceID=other->getID();
  damageInfo.damageType=1;
  damageInfo.amount=0.0f;
  self->attemptDamage(&damageInfo);
 }
 if(!(other->tmplate->flags&0x2000)){
  if(other->crushWeapon)other->crushWeapon->rva002CE6C5(other,getObject()->getID(),getObject(),0);
  else {
   damageInfo.sourceID=other->getID();damageInfo.damageType=1;damageInfo.deathType=2;damageInfo.amount=999999.0f;
   getObject()->attemptDamage(&damageInfo);
  }
  Weapon *crushedWeapon=getObject()->crushedWeapon;
  if(crushedWeapon && !getObject()->rva0028F44C(other))crushedWeapon->rva002CE6C5(getObject(),other->getID(),other,0);
 }
 other->rva0028AC34(false);
}
