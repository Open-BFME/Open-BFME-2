// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include
// Native [0036CC94 0036CE87), 499B RET0. WB00EDE000 names
// AIGroup::computeIndividualDestination; its debug body also has six explicit
// stack arguments and no receiver. ZH AIGroup.cpp:480 supplies the offset,
// radius clamp, normalization and ground-movement semantic guide.
// BFME2 changes: destination-layer lookup includes Object; kind bit109 can
// bypass offsets; modes0/1/2 select raw/formation offsets and optional scaling;
// kind bit186 controls the facing override; failed adjustment copies groupDest.
// Target layout: Object template4/position38/radiusB8/AI258/formation414;
// kind words114/11C; AI virtual224 and locomotor-set1CC; Terrain slot1C.
// Field names carried from the donor are semantic labels, while these offsets,
// calls and snapshot order are independently established by retail.
// The only direct retail caller is37293F. Its slot18 is initialized to0 or2
// at3728A5/3728B3 and passed as mode. The released switch retains an unspecified
// result for other out-of-domain values; no added fallback changes that contract.
#include "Lib/Coord2D.h"
#include "Lib/Coord3D.h"
struct IndividualTemplate {char pad[0x114];unsigned flags114;unsigned pad118;unsigned flags11c;};
class Object;
class LocomotorSet;
class DestinationAI {
public:
 virtual void p000();virtual void p001();virtual void p002();virtual void p003();
 virtual void p004();virtual void p005();virtual void p006();virtual void p007();
 virtual void p008();virtual void p009();virtual void p010();virtual void p011();
 virtual void p012();virtual void p013();virtual void p014();virtual void p015();
 virtual void p016();virtual void p017();virtual void p018();virtual void p019();
 virtual void p020();virtual void p021();virtual void p022();virtual void p023();
 virtual void p024();virtual void p025();virtual void p026();virtual void p027();
 virtual void p028();virtual void p029();virtual void p030();virtual void p031();
 virtual void p032();virtual void p033();virtual void p034();virtual void p035();
 virtual void p036();virtual void p037();virtual void p038();virtual void p039();
 virtual void p040();virtual void p041();virtual void p042();virtual void p043();
 virtual void p044();virtual void p045();virtual void p046();virtual void p047();
 virtual void p048();virtual void p049();virtual void p050();virtual void p051();
 virtual void p052();virtual void p053();virtual void p054();virtual void p055();
 virtual void p056();virtual void p057();virtual void p058();virtual void p059();
 virtual void p060();virtual void p061();virtual void p062();virtual void p063();
 virtual void p064();virtual void p065();virtual void p066();virtual void p067();
 virtual void p068();virtual void p069();virtual void p070();virtual void p071();
 virtual void p072();virtual void p073();virtual void p074();virtual void p075();
 virtual void p076();virtual void p077();virtual void p078();virtual void p079();
 virtual void p080();virtual void p081();virtual void p082();virtual void p083();
 virtual void p084();virtual void p085();virtual void p086();virtual void p087();
 virtual void p088();virtual void p089();virtual void p090();virtual void p091();
 virtual void p092();virtual void p093();virtual void p094();virtual void p095();
 virtual void p096();virtual void p097();virtual void p098();virtual void p099();
 virtual void p100();virtual void p101();virtual void p102();virtual void p103();
 virtual void p104();virtual void p105();virtual void p106();virtual void p107();
 virtual void p108();virtual void p109();virtual void p110();virtual void p111();
 virtual void p112();virtual void p113();virtual void p114();virtual void p115();
 virtual void p116();virtual void p117();virtual void p118();virtual void p119();
 virtual void p120();virtual void p121();virtual void p122();virtual void p123();
 virtual void p124();virtual void p125();virtual void p126();virtual void p127();
 virtual void p128();virtual void p129();virtual void p130();virtual void p131();
 virtual void p132();virtual void p133();virtual void p134();virtual void p135();
 virtual void p136();
 virtual bool isDoingGroundMovement();
};
class Object {
public:
 float GetRelativeAngle(const Coord3D*)const;
 void rva0028AD00(int,float,int);
 char pad0[4];IndividualTemplate *info;
 char pad8[0x38-8];float x,y,z,angle;
 char pad48[0xb8-0x48];float radius;
 char padbc[0x258-0xbc];DestinationAI *ai;
 char pad25c[0x414-0x25c];Coord2D formation;
};
enum PathfindLayerEnum { DestinationLayerInvalid=0,DestinationLayerGround=1,DestinationLayerRamp=16 };
class TerrainLogic {
public:
 virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void p6();
 virtual float getLayerHeight(float,float,int,Coord3D*,bool);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {public:bool adjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};extern AI *TheAI;
class AIGroup
{
public:
 static void computeIndividualDestination(Coord3D*,const Coord3D*,Object*,const Coord3D*,const float*,int);
};
void AIGroup::computeIndividualDestination(Coord3D *dest,const Coord3D *groupDest,Object *obj,const Coord3D *center,const float *facing,int mode)
{
 Coord2D offset;
 bool special=(obj->info->flags114>>13)&1;
 int layer=TheTerrainLogic->getLayerForDestination(obj,groupDest);
 if(special && layer!=1){*dest=*groupDest;return;}
 if(mode){offset=obj->formation;}
 else{offset.x=obj->x-center->x;offset.y=obj->y-center->y;}
 float offsetX,offsetY;
 if(mode!=2){
  float length=offset.length();
  if(length>6.f*obj->radius)length=6.f*obj->radius;
  offset.normalize();offsetX=offset.x*length;offsetY=offset.y*length;
 }else {offsetX=offset.x;offsetY=offset.y;}
 dest->x=groupDest->x+offsetX;dest->y=groupDest->y+offsetY;
 dest->z=TheTerrainLogic->getLayerHeight(dest->x,dest->y,layer,0,true);
 DestinationAI *ai=obj->ai;
 if(ai && ai->isDoingGroundMovement()){
  float angle=0.f;bool adjusted;
  switch(mode){
  case 0:
   if(obj->info->flags11c&(1u<<26)){float current=obj->angle;angle=current+obj->GetRelativeAngle(dest);}
   adjusted=TheAI->pathfinder->adjustDestination(obj,*(const LocomotorSet*)((char*)ai+0x1cc),dest,groupDest);break;
  case 1:
   if(obj->info->flags11c&(1u<<26)){float current=obj->angle;angle=current+obj->GetRelativeAngle(dest);}
   adjusted=TheAI->pathfinder->adjustDestination(obj,*(const LocomotorSet*)((char*)ai+0x1cc),dest,0);break;
  case 2:
   if(facing && (obj->info->flags11c&(1u<<26)))angle=*facing;
   adjusted=TheAI->pathfinder->adjustDestination(obj,*(const LocomotorSet*)((char*)ai+0x1cc),dest,0);break;
  }
  if(!adjusted)*dest=*groupDest;
  obj->rva0028AD00((int)dest,angle,1);
 }
}
