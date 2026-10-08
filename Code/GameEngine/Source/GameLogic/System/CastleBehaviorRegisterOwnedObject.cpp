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
class CastleBehavior { public: void registerOwnedObject(Object*); };
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
