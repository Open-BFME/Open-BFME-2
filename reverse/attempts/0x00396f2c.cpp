// ?playEvaEventsForCastlePacking@CastleBehavior@@QAEXXZ
// partial score=0.75 date=2026-10-08
// cl: /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <map>
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "GameLogicObjectLookupView.h"
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
class Player;
class Module;
class Object {
public:
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
class CastleBehavior { public: void registerOwnedObject(Object*); void playEvaEventsForCastlePacking(); };
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

class Team { public: Player* getControllingPlayer() const; };
enum Relationship { REL_ENEMY=0, REL_NEUTRAL=1, REL_ALLY=2 };
class Player { public: Relationship getRelationship(const Team*) const; int getPlayerIndex() const { return *(const int*)((const char*)this+0x54); } };
class PlayerList { char pad[0x10]; Player* local; public: Player* getLocalPlayer() const { return local; } };
extern PlayerList* ThePlayerList;
struct Coord3D;
class Eva { public: char pad[0x84]; unsigned timeout84; int timeout88; void reportEvaEvent(int,const Coord3D*,int); };
extern Eva* TheEva;
class Rva003962E7 { public: bool rva003962E7(int,int); };
class Rva00395561 {
 int count;
public:
 Rva00395561();
 void rva00395561();
 ~Rva00395561() { rva00395561(); }
};
static inline int moduleEvent(Module* m,int offset) { return field<int>(field<void*>(m,4),offset); }
void CastleBehavior::playEvaEventsForCastlePacking() {
 Object* self=field<Object*>(this,8);
 Team* team=field<Team*>(self,0x304);
 if(!team) return;
 Player* controllingPlayer=team->getControllingPlayer();
 if(!controllingPlayer) return;
 Rva00395561 guard;
 Player* localPlayer=ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
 if(!localPlayer) return;
 Object* object=TheGameLogic->findObjectByID(field<ObjectID>(this,0x38));
 Module* module=0;
 if(object) {
  static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
  module=object->findModule(key);
 }
 if(controllingPlayer==localPlayer) {
  if(!((Rva003962E7*)this)->rva003962E7(controllingPlayer->getPlayerIndex(),TheEva->timeout88)) return;
  int event=module ? moduleEvent(module,8) : 9;
  const Coord3D* position=object ? (Coord3D*)((char*)object+0x38) : (Coord3D*)((char*)self+0x38);
 TheEva->reportEvaEvent(event,position,0);
  return;
 }
 Relationship relationship=localPlayer->getRelationship(team);
 if(relationship==REL_ALLY) {
  if(!((Rva003962E7*)this)->rva003962E7(controllingPlayer->getPlayerIndex(),TheEva->timeout88)) return;
  int event=module ? moduleEvent(module,0xc) : 10;
  const Coord3D* position=object ? (Coord3D*)((char*)object+0x38) : (Coord3D*)((char*)self+0x38);
 TheEva->reportEvaEvent(event,position,0);
  return;
 }
 if(relationship!=REL_ENEMY) return;
 int playerKey=field<int>(localPlayer,0x54);
 _STL::map<int,int>& map=field<_STL::map<int,int> >(this,0xa0);
 _STL::map<int,int>::iterator it=map.find(playerKey);
 if(it==map.end()) return;
 if(TheEva->timeout84+(unsigned)it->second < TheGameLogic->getFrame()) return;
 int event=module ? moduleEvent(module,0x10) : 8;
 const Coord3D* position=object ? (Coord3D*)((char*)object+0x38) : (Coord3D*)((char*)self+0x38);
 TheEva->reportEvaEvent(event,position,0);
}
