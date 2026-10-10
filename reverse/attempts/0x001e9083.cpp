// ?rva001E9083@Rva001E46E1@@QAEXPAVObject@@PBUCoord3D@@MM@Z
// partial score=0.44809 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oi- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include
// ZH Locomotor::locoUpdate_moveTowardsPosition is the primary movement guide.
// BFME2 native 1E9083..1E99D8 plus40B jump table: transform-driven movement,
// cached speed clamp and wall climbing precede the appearance dispatch.
// Original target member name is not established; existing neutral ABI retained.
#include "matrix3d.h"
#include "Lib/Coord3D.h"
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <math.h>
extern GameLogic*TheGameLogic;
#define __min(a,b) (((a)<(b))?(a):(b))
#define __max(a,b) (((a)>(b))?(a):(b))
enum ObjectStatusTypes { STATUS_ZERO=0 };enum KindOfType { KIND_ZERO=0 };enum PathfindLayerEnum {LAYER_ZERO=0};enum Relationship {REL_ZERO=0};
class Drawable {public:void rva00272A02(bool);};
class Thing {public:
 const Coord3D*getUnitDirectionVector2D()const;void setPosition(const Coord3D*);void setOrientation(float);void setTransformMatrix(const Matrix3D*);Drawable*getDrawable()const;
 char pad00[8];Matrix3D transform08;Coord3D pos38;float angle44;
};
class GeometryInfo {public:float getMaxHeightAbovePosition()const;char pad00[0x24];float major24;};
class AIUpdateInterface {public:void destroyPath();};
class Rva00373EC6 {public:char pad00[0x3c];void*p3c;};
class StealthUpdate {public:void markAsDetected(unsigned,int,Object*,bool);};
class Object:public Thing {public:
 bool testStatus(ObjectStatusTypes)const;bool isKindOf(KindOfType)const;int rva0028B511()const;void rva0028AE6D();Rva00373EC6*rva0028F4BC();bool isLocallyControlled()const;
 char pad48[0x78-0x48];ObjectID parent78;char pad7C[0xa8-0x7c];GeometryInfo geomA8;char padD0[0x110-0xd0];unsigned flag110,flag114,flag118;char pad11c[0x258-0x11c];AIUpdateInterface*ai258;char pad25C[0x274-0x25c];void*p274;
 bool templateMask114(unsigned mask)const {return (*(unsigned*)((char*)this->templatePtr()+0x114)&mask)!=0;}
 bool templateByte(int off,unsigned mask)const {return (*(unsigned char*)((char*)this->templatePtr()+off)&mask)!=0;}
 void*templatePtr()const {return *(void**)((char*)this+4);}
 __forceinline void setClimbDown(){if((flag118&0x80)||!(flag118&0x200)){*(unsigned char*)((char*)this+0x118)&=0x7f;*(unsigned char*)((char*)this+0x119)|=2;rva0028AE6D();}}
 __forceinline void setClimbUp(){if((flag118&0x200)||!(flag118&0x80)){*(unsigned char*)((char*)this+0x119)&=0xfd;*(unsigned char*)((char*)this+0x118)|=0x80;rva0028AE6D();}}
 __forceinline void clearClimb(){if(flag118&0x80){*(unsigned char*)((char*)this+0x118)&=0x7f;rva0028AE6D();}if(flag118&0x200){*(unsigned char*)((char*)this+0x119)&=0xfd;rva0028AE6D();}}
};
class TerrainLogic {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual float height(float,float,int,void*,bool);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};extern TerrainLogic*TheTerrainLogic;
class Pathfinder {public:void*rva001E4461(int,int);};class AI {public:char pad[0x10];Pathfinder*pathfinder;};extern AI*TheAI;
class Player {public:Relationship getRelationship(const Object*)const;};class PlayerList {public:char pad[0x10];Player*local;};extern PlayerList*ThePlayerList;
class Eva {public:void rva001DE2DA(int,const Coord3D*,int);};extern Eva*TheEva;
struct Rva001E4194A;bool __stdcall Rva001E4194Get(Rva001E4194A*);

struct Rva001E3FFDOuter;void*__cdecl Rva001E3FFDGet(Rva001E3FFDOuter*);
class Rva001E3557 {public:bool rva001E3557();};class Rva001E3591 {public:bool rva001E3591();};
class Rva001E7C2B {public:void rva001E7C2B(int,int,float,float);};class Rva001E9045 {public:void rva001E9045(int,int,float,float);};class Rva001E7053 {public:void rva001e7053(unsigned,unsigned,float,float);};class Rva001E8C1B {public:void rva001E8C1B(int,int,float,float);};
class LocoWorker1E6B8B {public:void worker(Object*,const Coord3D*,float,float);};class LocoWorker1E756D {public:void worker(Object*,const Coord3D*,float,float);};class LocoWorker1E7C4C {public:void worker(Object*,const Coord3D*,float,float);};class LocoWorker1E68D7 {public:void worker(Object*,const Coord3D*,float,float);};
float normalizeAngle(float);
struct LocoDataView1E9083 {char pad00[0x74];unsigned appearance74;char pad78[0x150-0x78];bool flag150;};
class Rva001E46E1 {public:
 float rva001E46E1(Object*);bool rva001E7ECA(Object*,const Coord3D*);void rva001E9083(Object*,const Coord3D*,float,float);
 void*vt;LocoDataView1E9083*data;char pad08[0x44-8];unsigned flags44;char pad48[0x5c-0x48];float max5c;unsigned frame60;unsigned frame64;Matrix3D matrix68;bool flag98,flag99;
};
void Rva001E46E1::rva001E9083(Object*obj,const Coord3D*goal,float distance,float speed){
 flags44&=~4u;matrix68=obj->transform08;
 if(TheGameLogic->getFrame()<=frame60&&speed>max5c)speed=max5c;
 float maxSpeed=rva001E46E1(obj);if(speed>maxSpeed)speed=maxSpeed;
 if(Rva001E4194Get((Rva001E4194A*)obj)||obj->testStatus((ObjectStatusTypes)37))return;
 flag99=false;void*path=Rva001E3FFDGet((Rva001E3FFDOuter*)obj);if(path)flag99=((Rva001E3557*)path)->rva001E3557();
 if(!obj->testStatus((ObjectStatusTypes)38)&&!obj->p274){
  Object*parent=obj->parent78?TheGameLogic->findObjectByID(obj->parent78):0;
  if((!parent||!parent->templateMask114(0x2000))&&data->flag150&&!obj->templateMask114(0x2000)&&obj->templateByte(0x11f,1)){
   Coord3D pos=obj->pos38;
   float currentHeight=TheTerrainLogic->height(pos.x,pos.y,obj->rva0028B511(),0,true);
   const Coord3D*dir=obj->getUnitDirectionVector2D();float move=__min(7.0f,speed);
   Coord3D delta={dir->x*move,dir->y*move,dir->z*move};pos.x+=delta.x;pos.y+=delta.y;pos.z+=delta.z;
   float nextHeight=TheTerrainLogic->height(pos.x,pos.y,obj->rva0028B511(),0,true);
   float bias=__max(0.0f,currentHeight-nextHeight+0.1f);
   Object*wall=TheGameLogic->findObjectByID((ObjectID)(unsigned)TheAI->pathfinder->rva001E4461(TheTerrainLogic->getLayerForDestination(obj,&pos),(int)&pos));
   bool climbing=false,descending=false;
   if(wall&&wall->templateByte(0x121,2)){
    Vector3 local(pos.x,pos.y,pos.z);Matrix3D inverse;wall->transform08.Get_Orthogonal_Inverse(inverse);Matrix3D::Transform_Vector(inverse,local,&local);
    float width=wall->geomA8.major24;
    if(fabs(local.X)>width||local.Z>wall->geomA8.getMaxHeightAbovePosition())goto clear;
    float wallTop=wall->pos38.z+wall->geomA8.getMaxHeightAbovePosition();
    if(wallTop>pos.z){pos.x-=delta.x;pos.y-=delta.y;pos.z-=delta.z;climbing=true;
     if(obj->isKindOf((KindOfType)103)){pos.z+=speed*0.6f;if(pos.z>wallTop)pos.z=wallTop;}
     else{
      const Coord3D*forward=obj->getUnitDirectionVector2D();Coord3D copy=*forward;forward=wall->getUnitDirectionVector2D();
      float dot=copy.z*forward->z+copy.y*forward->y+copy.x*forward->x;
      obj->setOrientation(dot>=0?wall->angle44:normalizeAngle(wall->angle44+3.1415927f));
      Vector3 moved(pos.x,pos.y,pos.z);Matrix3D::Transform_Vector(inverse,moved,&moved);
      if(moved.X>wall->geomA8.major24)moved.X=wall->geomA8.major24;else if(moved.X<-wall->geomA8.major24)moved.X=-wall->geomA8.major24;
      Matrix3D::Transform_Vector(wall->transform08,moved,&moved);pos.x=moved.X;pos.y=moved.Y;pos.z=moved.Z;
      if(wall->isLocallyControlled()&&ThePlayerList->local->getRelationship(obj)==REL_ZERO)TheEva->rva001DE2DA(15,&wall->pos38,0);
     }
    }
   }else{
    nextHeight=TheTerrainLogic->height(pos.x,pos.y,obj->rva0028B511(),0,true);
    if(pos.z<=nextHeight+bias)goto clear;
    pos.x-=delta.x;pos.y-=delta.y;pos.z-=delta.z;descending=true;
    if(obj->isKindOf((KindOfType)105)){pos.z-=speed*0.6f;if(nextHeight+1.0f>=pos.z){pos.z=nextHeight;if(obj->ai258)obj->ai258->destroyPath();if(!(obj->flag110&0x20000000)){obj->flag110|=0x20000000;obj->rva0028AE6D();}}}
   }
   obj->setPosition(&pos);
   if(descending){if(obj->getDrawable())obj->getDrawable()->rva00272A02(false);obj->setClimbDown();}
   else if(climbing){if(obj->getDrawable())obj->getDrawable()->rva00272A02(false);obj->setClimbUp();}
   else{obj->clearClimb();if(obj->getDrawable())obj->getDrawable()->rva00272A02(true);return;}
   {Rva00373EC6*stealth=obj->rva0028F4BC();if(stealth&&stealth->p3c)((StealthUpdate*)stealth)->markAsDetected(0,1,0,true);}return;
clear:
   obj->clearClimb();if(obj->getDrawable())obj->getDrawable()->rva00272A02(true);
  }
 }
 switch(data->appearance74){
 case 0:case 4:case 7:((LocoWorker1E6B8B*)this)->worker(obj,goal,distance,speed);break;
 case 1:((Rva001E8C1B*)this)->rva001E8C1B((int)obj,(int)goal,distance,speed);break;
 case 2:((LocoWorker1E7C4C*)this)->worker(obj,goal,distance,speed);break;
 case 3:((Rva001E7C2B*)this)->rva001E7C2B((int)obj,(int)goal,distance,speed);break;
 case 5:break;
 case 6:((LocoWorker1E756D*)this)->worker(obj,goal,distance,speed);break;
 case 8:((Rva001E9045*)this)->rva001E9045((int)obj,(int)goal,distance,speed);break;
 case 9:((LocoWorker1E68D7*)this)->worker(obj,goal,distance,speed);break;
 default:((Rva001E7053*)this)->rva001e7053((unsigned)obj,(unsigned)goal,distance,speed);break;
 }
 path=Rva001E3FFDGet((Rva001E3FFDOuter*)obj);if(!path||!((Rva001E3591*)path)->rva001E3591())rva001E7ECA(obj,goal);
 obj->setTransformMatrix(&matrix68);flag99=false;
}
