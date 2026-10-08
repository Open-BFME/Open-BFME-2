// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Source lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/System/CastleBehaviorRegisterOwnedObject.cpp.
// Native 0x003986EF..0x003988BF, 464B. Existing createOwnedObject calls this
// registration pin; CastleMemberBehavior lookup and owner ID assignment
// independently support the donor identity. WB names the same flow
// DecideCastlesRelationshipToNewObject. Native fields, kind-flag masks,
// status values and callees replace the donor layout. Field names remain
// unresolved; ObjectID vector push_back uses the existing folded pin.
// The one local-static key and shared ID temporary preserve retail EH
// and stack-slot reuse. No new callee pins are needed.
#include <vector>
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../Common/GameLogicObjectLookupView.h"
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
class Player;
class Module;
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
class Object {
public:
 void* rva0028BCF4() const;
 void kill(DamageType,DeathType);
 void rva0028D282(void*);
 Player* getControllingPlayer() const;
 void setStatus(ObjectStatusTypes,bool);
protected:
 Module* findModule(NameKeyType) const;
 friend class CastleBehavior;
};
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;

extern GameLogic* TheGameLogic;
class Rva2225E0Filter { public: bool accepts(Object*,Player*); };
class Rva00395F0B { public: void rva00395F0B(Object*); };
class FoundationAIUpdate { void rva0045527A(ObjectID); friend class CastleBehavior; };
template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }
inline void* objectTemplate(Object* object) { return field<void*>(object,4); }
inline ObjectID objectID(Object* object) { return field<ObjectID>(object,0x74); }
class CastleBehavior { public: void registerOwnedObject(Object*); bool checkForAutoPack(); void rva00397B03(ObjectStatusTypes,bool); };
void CastleBehavior::registerOwnedObject(Object* object) {
 void* data=field<void*>(this,4);
 Object* owner=field<Object*>(this,8);
 if(!object) return;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 Module* member=object->findModule(key);
 ObjectID id;
 if(member) field<ObjectID>(member,0x18)=objectID(owner);
 if(field<unsigned char>(objectTemplate(object),0x11e)&4) object->setStatus(OBJECT_STATUS_79,true);
 if(field<unsigned char>(objectTemplate(object),0x10b)&0x10) {
  if(!field<ObjectID>(this,0x38)) {
   field<ObjectID>(this,0x38)=objectID(object);
   if(field<float>(object,0x324)==0.0f && field<float>(this,0x4c)!=0.0f) {
    field<float>(object,0x324)=field<float>(this,0x4c);
    field<float>(this,0x4c)=0.0f;
   }
   if(member) { field<bool>(member,0x24)=true; field<ObjectID>(member,0x14)=field<ObjectID>(this,0x38); }
   ((FoundationAIUpdate*)this)->rva0045527A(field<ObjectID>(this,0x38));
  } else TheGameLogic->destroyObject(object);
 } else if(field<unsigned>(objectTemplate(object),0x118)&0x2000000) {
  id=objectID(object); ((_STL::vector<ObjectID>*)((char*)this+0x74))->push_back(id);
 } else if((field<unsigned char>(objectTemplate(object),0x115)&1) || (field<unsigned>(objectTemplate(object),0x118)&0x400000)) {
  id=objectID(object); ((_STL::vector<ObjectID>*)((char*)this+0x50))->push_back(id);
  if(field<unsigned>(objectTemplate(object),0x118)&0x400000) object->setStatus(OBJECT_STATUS_5,false);
 } else if(((Rva2225E0Filter*)((char*)data+0x34))->accepts(object,owner->getControllingPlayer()) && ((Rva2225E0Filter*)((char*)data+0x30))->accepts(object,owner->getControllingPlayer())) {
  id=objectID(object); ((_STL::vector<ObjectID>*)((char*)this+0x68))->push_back(id);
  ((Rva00395F0B*)this)->rva00395F0B(object);
 } else {
  id=objectID(object); ((_STL::vector<ObjectID>*)((char*)this+0x5c))->push_back(id);
 }
 TheGameLogic->rva0023D0C2(object,field<int>(this,0x9c));
}

// Native 0x003974CE..0x003975B7, 233B. CastleSystem auto-pack 0x003975B7
// passes two native callbacks with an opaque zero context. The helper visits
// owner +8, factory +0x20 slot +0x18, then ID vectors +0x74/+0x50/+0x68/+0x5c.
// Callback and helper source identities remain address-derived.
class Rva003974CEFactory {
public:
 virtual void unused0(); virtual void unused1(); virtual void unused2();
 virtual void unused3(); virtual void unused4(); virtual void unused5();
 virtual Object* getObject();
};
typedef int (__cdecl *CastleObjectCallback)(Object*,int);
class Rva003974CE {
public:
 Object* getOwner() const { return *(Object* const*)((const char*)this+8); }
 int apply(CastleObjectCallback callback,int context);
};
static __forceinline bool applyCastleRange(const _STL::vector<ObjectID>& ids,CastleObjectCallback callback,int context) {
 for(_STL::vector<ObjectID>::const_iterator it=ids.begin(); it!=ids.end(); ++it) {
  Object* object=TheGameLogic->findObjectByID(*it);
  if(object && !callback(object,context)) return false;
 }
 return true;
}
int Rva003974CE::apply(CastleObjectCallback callback,int context) {
 if(!callback(getOwner(),context)) return 0;
 Object* object=((Rva003974CEFactory*)((char*)this+0x20))->getObject();
 if(object && !callback(object,context)) return 0;
 if(!applyCastleRange(field<_STL::vector<ObjectID> >(this,0x74),callback,context)) return 0;
 if(!applyCastleRange(field<_STL::vector<ObjectID> >(this,0x50),callback,context)) return 0;
 if(!applyCastleRange(field<_STL::vector<ObjectID> >(this,0x68),callback,context)) return 0;
 if(!applyCastleRange(field<_STL::vector<ObjectID> >(this,0x5c),callback,context)) return 0;
 return 1;
}

// Native cdecl callback VA795AD2..795AF2 (32B), embedded at 0x0039763C.
// Its second word is unused; the witnessed traversal call supplies zero.
int Rva00395AD2Destroy(Object* object,int context) {
 if(field<unsigned char>(objectTemplate(object),0x115)&1)
  TheGameLogic->destroyObject(object);
 return 1;
}

// Native cdecl callback VA795A9F..795AD2 (51B), embedded at 0x0039762F.
// The template flag redirects the kill to the module slot-6 object; retail
// assumes the module exists on that path. Callback context is unused.
class Rva00395A9FInterface {
public:
 virtual void unused0(); virtual void unused1(); virtual void unused2();
 virtual void unused3(); virtual void unused4(); virtual void unused5();
 virtual Object* getObject();
};
int Rva00395A9FKill(Object* object,int context) {
 if(object) {
  if(field<unsigned char>(objectTemplate(object),0x115)&1)
   object=((Rva00395A9FInterface*)object->rva0028BCF4())->getObject();
  if(object) object->kill(DAMAGE_8,DEATH_0);
 }
 return 1;
}

// CastleBehavior::checkForAutoPack, native RVA003975B7, 415 bytes.
// Semantic donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00371B00.cpp.
// Native layouts, timer scale, disposal flag and callbacks verified independently.
class GlobalData { public: char pad[0x110c]; float secondsBeforeBaseCheckActive; };
extern GlobalData* TheWritableGlobalData;
extern int g_Va00DBA4E4;
class Rva003975B7Projectile {
public:
 virtual void unused0(); virtual void unused1(); virtual void unused2();
 virtual bool query();
};
static __forceinline bool castleBit(Object* object,int wordOffset,int bit) {
 return ((field<unsigned>(object,wordOffset)>>bit)&1)!=0;
}
static __forceinline bool anyCastleProjectile(const _STL::vector<ObjectID>& ids) {
 for(_STL::vector<ObjectID>::const_iterator it=ids.begin();it!=ids.end();++it) {
  Object* object=TheGameLogic->findObjectByID(*it);
  if(!object) continue;
  if(field<unsigned>(objectTemplate(object),0x118)&0x400000) continue;
  Rva003975B7Projectile* projectile=(Rva003975B7Projectile*)object->rva0028BCF4();
  if(projectile && projectile->query()) return true;
 }
 return false;
}
bool CastleBehavior::checkForAutoPack() {
 GlobalData* global=TheWritableGlobalData;
 GameLogic* logic=TheGameLogic;
 unsigned frame=logic->getFrame();
 unsigned threshold=(unsigned)(int)(global ? global->secondsBeforeBaseCheckActive*(float)g_Va00DBA4E4 : 25.0f);
 if(frame<threshold) return false;
 void* data=field<void*>(this,4);
 Object* object=logic->findObjectByID(field<ObjectID>(this,0x38));
 if(!object) {
  if(field<bool>(data,0x3d)) {
    ((Rva003974CE*)this)->apply(Rva00395A9FKill,0);
    ((Rva003974CE*)this)->apply(Rva00395AD2Destroy,0);
    field<bool>(this,0x3d)=true;
    TheGameLogic->destroyObject(field<Object*>(this,8));
    return false;
  }
  field<bool>(this,0x3d)=true;
 } else {
  field<bool>(this,0x3d)=false;
  if(field<unsigned char>(object,0x438)&1) {
   if(field<bool>(data,0x3d)) {
    ((Rva003974CE*)this)->apply(Rva00395A9FKill,0);
    ((Rva003974CE*)this)->apply(Rva00395AD2Destroy,0);
    field<bool>(this,0x3d)=true;
    TheGameLogic->destroyObject(field<Object*>(this,8));
    return false;
   }
   field<bool>(this,0x3d)=true;
  }
  if(castleBit(object,0x114,3)) field<bool>(this,0x3d)=true;
  if(castleBit(object,0x114,4)) {
   Object* builder=TheGameLogic->findObjectByID(field<ObjectID>(object,0x7c));
   if(!builder || ((field<unsigned char>(builder,0x438)&1) && (field<unsigned char>(objectTemplate(builder),0x109)&0x40)))
    field<bool>(this,0x3d)=true;
  }
  if(castleBit(object,0x110,28)) field<bool>(this,0x3d)=true;
 }
 if(!field<bool>(this,0x3d) || anyCastleProjectile(field<_STL::vector<ObjectID> >(this,0x50)) || anyCastleProjectile(field<_STL::vector<ObjectID> >(this,0x74))) return false;
 return true;
}

// Native RVA00397B03, 134 bytes; called by checkForInstantUnPack with (79,false).
// Semantic donor ba7ddda7 CastleBehaviorRva00371EE0StatusBit.cpp, adapted to
// native pending ID +0x38 and vector +0x5C with the rowed Object status setter.
// WB leaves the method unnamed, so retain an address-derived identity.
class ScriptEngine;
extern ScriptEngine* TheScriptEngine;
class Rva002039B6Host { public: void rva002039B6(); };
void CastleBehavior::rva00397B03(ObjectStatusTypes status,bool set) {
 Object* pending=TheGameLogic->findObjectByID(field<ObjectID>(this,0x38));
 if(pending) {
  if(set) pending->setStatus(status,true);
  else pending->setStatus(status,false);
 }
 for(unsigned i=0;i<field<_STL::vector<ObjectID> >(this,0x5c).size();++i) {
  Object* object=TheGameLogic->findObjectByID(field<_STL::vector<ObjectID> >(this,0x5c)[i]);
  if(object) {
   if(set) object->setStatus(status,true);
   else object->setStatus(status,false);
  }
 }
 ((Rva002039B6Host*)TheScriptEngine)->rva002039B6();
}

// WB names CastleBehavior::mapLoadPostProcess; native 0x0039585A is a
// 156B interface method whose owner is at this-4, so keep the receiver
// address-derived until its exact base type is established. The RET4
// argument is unused. The existing rva0028D282 provider spells its raw
// argument void*; this caller proves it transports the player index word.
enum CellShroudStatus { CELL_NATIVE_1=1 };
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager* TheShroudManager;
class PlayerList;
extern PlayerList* ThePlayerList;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Rva00395561 {
 int count;
public:
 Rva00395561();
 void rva00395561();
 ~Rva00395561() { rva00395561(); }
};
class Rva0039585A { public: void mapLoadPostProcess(int context); };
void Rva0039585A::mapLoadPostProcess(int context) {
 GameLogic* logic=TheGameLogic;
 if(logic && (logic->isInMultiplayerGame() || field<int>(logic,0x110)==2)) {
  Object* object=field<Object*>(this,-4);
  if(TheShroudManager && object && ThePlayerList && field<Player*>(ThePlayerList,0x10)) {
   Rva00395561 guard;
   int index=field<int>(field<Player*>(ThePlayerList,0x10),0x54);
   if(TheShroudManager->getShroudStatusForPlayer(index,&field<Coord3D>(object,0x38))==CELL_NATIVE_1)
    object->rva0028D282((void*)index);
  }
 }
}
