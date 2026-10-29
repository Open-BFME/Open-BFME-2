// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// Split from CastleBehaviorRegisterOwnedObject.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <map>
// Keep the map<int,int> iterator step inline-only; retail's out-of-line copy
// lives in stlport_map_int_int.cpp (0x169ED0).
namespace _STL { template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++() { _M_node = _Rb_global_inst::_M_increment(_M_node); return *this; } }

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Xfer;
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../Common/GameLogicObjectLookupView.h"
// erase and push_back are called out of line: bind them to retail's copies (erase is
// rowed in DockUpdateCtor.cpp) instead of emitting this unit's __false_type copies.
namespace _STL { template <> ObjectID *vector<ObjectID, allocator<ObjectID> >::erase(ObjectID *, ObjectID *); }
namespace _STL { template <> void vector<ObjectID, allocator<ObjectID> >::push_back(const ObjectID &); }
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
 friend class Rva00399959; char native04[0x2c]; };
template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }
inline void* objectTemplate(Object* object) { return field<void*>(object,4); }
inline ObjectID objectID(Object* object) { return field<ObjectID>(object,0x74); }
class BuildListInfo;
class ThingTemplate;
class PolygonTrigger;
class CastleBehaviorInterface {
public:
 virtual void slot0()=0;
 virtual void rva00395DAC()=0;
 virtual void slot2()=0;
 virtual bool slot3()=0;
};
class CastleBehavior : public FoundationAIUpdate, public CastleBehaviorInterface { public: virtual void rva00395DAC(); void rva0039865E(PolygonTrigger*); Object* buildCastleStructure(BuildListInfo*,bool); void* GetArmyIDFromClosestObject(); Object* createOwnedObject(void*); void rva003993F2(bool); void teleportStragglersFromWallToGround(bool); void registerOwnedObject(Object*); bool checkForAutoPack(); bool checkForInstantUnPack(); void rva00397B03(ObjectStatusTypes,bool); virtual void DoXfer(Xfer*); void rva00399370(); void rva0039792B(); void initiateUnpack(bool,const ThingTemplate*); };
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

int Rva00395AD2Destroy(Object* object,int context);

// Native cdecl callback VA795A9F..795AD2 (51B), embedded at 0x0039762F.
// The template flag redirects the kill to the module slot-6 object; retail
// assumes the module exists on that path. Callback context is unused.
class Rva00395A9FInterface {
public:
 virtual void unused0(); virtual void unused1(); virtual void unused2();
 virtual void unused3(); virtual void unused4(); virtual void unused5();
 virtual Object* getObject();
};
int Rva00395A9FKill(Object* object,int context);

// CastleBehavior::checkForAutoPack, native RVA003975B7, 415 bytes.
// Semantic donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00371B00.cpp.
// Native layouts, timer scale, disposal flag and callbacks verified independently.
class GlobalData { public: char pad[0x110c]; float secondsBeforeBaseCheckActive; };
extern GlobalData* TheWritableGlobalData;
extern int BfmeLogicFramesPerSecond;
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

// Native RVA00397B03, 134 bytes; called by checkForInstantUnPack with (79,false).
// Semantic donor ba7ddda7 CastleBehaviorRva00371EE0StatusBit.cpp, adapted to
// native pending ID +0x38 and vector +0x5C with the rowed Object status setter.
// WB leaves the method unnamed, so retain an address-derived identity.
class ScriptEngine;
extern ScriptEngine* TheScriptEngine;
class Rva002039B6Host { public: void rva002039B6(); };

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
 ~Rva00395561();
};
class Rva0039585A { public: void mapLoadPostProcess(int context); };

// CastleBehavior::DoXfer: WB named identity and native630B boundary.
// Existing vector<ScienceType> serialization provider is a measured 4-byte
// ABI view: these caller fields contain ObjectIDs, not established sciences.
// Field +0x98 is AsciiString, independently witnessed by unpack.
// One shared ObjectID temporary preserves native stack-slot reuse.
class AsciiString;
struct CastleXferVersion { unsigned char first,second; CastleXferVersion(unsigned char a,unsigned char b):first(a),second(b){} };
class Snapshot;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"
enum ScienceType { SCIENCE_0=0 };
Xfer* Rva00398280Xfer(Xfer*,_STL::vector<ScienceType>*);
void XferObjectID(Xfer*,ObjectID*);
void XferLivingWorldArmyID(Xfer*,int*);
void CastleBehavior::DoXfer(Xfer* xfer) {
 CastleXferVersion version(1,2);
 ObjectID id;
 *xfer == (Xfer::Version &)version;
 xfer->XferRawBytes(&field<int>(this,0x34),4);
 XferObjectID(xfer,&field<ObjectID>(this,0x38));
 *xfer == field<bool>(this,0x3c);
 *xfer == field<bool>(this,0x3d);
 *xfer == field<float>(this,0x40);
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x50));
 XferLivingWorldArmyID(xfer,&field<int>(this,0x9c));
 unsigned countA=field<_STL::vector<ObjectID> >(this,0x50).size();
 *xfer == (int&)countA;
 if(xfer->IsStoring()) {
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
 *xfer == (int&)countB;
 if(xfer->IsStoring()) {
  for(_STL::vector<ObjectID>::iterator it=field<_STL::vector<ObjectID> >(this,0x5c).begin();it!=field<_STL::vector<ObjectID> >(this,0x5c).end();++it) {
   id=*it; XferObjectID(xfer,&id);
  }
 } else {
  for(unsigned i=0;i<countB;++i) { XferObjectID(xfer,&id); field<_STL::vector<ObjectID> >(this,0x5c).push_back(id); }
 }
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x68));
 *xfer == field<unsigned>(this,0x48);
 if(version.second>=2) *xfer == field<bool>(this,0x44);
 if(xfer->IsLoading() && field<int>(this,0x34)!=0) rva00399370();
 ((FoundationAIUpdate*)this)->FoundationAIUpdate::xfer(xfer);
 Rva00398280Xfer(xfer,&field<_STL::vector<ScienceType> >(this,0x74));
 *xfer == field<AsciiString>(this,0x98);
 if(xfer->IsStoring()) {
  unsigned count=field<_STL::map<int,int> >(this,0xa0).size();
  *xfer == (int&)count;
  for(_STL::map<int,int>::iterator it=field<_STL::map<int,int> >(this,0xa0).begin();it!=field<_STL::map<int,int> >(this,0xa0).end();++it) {
   int key=it->first; *xfer == key;
   unsigned value=it->second; *xfer == value;
  }
 } else {
  unsigned count;
  *xfer == (int&)count;
  while(count) {
   int key; unsigned value;
   *xfer == key; *xfer == value;
   field<_STL::map<int,int> >(this,0xa0).insert(_STL::pair<const int,int>(key,value));
   --count;
  }
 }
}

void Rva00396BC5SetCastleId(_STL::vector<ObjectID>* ids,ObjectID id);

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
// The dtor's out-of-line copy (the unwind funclet's call) expands ~AsciiString into the
// releaseBuffer tail jump, retail's 0x0048BA39 shape and the copy the link keeps first.
struct BfmeAsciiScalarValue8 {
 AsciiString first;
 int second;
 BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8&);
 ~BfmeAsciiScalarValue8() {}
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
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@IAEXPAW4Ob:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ObjectID;
namespace _STL { template <> void vector<ObjectID, allocator<ObjectID> >::_M_insert_overflow(ObjectID *, const ObjectID &, const __false_type &, size_t, bool); }

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
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
struct Rva00045411BitSet { unsigned m_bits[7]; Rva00045411BitSet(int,int); };
class BfmeFixedStorage0004543D {
public: BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&) throw();
private: unsigned char bytes[28];
};
class Rva0004584D:public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&) throw();
 virtual bool allow(Object*);
 BfmeFixedStorage0004543D m08,m24;
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
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
class TerrainLogic { public: void rva00283262(const Coord3D*,float); };
extern TerrainLogic* TheTerrainLogic;
#include "../../../Include/GameLogic/ScriptEngine.h"
static __forceinline void castleUnpackedConditions(Object* owner) {
 CastleConditionView* view=(CastleConditionView*)owner;
 if(view->conditions.test(94)!=0 || view->conditions.test(96)==0) {
  view->conditions.clear(94); view->conditions.set(96); owner->rva0028AE6D();
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
// The rowed lookups (SidesListCastleBuildLists.cpp) take an int key and a PolygonalArea.
class PolygonalArea;
class SidesList { public: bool rva0032BD64(int,int,PolygonalArea*); bool rva0032BD25(int,int,BuildListInfo*); };
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

// Native00399370..003993F2,130B; WB00EB9110 unnamed CastleSystem helper.
// Native allocates100B PolygonTrigger with explicit initialAllocation1 and
// MSVC's hidden virtual-base-construction flag. The virtual interface below
// is independently recovered in Rva00330C50Ctor.cpp. This is the complete
// caller storage extent with an opaque92B nonvirtual prefix, not a claim that
// PolygonTrigger's other native bases or fields have been reconciled here.
// The native release path calls slot0(flags0), then deletes its returned
// allocation pointer; a null polygon still reaches operator delete(nullptr).
// Constructor, indexed loader and registration calls have checked native pins.
class Rva00330C50Interface {
public:
 ~Rva00330C50Interface() {}
 virtual void slot0()=0; virtual void slot1()=0; virtual void slot2()=0;
 virtual void slot3()=0; virtual void slot4()=0; virtual void slot5()=0; virtual void slot6()=0;
};
class PolygonTrigger:public virtual Rva00330C50Interface {
public:
 PolygonTrigger(int initialAllocation);
 static void addPolygonTrigger(PolygonTrigger*);
 virtual void* deleteInstance(int);
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
private: char nativePrefix[0x54];
};
typedef char PolygonTriggerExtentCheck[sizeof(PolygonTrigger)==100?1:-1];
void CastleBehavior::rva00399370() {
 NameKeyType key=(NameKeyType)((Rva00396B0D*)this)->rva00396B0D();
 int index=0;
 PolygonTrigger* polygon;
 for(;;) {
  polygon=new PolygonTrigger(1);
  if(!TheSidesList->rva0032BD64(key,index,(PolygonalArea*)polygon)) break;
  rva0039865E(polygon);
  ++index;
 }
 ::operator delete(polygon?polygon->deleteInstance(0):0);
}
