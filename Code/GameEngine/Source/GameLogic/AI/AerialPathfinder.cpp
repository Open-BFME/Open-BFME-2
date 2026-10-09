// cl: /O1 /arch:SSE /G7 /MD /EHs
// BFME1 donor f98983a7d: game/GameEngine/Source/GameLogic/AI/
// AerialPathfinder_separationPush.cpp supplies the separation algorithm.
// Native 00375C28..00375DFF, RET16, proves Object geometry+A8/radius+BC,
// AI+258 slot97, partner ObjectID+4C0 and ThingTemplate kind words+108.
// WB F2C0E0 corroborates the algorithm; original method name is unknown.
// Native clears the temporary filter's unwind state immediately after the
// range query, before all loop calls. Nonthrowing views of the existing
// vector helpers preserve that lifetime without changing their linkage.
// The native loop records an overlap after adding the separation vector.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"
class GeometryInfo { public: char prefix[0x14];float radius; };
class ThingTemplate {public: char prefix[0x108];unsigned kinds[7];};
class AerialPartner {public:char prefix[0x4C0];unsigned id;};
class AerialAI {public:
#define V(n) virtual void slot##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79) V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95) V(96)
#undef V
 virtual AerialPartner* getPartner();
};
class Object {public:
 void* vtable;ThingTemplate* thing;char pad8[0x38-8];Coord3D position;float angle;
 char pad48[0x74-0x48];unsigned id;char pad78[0xA8-0x78];GeometryInfo geometry;
 char padC0[0x258-0xC0];AerialAI* ai;
};
class Rva000421C8 {public:
 Rva000421C8():next(0){} virtual ~Rva000421C8(){} virtual bool allow(Object*)=0;virtual int getPlayerMask();
 Rva000421C8* next;
};
class Rva00261603Filter : public Rva000421C8 {public:
 Rva00261603Filter(const Coord3D&,const GeometryInfo&,float,bool) throw();virtual bool allow(Object*);
 private:Coord3D position;const GeometryInfo& geometry;float angle;bool desired;
};
class BfmeVec3EJ;
class Gen_000E5A50 {public:float bfmeDistanceSquared(const BfmeVec3EJ*)const throw();};
class Rva001E438B {public:void rva001E438B(float*,const float*) throw();};
// ?nativeLength absent-from-retail - source-only nonthrowing call view
static __forceinline float nativeLength(const Coord3D*p) throw(){return p->length();}
// ?nativeNormalize absent-from-retail - source-only nonthrowing call view
static __forceinline void nativeNormalize(Coord3D*p) throw(){p->normalize();}
extern PartitionManager* ThePartitionManager;
class AerialPathfinder {public:bool rva00375C28(Object*,const Coord3D*,float*,Coord3D*);};
bool AerialPathfinder::rva00375C28(Object*obj,const Coord3D*pos,float*worstOverlap,Coord3D*push){
 bool clear=true;
 AerialAI* ai=obj->ai;
 float radius=obj->geometry.radius;
 unsigned partnerID=0;
 if(ai){AerialPartner*partner=ai->getPartner();if(partner)partnerID=partner->id;}
 const BfmeWideResult& found=ThePartitionManager->iterateObjectsInRange(pos,radius,3,
 &Rva00261603Filter(*pos,obj->geometry,obj->angle,true),0);
 Object*them;
 while((them=const_cast<BfmeWideResult&>(found).next())!=0){
  if(them==obj)continue;
  if(partnerID!=0&&partnerID==them->id)continue;
  if((them->thing->kinds[0]&0x100)!=0)continue;
  if((them->thing->kinds[0]&0x200)!=0)continue;
  if((them->thing->kinds[3]&0x2000)!=0)continue;
  if((them->thing->kinds[0]&4)==0){
   float range=radius*1.2f;
   if(((Gen_000E5A50*)them)->bfmeDistanceSquared((BfmeVec3EJ*)&obj->position)>range*range)continue;
  }
  Coord3D delta;((Rva001E438B*)them)->rva001E438B(&delta.x,&pos->x);
  float overlap=them->geometry.radius*2.0f+obj->geometry.radius-nativeLength(&delta);
  if(*worstOverlap<overlap)*worstOverlap=overlap;
  nativeNormalize(&delta);
  delta.x*=overlap;delta.y*=overlap;delta.z*=overlap;
  push->x+=delta.x;push->y+=delta.y;push->z+=delta.z;
  clear=false;
 }
 return clear;
}
