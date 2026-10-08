// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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
class Xfer;
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../Common/GameLogicObjectLookupView.h"
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
class Player;
class Module;
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
class Team;
struct Coord3D;
class Drawable;
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
class Object {
public:
 float getCastleValue() const { return *(const float*)((const char*)this+0x324); }
 float GetRelativeAngle(const Coord3D*) const;
 Coord3D* getPlanarDirectionTo(Coord3D*,const Object*) const;
 float getBoundingCircleRadius() const { return *(const float*)((const char*)this+0xb8); }
 Relationship getRelationship(const Object*) const;
 int rva0028B511() const;
 bool testStatus(ObjectStatusTypes) const;
 Object* rva002931F5(bool);
 void* rva0028C197() const;
 void teleportTo(const Coord3D*,bool);
 Drawable* getDrawable() const;
 void* rva0028BCF4() const;
 void kill(DamageType,DeathType);
 void rva0028D282(void*);
 Player* getControllingPlayer() const;
 void setStatus(ObjectStatusTypes,bool);
 void setTeam(Team*); void rva0028BAC0(); void rva0028DCC4(); void rva0028D253(); void rva0028AE6D();
protected:
 Module* findModule(NameKeyType) const;
 friend class CastleBehavior;
 friend class Rva00399959;
 friend void Rva00396BC5SetCastleId(_STL::vector<ObjectID>*,ObjectID);
};
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;

extern GameLogic* TheGameLogic;
class Rva2225E0Filter { public: bool accepts(Object*,Player*); };
class Rva00395F0B { public: void rva00395F0B(Object*); };
class FoundationAIUpdate { protected: virtual void xfer(Xfer*); private: void rva0045527A(ObjectID); friend class CastleBehavior;
 friend class Rva00399959; };
template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }
inline void* objectTemplate(Object* object) { return field<void*>(object,4); }
inline ObjectID objectID(Object* object) { return field<ObjectID>(object,0x74); }
class BuildListInfo;
class ThingTemplate;
class CastleBehavior { public: Object* buildCastleStructure(BuildListInfo*,bool); void* GetArmyIDFromClosestObject(); Object* createOwnedObject(void*); void rva003993F2(bool); void teleportStragglersFromWallToGround(bool); void registerOwnedObject(Object*); bool checkForAutoPack(); bool checkForInstantUnPack(); void rva00397B03(ObjectStatusTypes,bool); void DoXfer(Xfer*); void rva00399370(); void rva0039792B(); void initiateUnpack(bool,const ThingTemplate*); };
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

// CastleBehavior::DoXfer: WB named identity and native630B boundary.
// Existing vector<ScienceType> serialization provider is a measured 4-byte
// ABI view: these caller fields contain ObjectIDs, not established sciences.
// Field +0x98 is AsciiString, independently witnessed by unpack.
// One shared ObjectID temporary preserves native stack-slot reuse.
class AsciiString;
struct CastleXferVersion { unsigned char first,second; CastleXferVersion(unsigned char a,unsigned char b):first(a),second(b){} };
class Xfer {
public:
 virtual ~Xfer();
 virtual bool isLoading();
 virtual bool isSaving();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual Xfer& raw(void*,unsigned);
 virtual Xfer& version(CastleXferVersion&);
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual Xfer& xferAsciiString(AsciiString&);
 virtual Xfer& real28(float&);
 virtual void slot29();
 virtual Xfer& unsignedInt(unsigned&);
 virtual Xfer& signedInt(int&);
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual Xfer& boolean(bool&);

};
enum ScienceType { SCIENCE_0=0 };
Xfer* Rva00398280Xfer(Xfer*,_STL::vector<ScienceType>*);
void XferObjectID(Xfer*,ObjectID*);
void XferLivingWorldArmyID(Xfer*,int*);
void CastleBehavior::DoXfer(Xfer* xfer) {
 CastleXferVersion version(1,2);
 ObjectID id;
 xfer->version(version);
 xfer->raw(&field<int>(this,0x34),4);
 XferObjectID(xfer,&field<ObjectID>(this,0x38));
 xfer->boolean(field<bool>(this,0x3c));
 xfer->boolean(field<bool>(this,0x3d));
 xfer->real28(field<float>(this,0x40));
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x50));
 XferLivingWorldArmyID(xfer,&field<int>(this,0x9c));
 unsigned countA=field<_STL::vector<ObjectID> >(this,0x50).size();
 xfer->signedInt((int&)countA);
 if(xfer->isSaving()) {
  for(_STL::vector<ObjectID>::iterator it=field<_STL::vector<ObjectID> >(this,0x50).begin();it!=field<_STL::vector<ObjectID> >(this,0x50).end();++it) {
   id=*it;
   XferObjectID(xfer,&id);
  }
 } else {
  _STL::vector<ObjectID>& foundations=field<_STL::vector<ObjectID> >(this,0x50);
  foundations.erase(foundations.begin(),foundations.end());
  for(unsigned i=0;i<countA;++i) { XferObjectID(xfer,&id); field<_STL::vector<ObjectID> >(this,0x50).push_back(id); }
 }
 unsigned countB=field<_STL::vector<ObjectID> >(this,0x5c).size();
 xfer->signedInt((int&)countB);
 if(xfer->isSaving()) {
  for(_STL::vector<ObjectID>::iterator it=field<_STL::vector<ObjectID> >(this,0x5c).begin();it!=field<_STL::vector<ObjectID> >(this,0x5c).end();++it) {
   id=*it; XferObjectID(xfer,&id);
  }
 } else {
  for(unsigned i=0;i<countB;++i) { XferObjectID(xfer,&id); field<_STL::vector<ObjectID> >(this,0x5c).push_back(id); }
 }
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x68));
 xfer->unsignedInt(field<unsigned>(this,0x48));
 if(version.second>=2) xfer->boolean(field<bool>(this,0x44));
 if(xfer->isLoading() && field<int>(this,0x34)!=0) rva00399370();
 ((FoundationAIUpdate*)this)->FoundationAIUpdate::xfer(xfer);
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x74));
 xfer->xferAsciiString(field<AsciiString>(this,0x98));
 if(xfer->isSaving()) {
  unsigned count=field<_STL::map<int,int> >(this,0xa0).size();
  xfer->signedInt((int&)count);
  for(_STL::map<int,int>::iterator it=field<_STL::map<int,int> >(this,0xa0).begin();it!=field<_STL::map<int,int> >(this,0xa0).end();++it) {
   int key=it->first; xfer->signedInt(key);
   unsigned value=it->second; xfer->unsignedInt(value);
  }
 } else {
  unsigned count;
  xfer->signedInt((int&)count);
  while(count) {
   int key; unsigned value;
   xfer->signedInt(key); xfer->unsignedInt(value);
   field<_STL::map<int,int> >(this,0xa0).insert(_STL::pair<const int,int>(key,value));
   --count;
  }
 }
}

// Native RVA00396BC5,126B, shared by unpack for vectors +0x50/+0x5C/+0x74.
// WB leaves the free function unnamed. Native initializes the module key
// before iteration and writes the supplied ObjectID into module +0x14.
void Rva00396BC5SetCastleId(_STL::vector<ObjectID>* ids,ObjectID id) {
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 for(_STL::vector<ObjectID>::iterator it=ids->begin();it!=ids->end();++it) {
  Object* object=TheGameLogic->findObjectByID(*it);
  if(object) {
   Module* module=object->findModule(key);
   if(module) field<ObjectID>(module,0x14)=id;
  }
 }
}

// Native RVA0039792B,203B; invoked by unpack after ownership setup.
// WB confirms Pathfinder::AddObjectToPathfindMap, but leaves this helper
// unnamed. Native vectors +0x5C/+0x50 and pending ID +0x38, template bit60.
class Pathfinder { public: void AddObjectToPathfindMap(Object*); void RemoveObjectFromPathfindMap(Object*); };
class AI;
extern AI* TheAI;
static __forceinline void addCastlePathObject(Object* object) {
 if(object && (field<unsigned>(objectTemplate(object),0x10c)&0x10000000))
  field<Pathfinder*>(TheAI,0x10)->AddObjectToPathfindMap(object);
}
void CastleBehavior::rva0039792B() {
 for(unsigned i=0;i<field<_STL::vector<ObjectID> >(this,0x5c).size();++i)
  addCastlePathObject(TheGameLogic->findObjectByID(field<_STL::vector<ObjectID> >(this,0x5c)[i]));
 for(unsigned i=0;i<field<_STL::vector<ObjectID> >(this,0x50).size();++i)
  addCastlePathObject(TheGameLogic->findObjectByID(field<_STL::vector<ObjectID> >(this,0x50)[i]));
 addCastlePathObject(TheGameLogic->findObjectByID(field<ObjectID>(this,0x38)));
}

// WB 0x00EBDE20 names CastleBehavior::checkForInstantUnPack; native
// 0x00399D54..0x00399EB3, 351B. Player-search locals and break follow the
// WB source flow; extracting the loop changes the native branch layout.
// Model-condition update follows the byte-verified masked-word helper in
// HordeSiegeEngineContainCtor.cpp, with this native bit at Object+0x124.
// Unpack callee has its own checked native pin; other calls use existing rows.
// The record scalar is forwarded unchanged to the existing opaque 3980BF ABI.
#include <ascii_string.h>
class Team;
class PlayerList { public: Player* getNthPlayer(int); };
class ThingTemplate;
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
extern ThingFactory* TheThingFactory;
// Existing verified 8B ASCII-plus-word record view. The source pair's scalar
// identity is unresolved; only the measured layout and copy ABI are used here.
struct BfmeAsciiScalarValue8 {
 AsciiString first;
 int second;
 BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8&);
};
class Rva003980BF { public: void* rva003980BF(void*,int,int); };
class Rva00399959 { public: void unpack(bool); };
class CastleConditionBits {
 unsigned words[20];
public:
 unsigned test(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 void clear(int bit) { words[bit>>5] &= ~(1U<<(bit&31)); }
 void set(int bit) { words[bit>>5] |= 1U<<(bit&31); }
};
struct CastleConditionView { char pad[0x10c]; CastleConditionBits conditions; };
static __forceinline void castleSetCondition(Object* owner,int bit) {
 CastleConditionView* view=(CastleConditionView*)owner;
 if(view->conditions.test(bit)==0) {
  view->conditions.set(bit);
  owner->rva0028AE6D();
 }
}
bool CastleBehavior::checkForInstantUnPack() {
 if(field<bool>(this,0x3c)) {
 Object* owner=field<Object*>(this,8);
 void* data=field<void*>(this,4);
 AsciiString& name=field<AsciiString>(data,0x10);
 Player* player=0;
 if(((StringBase<char>*)&name)->isEmpty()) player=owner->getControllingPlayer();
 else {
  for(int i=0;i<field<int>(ThePlayerList,0x14);++i) {
   Player* candidate=ThePlayerList->getNthPlayer(i);
   if(candidate && ((StringBase<char>*)((char*)candidate+0x4c))->compare(*(const StringBase<char>*)&name)==0) {
    player=candidate;
    break;
   }
  }
 }
 if(player) {
  Team* team=field<Team*>(player,0x2ec);
  if(team) {
   owner->setTeam(team);
   owner->rva0028BAC0();
   owner->rva0028DCC4();
   owner->rva0028D253();
   ((Rva00399959*)this)->unpack(true);
   int count=(field<BfmeAsciiScalarValue8*>(data,0x54)-field<BfmeAsciiScalarValue8*>(data,0x50));
   for(int i=0;i<count;++i) {
    BfmeAsciiScalarValue8 entry(field<BfmeAsciiScalarValue8*>(data,0x50)[i]);
    const ThingTemplate* type=TheThingFactory->findTemplate(entry.first);
    if(type) ((Rva003980BF*)this)->rva003980BF((void*)type,entry.second,1);
   }
  }
 }
 field<bool>(this,0x3c)=false;
 castleSetCondition(owner,218);
 rva00397B03(OBJECT_STATUS_79,false);
 return true;
 }
 return false;
}

// Native 0x003988BF..0x00398BC7,776B; WB 0x00EBEC10 names
// CastleBehavior::teleportStragglersFromWallToGround (CastleSystem.cpp:2477).
// Native vector+0x5C, kind flags60/109, status38 and filter temporaries
// independently establish this target flow. Existing HordeContain slot67
// (rva0046D1F7) supplies the const Object list interface and folded STL pins.
// Native radius is captured by value before linking the temporary filters;
// preserving that accessor semantics reproduces its stack slot and EH state.
// All calls use existing verified rows or previously admitted pins.
#include <list>
class Drawable { public: void rva00274176(bool); void fadeIn(unsigned); };
struct FindPositionOptions {
 FindPositionOptions() { flags=0;minRadius=0;maxRadius=0;startAngle=-99999.9f;maxZDelta=1e10f;ignoreObject=0;sourceToPathToDest=0;relationshipObject=0; }
 unsigned flags; float minRadius,maxRadius,startAngle,maxZDelta;
 const void *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
class Rva000421C8 {
public:
 Rva000421C8():m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask();
 Rva000421C8* link(Rva000421C8*);
 Rva000421C8* m_next;
};
class Rva0026119DFilter:public Rva000421C8 { public: virtual bool allow(Object*); };
class BfmeFixedStorage0004543D {
public: BfmeFixedStorage0004543D(int,int); BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&) throw();
private: unsigned char bytes[28];
};
class Rva0004584D:public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&) throw();
 virtual bool allow(Object*);
 BfmeFixedStorage0004543D m08,m24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];
extern PartitionManager* ThePartitionManager;
class CastleContainListView {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void listObjects(_STL::list<const Object*>&);
};
void CastleBehavior::teleportStragglersFromWallToGround(bool filter) {
 FindPositionOptions options;
 options.flags=0x80;
 Coord3D center;
 Object* owner=field<Object*>(this,8);
 center.x=field<float>(owner,0x38); center.y=field<float>(owner,0x3c); center.z=field<float>(owner,0x40);
 for(unsigned i=0;i<field<_STL::vector<ObjectID> >(this,0x5c).size();++i) {
  Object* wall=TheGameLogic->findObjectByID(field<_STL::vector<ObjectID> >(this,0x5c)[i]);
  if(!wall || !(field<unsigned char>(objectTemplate(wall),0x10f)&0x10)) continue;
  const Coord3D* pos=&field<Coord3D>(wall,0x38);
  Coord3D out; out.x=pos->x;out.y=pos->y;out.z=pos->z;
  BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(pos,wall->getBoundingCircleRadius(),1,
   Rva0004584D(*(const BfmeFixedStorage0004543D*)g_00DFEFA4StoragePrototype,BfmeFixedStorage0004543D(0,2)).link(&Rva0026119DFilter()),0);
  options.startAngle=field<Object*>(this,8)->GetRelativeAngle(pos);
  Object* object;
  while((object=result.next())!=0) {
   if(filter && object->rva0028B511()<17) continue;
   Coord3D delta;
   float distance=field<Object*>(this,8)->getPlanarDirectionTo(&delta,wall)->length();
   if(object->getRelationship(wall)==ENEMIES) { options.minRadius=distance*1.3;options.maxRadius=distance*4.0; }
   else { options.minRadius=distance*0.4f;options.maxRadius=distance*0.8f; }
   if(PartitionManager::findPositionAround(&center,&options,&out)) {
    if(object->testStatus((ObjectStatusTypes)38)) object=object->rva002931F5(false);
    if(object) {
     if(field<unsigned char>(objectTemplate(object),0x115)&0x20) {
      CastleContainListView* contain=(CastleContainListView*)object->rva0028C197();
      if(contain) {
       _STL::list<const Object*> objects;
       contain->listObjects(objects);
       for(_STL::list<const Object*>::iterator it=objects.begin();it!=objects.end();++it) {
        Object* member=const_cast<Object*>(*it);
        member->teleportTo(&out,false);
        if(member->getDrawable()) member->getDrawable()->fadeIn(10);
       }
      }
     }
     object->teleportTo(&out,false);
     if(object->getDrawable()) object->getDrawable()->fadeIn(10);
    }
   }
  }
 }
}

// WB 0x00EB85E0 names CastleBehavior::unpack; native00399959..00399C6C,
// 787B. Keep the previously admitted address-derived receiver spelling.
// Player+0x3BC is an unresolved build-control object; the existing W3DBridge
// setter supplies its measured +0x110 bool ABI, not a claim of bridge identity.
// Its typed nested layout preserves the native LEA and flag-load ordering.
// Native helper3993F2 has an independently admitted136B boundary/call pin.
// Rehome the already-matched34B height helper here: its visible noinline body
// lets MSVC preserve EDX across the native call, as retail does. Its own bytes
// remain exact; this move adds no recovered bytes.
class W3DBridge { char pad[0x110]; bool enabled; public: void setEnabled(bool); bool isEnabled() const { return enabled; } };
class Player { char pad[0x3bc]; W3DBridge buildControl; public: W3DBridge* getBuildControl() { return &buildControl; } };
class Rva00395A60 { public: __declspec(noinline) float rva00395A60(); };
float Rva00395A60::rva00395A60() { float value=0.0f; void* data=field<void*>(this,4); if(data) value=field<float>(data,0x2c);return value; }
class TerrainLogic { public: void rva00283262(const Coord3D*,float); };
extern TerrainLogic* TheTerrainLogic;
class ScriptEngine { public: void rva00357960(const AsciiString&,Object*); };
extern void* g_00DFEFF0;
extern "C" int __cdecl fprintf(void*,const char*,...);
static __forceinline void castleUnpackedConditions(Object* owner) {
 CastleConditionView* view=(CastleConditionView*)owner;
 if(view->conditions.test(94)!=0 || view->conditions.test(96)==0) {
  view->conditions.clear(94); view->conditions.set(96); owner->rva0028AE6D();
 }
}
void Rva00399959::unpack(bool instant) {
 Object* owner=field<Object*>(this,8);
 if(owner) {
  field<Pathfinder*>(TheAI,0x10)->RemoveObjectFromPathfindMap(owner);
  field<void*>(this,0x9c)=((CastleBehavior*)this)->GetArmyIDFromClosestObject();
  field<bool>(this,0x44)=false;
  AsciiString& name=field<AsciiString>(this,0x98);
  if(!((StringBase<char>*)&name)->isEmpty()) {
   const ThingTemplate* type=TheThingFactory->findTemplate(name);
   if(type) ((CastleBehavior*)this)->createOwnedObject((void*)type);
   name.setCopyInline(AsciiString::TheEmptyString);
  } else {
   W3DBridge* buildControl=owner->getControllingPlayer()->getBuildControl();
   bool old=buildControl->isEnabled();
   if(field<int>(owner,0x78)==0) buildControl->setEnabled(false);
   ((CastleBehavior*)this)->rva003993F2(instant);
   buildControl->setEnabled(old);
   ((CastleBehavior*)this)->rva00399370();
  }
  if(TheTerrainLogic) TheTerrainLogic->rva00283262(&field<Coord3D>(owner,0x38),((Rva00395A60*)this)->rva00395A60());
  Rva00396BC5SetCastleId(&field<_STL::vector<ObjectID> >(this,0x50),field<ObjectID>(this,0x38));
  Rva00396BC5SetCastleId(&field<_STL::vector<ObjectID> >(this,0x5c),field<ObjectID>(this,0x38));
  Rva00396BC5SetCastleId(&field<_STL::vector<ObjectID> >(this,0x74),field<ObjectID>(this,0x38));
  field<unsigned>(this,0x48)=TheGameLogic->getFrame();
  for(_STL::vector<ObjectID>::iterator it=field<_STL::vector<ObjectID> >(this,0x50).begin();it!=field<_STL::vector<ObjectID> >(this,0x50).end();++it) {
   Object* object=TheGameLogic->findObjectByID(*it);
   if(object) {
    static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
    Module* module=object->findModule(key);
    if(module) { field<ObjectID>(module,0x14)=field<ObjectID>(this,0x38);field<ObjectID>(module,0x18)=objectID(field<Object*>(this,8)); }
   }
  }
  for(_STL::vector<ObjectID>::iterator it=field<_STL::vector<ObjectID> >(this,0x74).begin();it!=field<_STL::vector<ObjectID> >(this,0x74).end();++it) {
   Object* object=TheGameLogic->findObjectByID(*it);
   if(object) {
    static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
    Module* module=object->findModule(key);
    if(module) { field<ObjectID>(module,0x14)=field<ObjectID>(this,0x38);field<ObjectID>(module,0x18)=objectID(field<Object*>(this,8)); }
   }
  }
  castleUnpackedConditions(owner);
  owner->setStatus((ObjectStatusTypes)3,true);
  owner->getDrawable()->rva00274176(false);
  ((CastleBehavior*)this)->rva0039792B();
  if(field<int>(TheGameLogic,0x1b4)>0 && g_00DFEFF0) {
   fprintf(g_00DFEFF0,"CAMP: Frame %d: Castle %s(%d) ::unpack() called by %s",TheGameLogic->getFrame(),field<AsciiString>(objectTemplate(owner),0x64).str(),objectID(owner),field<AsciiString>(owner->getControllingPlayer(),0x4c).str());
  }
  Object* pending=TheGameLogic->findObjectByID(field<ObjectID>(this,0x38));
  if(pending && field<Object*>(this,8)) {
   Object* currentOwner=field<Object*>(this,8);
   field<float>(pending,0x324)=(float)(int)currentOwner->getCastleValue();
   TheScriptEngine->rva00357960(field<AsciiString>(currentOwner,0x88),pending);
   field<AsciiString>(currentOwner,0x88).setCopyInline(AsciiString("No Name"));
  }
 }
}

// Native003993F2..0039947A,136B; WB00EB9220 unnamed CastleSystem helper.
// The WB loop increments the index in the lookup condition, then builds and
// registers each returned entry. Native BuildListInfo occupies128B with the
// existing protected virtual destructor. Only its storage extent is needed.
// Construction identity/ABI is independently witnessed at WB00EBC8C0 and the
// complete native1041B callee; that body remains a banked partial, not recovery.
class BuildListInfo {
public: BuildListInfo();
protected: virtual ~BuildListInfo(); friend class CastleBehavior;
private: unsigned char storage[124];
};
class SidesList { public: bool rva0032BD25(NameKeyType,int,BuildListInfo*); };
extern SidesList* TheSidesList;
class Rva00396B0D { public: int rva00396B0D(); };
void CastleBehavior::rva003993F2(bool instant) {
 NameKeyType key=(NameKeyType)((Rva00396B0D*)this)->rva00396B0D();
 int index=0;
 BuildListInfo info;
 while(TheSidesList->rva0032BD25(key,index++,&info)) registerOwnedObject(buildCastleStructure(&info,instant));
}

// Native 00399C6C..00399D54 (232B), WB 00EB9B60. The native trace
// names initiateUnpack; the BFME 1 ba7ddda7 donor at
// game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorInitiateUnpack.cpp
// supplies the const template signature and transition purpose. Target bytes
// establish the ASCII name at +98, state at +34, condition bit 218 and
// type-dependent payment helpers; those differ from the donor layout/flow.
// Calls retain the already-rowed address-derived provider identities.
class Rva0039561F { public: int rva0039561F(ThingTemplate*); };
class Rva00396B25 { public: void rva00396B25(); };
class Rva00395CEB { public: void rva0039611E(); };
void CastleBehavior::initiateUnpack(bool instant,const ThingTemplate* type) {
 Object* owner=field<Object*>(this,8);
 if(type) field<AsciiString>(this,0x98).set(field<AsciiString>((void*)type,0x64));
 field<float>(this,0x4c)=0.0f;
 if(instant) {
  ((Rva00399959*)this)->unpack(true);
  castleSetCondition(owner,218);
  field<int>(this,0x34)=4;
 } else {
  field<int>(this,0x34)=1;
  if(type) ((Rva0039561F*)this)->rva0039561F((ThingTemplate*)type);
  else ((Rva00396B25*)this)->rva00396B25();
 }
 ((Rva00395CEB*)((char*)this+0xa0))->rva0039611E();
 if(field<int>(TheGameLogic,0x1b4)>0 && g_00DFEFF0) {
  fprintf(g_00DFEFF0,"CAMP: Frame %d: Castle %s(%d) ::initiateUnpack() called by %s",TheGameLogic->getFrame(),field<AsciiString>(objectTemplate(owner),0x64).str(),objectID(owner),field<AsciiString>(owner->getControllingPlayer(),0x4c).str());
 }
}
