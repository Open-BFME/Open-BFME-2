// ?rva00296065@Object@@QAEXPAURva00297612Entry@@@Z
// partial score=0.8887731533183905 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /Ireference/shims/bfme2_ascii
// Native296065..29660A RET4; native frameC8 and EBXowner/ESIentry/EDIvector allocation restored by cached vector pointer and scalar component copy.
// Scorer uses read-only candidate contracts for unrowed3909FA/294D61/27B18C; no pins written.
// Native296065..29660A RET4; owned queued caller2975AC supplies Rva00297612Entry.
// ZH Object::attemptDamage shockwave section primary guide; target audio/airborne/recoil/AI feedback extensions follow native and WB CC92C0 Object.cpp.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/RTS/XYDistanceCallView.h"
class Rva0036CA00Str {public:__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str&);__forceinline ~Rva0036CA00Str(){if(ref)ref->Release_Ref();} OpaqueRefCounted*ref;};
class Rva002390CB {public:Rva002390CB(const Rva002390CB&);__forceinline ~Rva002390CB(){if(name.referent)name.referent->Release_Ref();}int index;OpaqueRefElement4 name;__forceinline const Rva0036CA00Str&getSound()const{return *(const Rva0036CA00Str*)&name;}};
struct Rva00297612Entry {char pad0[0x2c];int visualState;ObjectID source;Coord3D vector;float amount,radius,taper,up;bool radial;char pad51[3];float extraDistance,secondary;Coord3D origin;float mode;};
class Drawable {public:Rva002390CB rva0028F8F9();Rva002390CB rva0028F8E0();void rva0027B18C(Rva00297612Entry*);};
class Rva002D9531 {public:void rva002D9531(int);};
template<int N>class ShockSlots:public ShockSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class ShockSlots<0>{};
class AudioManager:public ShockSlots<25>{public:virtual void addAudioEvent(BfmeAudioEventPrefix136*)=0;};extern AudioManager*TheAudio;
class PhysicsBehavior {public:void rva003906BF();void rva00390557(const Coord3D*,float,float,int,int);void rva003909FA(const Coord3D*,int,int);void rva00390629(bool);char pad0[0x5c];bool flag5c;};
class AttributeModifierPoolUpdate {public:bool rva00403382(int,float*,int);};
struct ShockBodyEntry {char pad0[8];ObjectID source;};
class BodyModule:public ShockSlots<15>{public:virtual ShockBodyEntry*slot15()=0;};
class AIUpdateInterface:public ShockSlots<153>{public:virtual void slot153()=0;int getCurrentStateID() const;};
enum PathfindLayerEnum{LAYER_UNKNOWN0=0};
class TerrainLogic:public ShockSlots<7>{public:virtual float getLayerHeight(float,float,int,int*,bool)=0;PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};extern TerrainLogic*TheTerrainLogic;
class ThingTemplate {public:char pad0[0x11c];unsigned kinds;};
class Rva001E438B {public:float*rva00261988(float*,Rva001E438B*);};
enum DamageType{DAMAGE_UNKNOWN8=8};enum DeathType{DEATH_UNKNOWN0=0};
class ShockFlags {public:unsigned words[19];unsigned test(int bit)const{return words[bit>>5]&(1u<<(bit&31));}void SetBit(int bit){words[bit>>5]|=1u<<(bit&31);}};
class Object {public:void rva00296065(Rva00297612Entry*);void rva0028AE9B(int);bool rva0028DB0F(bool)const; PhysicsBehavior*getPhysics()const{return physics;} Drawable *getDrawable()const{return drawable;}private:AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;public:void rva0028AE6D();void scoreTheKill(Object*,bool);void kill(DamageType,DeathType);
 char pad0[4];ThingTemplate*templ;char pad8[0x38-8];Coord3D position;char pad44[0x74-0x44];ObjectID id;char pad78[0x84-0x78];Drawable*drawable;char pad88[0x10c-0x88];ShockFlags flags;char pad158[0x254-0x158];BodyModule*body;AIUpdateInterface*ai;PhysicsBehavior*physics;char pad260[0x438-0x260];unsigned char status;
 __forceinline unsigned getCondition(int bit)const{return flags.test(bit);}__forceinline void setCondition(int bit){flags.SetBit(bit);rva0028AE6D();}
};
extern GameLogic*TheGameLogic;
float GetGameLogicRandomValueReal(float,float,char*,int);
static inline const float&shockMin(const float&a,const float&b){return a<b?a:b;}static inline const float&shockMax(const float&a,const float&b){return a>b?a:b;}
static const char shockFile[]="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Object.cpp";
void Object::rva00296065(Rva00297612Entry*entry){
 rva0028AE9B(0);Drawable*draw=getDrawable();
 if(entry->amount>0.0f&&entry->radius>0.0f){
  PhysicsBehavior*behavior=getPhysics();bool force=entry->mode!=0.0f;bool blocked=behavior?behavior->flag5c:false;
  if(!behavior||(blocked&&!force))goto end;
  if(draw&&!blocked){Rva0036CA00Str sound((force?draw->rva0028F8F9():draw->rva0028F8E0()).getSound());BfmeAudioEventPrefix136 event(*(OpaqueRefElement4*)&sound,0);((Rva002D9531*)&event)->rva002D9531(id);TheAudio->addAudioEvent(&event);}
  if(rva0028DB0F(force)){behavior->rva003906BF();goto end;}
  float resistance;AttributeModifierPoolUpdate*pool=findAttributeModifierPoolUpdate();if(pool)pool->rva00403382(10,&resistance,0);if(resistance>=1.0f)return;
  const Coord3D *shockVector=&entry->vector;float distance=shockVector->length();float percent=shockMin(1.0f,distance/entry->radius);
  float random=GetGameLogicRandomValueReal(0.85f,1.15f,(char*)shockFile,4093);
  if(entry->radial){float extra=shockMax(0.0f,entry->extraDistance);Coord3D destination;destination.x=shockVector->x;destination.y=shockVector->y;destination.z=0.0f;destination.normalize();float scale=entry->radius+(entry->radius*extra*random*percent);destination.x*=scale;destination.y*=scale;destination.z*=scale;destination.x+=entry->origin.x;destination.y+=entry->origin.y;destination.z+=entry->origin.z;destination.z=TheTerrainLogic->getLayerHeight(destination.x,destination.y,TheTerrainLogic->getLayerForDestination(0,&destination),0,true);behavior->rva00390557(&destination,entry->secondary*random,entry->amount,0,0);}
  else{float taper=1.0f-percent*(1.0f-entry->taper);Coord3D forceVector;forceVector.x=shockVector->x;forceVector.y=shockVector->y;forceVector.z=shockVector->z;forceVector.normalize();
   if(!force){float scale=entry->amount*taper*random;forceVector.x*=scale;forceVector.y*=scale;forceVector.z*=scale;forceVector.z=forceVector.length()*entry->up*random;}
   else{Object*source=TheGameLogic->findObjectByID(entry->source);if(source&&entry->radius>0.0f){float relative[3];float*point=((Rva001E438B*)this)->rva00261988(relative,(Rva001E438B*)source);float negativeHeight=point[2]*-1.0f;float factor=1.0f-negativeHeight/entry->radius;float scale=entry->amount*factor*taper*random;random=GetGameLogicRandomValueReal(0.65f,1.35f,(char*)shockFile,4169);if(factor<0.0f)scale*=2.0f;forceVector.x*=scale;forceVector.y*=scale;forceVector.z*=scale;float r=entry->radius;forceVector.z=(1.0f-((Rva000CBA20*)this)->distSq((Rva000CBA20Point*)&source->position)/(r*r))*0.5f*entry->amount*random;}}
   if(templ->kinds&0x80000000){if(forceVector.z>0.0f)forceVector.z=-forceVector.z;}else{if(forceVector.z<0.0f)forceVector.z=-forceVector.z;}behavior->rva003909FA(&forceVector,0,0);
  }
  if(!getCondition(127))setCondition(127);behavior->rva00390629(true);
  if(ai&&ai->getCurrentStateID()==45){ShockBodyEntry*data=body->slot15();Object*source=TheGameLogic->findObjectByID(data?body->slot15()->source:INVALID_OBJECT_ID);if(source&&!(status&1))source->scoreTheKill(this,true);kill(DAMAGE_UNKNOWN8,DEATH_UNKNOWN0);kill(DAMAGE_UNKNOWN8,DEATH_UNKNOWN0);}
  if(ai)ai->slot153();rva0028AE9B(entry->visualState);
 }
end:if(draw)draw->rva0027B18C(entry);
}
