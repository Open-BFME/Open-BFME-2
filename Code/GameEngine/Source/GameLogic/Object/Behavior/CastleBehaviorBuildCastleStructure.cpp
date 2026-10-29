// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// CastleBehavior::buildCastleStructure, native 0x00396311..0x00396722 (1041B);
// WB 0xEBC8C0 names it. Its three KindOf checks go through BitFlags<218>::test
// on the template flags at +0x108 (bits 100/60/17, opaque names here) as in WB;
// the word-read/mask spelling is what gives retail's type spill and 0xA4 frame.
// Matrix lead: Open-BFME-1 ba7ddda7 WWMath matrix3d.h Transform_Vector.
// Damage field names beyond source/type/death/amount remain opaque.
// stlport
#include <ascii_string.h>
#include <math.h>
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix3d.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
template<class T> inline T& field(void* p,int n) { return *(T*)((char*)p+n); }
class BuildListInfo { public: float angle() const { return *(const float*)((const char*)this+0x20); } AsciiString getTemplateName() const; };
// KindOf bits (opaque names; numbered as retail tests them): WB EBC8C0 calls
// BitFlags<218,KindOfType>::test(type+0x108, 100 / 60 / 17) for all three.
enum KindOfType { KINDOF_17=17, KINDOF_60=60, KINDOF_100=100 };
template<int NUMBITS> class BitFlags { public: unsigned long m_words[(NUMBITS+31)/32];
 __forceinline bool test(size_t pos) const { return (m_words[pos/32] & (1UL<<(pos%32)))!=0; } };
class ThingTemplate { public: char pad[0x108]; BitFlags<218> m_kindof;
 __declspec(dllimport) __forceinline bool isKindOf(KindOfType t) const { return m_kindof.test(t); } };
class ThingFactory
{
public:
	const ThingTemplate* findTemplate(const AsciiString&);
};
extern ThingFactory* TheThingFactory;
class Player;
class PlayerList;
extern PlayerList* ThePlayerList;
class ObjectFilter { public: bool testTemplate(const ThingTemplate*,const Player*,const Player*); };
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
// Retail builds it through the rowed initializer Rva00263895Member
// (Rva00263895Init.cpp); the inline forwarder binds the call there.
class Rva00263895Member
{
public:
	Rva00263895Member();	// 0x00263895
};
class DamageInfo { public: __declspec(dllimport) __forceinline DamageInfo() { ((Rva00263895Member *)this)->Rva00263895Member::Rva00263895Member(); } char prefix[8]; int sourceID; int unknownC; int damageType; int unknown14; int unknown18; int deathType; float amount; int unknown24; float unknown28; char tail[0x50]; };
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
extern int BfmeClientFramesPerSecond;
float normalizeAngle(float);
class Rva003955AFData { public: int query(int,int,float,int,int); };
struct CastleBehaviorModuleData { char pad[0x30]; ObjectFilter m_filter; char p2[0x44]; bool m_flag75; };
class CastleBehavior { public: Object* getOwner() const { return *(Object*const*)((const char*)this+8); }
 void* getData() const { return *(void*const*)((const char*)this+4); } Object* buildCastleStructure(BuildListInfo*,bool); };
Object* CastleBehavior::buildCastleStructure(BuildListInfo* record,bool instant) {
 Object* created=0;
 CastleBehaviorModuleData* data=field<CastleBehaviorModuleData*>(this,4);
 AsciiString name=record->getTemplateName();
 if(name.isEmpty()) return created;
 const ThingTemplate* type=TheThingFactory->findTemplate(name);
 if(!type) return 0;
 if(type->isKindOf(KINDOF_100)) return 0;
 if(type->isKindOf(KINDOF_60)) field<bool>(this,0x44)=true;
 Player* player=getOwner()->getControllingPlayer();
 if(!data->m_filter.testTemplate(type,0,0)) player=field<Player*>(ThePlayerList,0x18);
 if(!player) return 0;
 Object* owner=getOwner();
 Vector3 p(field<float>(record,0xc),field<float>(record,0x10),field<float>(record,0x14));
 Matrix3D::Transform_Vector(field<Matrix3D>(owner,8),p,&p);
 Coord3D pos;
 pos.x=p.X; pos.y=p.Y; pos.z=p.Z;
 float angle=owner->orientation(); angle+=record->angle();
 angle=normalizeAngle(angle);
 if(!type->isKindOf(KINDOF_17) && ((Rva003955AFData*)getData())->query((int)&pos,(int)type,angle,5,(int)getOwner())) return 0;
 created=((CastleFactoryView*)((char*)this+0x20))->create(getOwner(),type,&pos,angle,player,instant);
 if(created) {
  if(type->isKindOf(KINDOF_17) && data->m_flag75 && getOwner()) {
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
   float duration=field<float>(getData(),0x1c);
   unsigned frames=(unsigned)(int)(duration*BfmeClientFramesPerSecond);
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
