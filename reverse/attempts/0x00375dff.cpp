// ?rva00375DFF@AerialPathfinder@@QAE_NPAVObject@@PAVRva00375A73Context@@MM@Z
// partial score=0.9777 date=2026-10-10
// ?rva00375DFF@AerialPathfinder@@QAE_NPAVObject@@PAVRva00375A73Context@@MM@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHs
// BFME1 f98983a7d AerialPathfinder_separationPush semantic donor;
// target 375C28..375DFF/471 establishes layouts and all callees.
#include "../../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../../Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
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
static __forceinline float nativeLength(const Coord3D*p) throw(){return p->length();}
static __forceinline void nativeNormalize(Coord3D*p) throw(){p->normalize();}
extern PartitionManager* ThePartitionManager;
struct Rva00375A73Coord:Coord3D{};
class Rva00375A73Context {public: char prefix[0x24];bool valid24;};
class TerrainLogic
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual float getGroundHeight(float x, float y, Coord3D *normal) const;
};
extern TerrainLogic *TheTerrainLogic;

class AerialPathfinder {public:bool rva00375A73(Rva00375A73Context*,float,Rva00375A73Coord*); bool rva00375DFF(Object*,Rva00375A73Context*,float,float);bool rva00375C28(Object*,const Coord3D*,float*,Coord3D*);};
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

extern AerialPathfinder *TheAerialPathfinder;
bool AerialPathfinder::rva00375DFF(Object *obj, Rva00375A73Context *context, float distance, float clearance)
{
    if (obj->ai && context->valid24)
    {
        Rva00375A73Coord pos;
        if (rva00375A73(context, distance, &pos))
        {
            pos.z -= clearance * 0.5f;
            bool above = false;
            bool hit = false;
            float t = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
            if (pos.z > t)
                above = true;
            t = 0.0f;
            Rva00375A73Coord where;
            where.x = 0.0f;
            where.y = 0.0f;
            where.z = 0.0f;
            if (TheAerialPathfinder->rva00375C28(obj, &pos, &t, &where))
                hit = true;
            bool ok=above==true&&hit==true; return ok==true;
        }
    }
    return true;
}
