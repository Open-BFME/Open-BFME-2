// ?buildCastleStructure@CastleBehavior@@QAEPAVObject@@PAVBuildListInfo@@_N@Z
// partial score=0.85 date=2026-10-08
// Native 00396311..00396722, 1041B; WB ebc8c0 names CastleBehavior::buildCastleStructure.
// Semantic matrix lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f WWMath matrix3d.h Transform_Vector.
// Trial emits1036B; by-value angle access and a sequential += recover the native SSE spill. Stack A0 vs retail A4 and type/created register lifetimes remain.
// All direct callees resolved after the separately verified 3955AF return/receiver ABI correction.
// No production construction body or ledger row has been added. Damage field names beyond established source/type/death/amount remain opaque.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
#include <ascii_string.h>
#include <math.h>
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix3d.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }
class BuildListInfo { public: float angle() const { return *(const float*)((const char*)this+0x20); } AsciiString rva000AF1DD() const; };
class ThingTemplate;
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
extern ThingFactory* TheThingFactory;
class Player;
class PlayerList;
extern PlayerList* ThePlayerList;
class Rva2225E0Filter { public: bool rva003618B9(const ThingTemplate*,Player*,Player*); };
enum ObjectStatusTypes { STATUS5=5 };
enum ModelConditionFlagType { CONDITION218=218 };
class Drawable { public: void fadeIn(unsigned); void rva00274176(bool); };
class ExitInterface {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6();
 virtual void slot7(const Coord3D*);
 virtual void slot8(); virtual bool slot9(Coord3D*,bool);
};
class CastleBodyView;
class Object { public: CastleBodyView* body() const { return *(CastleBodyView*const*)((const char*)this+0x254); } float orientation() const { return *(const float*)((const char*)this+0x44); }
 Player* getControllingPlayer() const;
 Drawable* getDrawable() const;
 void setSpecialModelConditionState(ModelConditionFlagType,unsigned);
 void setStatus(ObjectStatusTypes,bool);
 ExitInterface* getObjectExitInterface() const;
};
class Rva0028CBFD { public: void rva0028CBFD(); };
class DamageInfo { public: DamageInfo(); char prefix[8]; int sourceID; int unknownC; int damageType; int unknown14; int unknown18; int deathType; float amount; int unknown24; float unknown28; char tail[0x50]; };
class CastleBodyView {
public:
 virtual void damage(DamageInfo*); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4();
 virtual float fraction(); virtual float maximum();
};
class CastleFactoryView {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual Object* create(Object*,const ThingTemplate*,const Coord3D*,float,Player*,bool);
};
class GameLogic;
extern GameLogic* TheGameLogic;
class GlobalData;
extern GlobalData* TheWritableGlobalData;
class ScriptEngine { public:
 void AppendDebugMessage(const AsciiString&,bool);
 void addObjectToCache(Object*,const AsciiString&);
};
extern ScriptEngine* TheScriptEngine;
extern int g_009BA4E8;
float normalizeAngle(float);
class Rva003955AFData { public: int query(int,int,float,int,int); };
class CastleBehavior { public: Object* getOwner() const { return *(Object*const*)((const char*)this+8); } Object* buildCastleStructure(BuildListInfo*,bool); };
Object* CastleBehavior::buildCastleStructure(BuildListInfo* record,bool instant) {
 Object* created=0;
 void* data=field<void*>(this,4);
 AsciiString name=record->rva000AF1DD();
 if(name.isEmpty()) return created;
 const ThingTemplate* type=TheThingFactory->findTemplate(name);
 if(!type) return 0;
 if(field<unsigned char>((void*)type,0x114)&0x10) return 0;
 if(field<unsigned char>((void*)type,0x10f)&0x10) field<bool>(this,0x44)=true;
 Player* player=getOwner()->getControllingPlayer();
 if(!((Rva2225E0Filter*)((char*)data+0x30))->rva003618B9(type,0,0)) player=field<Player*>(ThePlayerList,0x18);
 if(!player) return 0;
 Object* owner=getOwner();
 Vector3 p(field<float>(record,0xc),field<float>(record,0x10),field<float>(record,0x14));
 Matrix3D::Transform_Vector(field<Matrix3D>(owner,8),p,&p);
 Coord3D pos;
 pos.x=p.X; pos.y=p.Y; pos.z=p.Z;
 float angle=owner->orientation(); angle+=record->angle();
 angle=normalizeAngle(angle);
 if(!(field<unsigned char>((void*)type,0x10a)&2) && field<Rva003955AFData*>(this,4)->query((int)&pos,(int)type,angle,5,(int)getOwner())) return 0;
 created=((CastleFactoryView*)((char*)this+0x20))->create(getOwner(),type,&pos,angle,player,instant);
 if(created) {
  if((field<unsigned char>((void*)type,0x10a)&2) && field<bool>(data,0x75) && getOwner()) {
   CastleBodyView* from=getOwner()->body();
   CastleBodyView* to=created->body();
   if(from && to) {
    DamageInfo damage;
    float fraction=from->fraction();
    damage.sourceID=0;
    damage.amount=(1.0f-fraction)*to->maximum();
    damage.unknown14=29;
    damage.damageType=8;
    damage.deathType=0;
    damage.unknown28=2.0f;
    to->damage(&damage);
   }
  }
  field<unsigned>(record,0x48)=field<unsigned>(created,0x74);
  field<unsigned>(record,0x4c)=field<unsigned>(TheGameLogic,0x40)+1;
  if(field<int>(TheWritableGlobalData,0x9b8)) {
   AsciiString message;
   message+=name;
   message+=" - Building completed.";
   TheScriptEngine->AppendDebugMessage(name,false);
  }
  TheScriptEngine->addObjectToCache(created,AsciiString(""));
  if(!instant) {
   float duration=field<float>(field<void*>(this,4),0x1c);
   unsigned frames=(unsigned)(int)(duration*g_009BA4E8);
   created->getDrawable()->fadeIn(frames);
   created->setSpecialModelConditionState(CONDITION218,frames);
   created->setStatus(STATUS5,true);
   created->getDrawable()->rva00274176(false);
  }
  ExitInterface* exit=created->getObjectExitInterface();
  if(exit) {
   bool hasOffset=false;
   if(fabs(field<float>(record,0x18))>1.0 || fabs(field<float>(record,0x1c))>1.0) hasOffset=true;
   Coord3D rally;
   if(!exit->slot9(&rally,true)) rally=field<Coord3D>(record,0xc);
   if(hasOffset) {
    rally.x+=field<float>(record,0x18);
    rally.y+=field<float>(record,0x1c);
    exit->slot7(&rally);
   }
  }
  if(instant) ((Rva0028CBFD*)created)->rva0028CBFD();
 }
 return created;
}
