// ?call@Rva001E19E8CallView@@QBEXPBUCoord3D@@PBVMatrix3D@@PBVObject@@2@Z
// partial score=0.884135 date=2026-10-09
// ?call@Rva001E19E8CallView@@QBEXPBUCoord3D@@PBVMatrix3D@@PBVObject@@2@Z
// partial score=0.8 date=2026-10-09
// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /ICode/Libraries/Include /DNDEBUG /MD /EHsc /Oi-
#include "Lib/Coord3D.h"
#include "matrix3d.h"
#include "ascii_string.h"
#pragma intrinsic(sqrt)
class Object;
class Drawable { public: bool rva00272835(int,int); };
class Thing {public: Drawable *getDrawable() const;};
class Object {public: int rva0028B511() const;};
class GameClientRandomVariable {public: float getValue() const; int type; float low,high;};
float GetGameClientRandomValueReal(float,float,char*,int);
struct Rva001F3899Arg; struct Rva001F38C1Arg; struct Rva001F3C43Arg;
class Rva001F3899Slot {public: void set(const Rva001F3899Arg&);};
class Rva001F38C1Slot {public: void set(const Rva001F38C1Arg&);};
class Rva001F3C43Slot {public: void set(const Rva001F3C43Arg*);};
class Rva001F3C60Slot {public: AsciiString& set(const AsciiString&);};
class ParticleSystem {public:
 void rotateLocalTransformX(float);void rotateLocalTransformY(float);void rotateLocalTransformZ(float); void destroy();
 char pad[0x120]; unsigned int delay; char pad124[4];int field128;char pad12C[0x188-0x12C];Vector3 target;bool targetValid;
 __forceinline void setPosition(const Coord3D*p){((Rva001F3899Slot*)this)->set(*(const Rva001F3899Arg*)p);}
 __forceinline void setLocalTransform(const Matrix3D*m){((Rva001F38C1Slot*)this)->set(*(const Rva001F38C1Arg*)m);}
 __forceinline void attachToObject(const Object*p){((Rva001F3C43Slot*)this)->set((const Rva001F3C43Arg*)p);}
 __forceinline void setTarget(const Vector3&p){target=p;targetValid=true;}
};
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {public: void rva0004CBC0() throw();};
class BfmeParticleSystemHandle {public:
 __forceinline ~BfmeParticleSystemHandle(){if(system)((RvaSmartPtr12*)this)->rva0004CBC0();}
 operator bool() const{return system!=0;}
 __forceinline ParticleSystem*operator->() const{return system?system:Make001FCBD7();}
 ParticleSystem*system;void*previous;void*next;
};
class ParticleSystemTemplate;
class ParticleSystemManager {public: ParticleSystemTemplate*findTemplate(const AsciiString&)const; BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);};
extern ParticleSystemManager *TheParticleSystemManager;
enum PathfindLayerEnum{LAYER_GROUND};
class TerrainLogic {public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();
 virtual float s07(float,float,PathfindLayerEnum,float*,bool);virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual bool s19(float,float,float*,float*,unsigned char*);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {public: int GetGroundLayer(const Coord3D*);};
struct RvaFxAi {char pad[0x10];Pathfinder *path;};
extern RvaFxAi *TheAI;
extern float g_msecToFrames;
class Rva001E19E8CallView {public:
 void call(const Coord3D*,const Matrix3D*,const Object*,const Object*)const;
 char pad[0x148]; AsciiString name;int count; Coord3D offset;GameClientRandomVariable radius,height,delay;
 float rotateX,rotateY,rotateZ;bool orient,attach;char pad18e[2];AsciiString bone;
 bool ground,ricochet;char pad196[2];AsciiString createBone,targetBone;bool secondaryBone;char pad1a1[3];int unknown1a4,field1a8;
 bool useTarget,aimSecondary,killWater,killLand;Coord3D targetOffset;
};
static __forceinline const Coord3D *objectPos(const Object*p){return (const Coord3D*)((const char*)p+0x38);}
static __forceinline bool boneTransform(const Object*p,const AsciiString&name,Matrix3D&m){return ((const Thing*)p)->getDrawable()->rva00272835((int)name.str(),(int)&m);}
void adjustVector(Coord3D*,const Matrix3D*);
static __forceinline int roundDelay(float f){int n;__asm { fld f } __asm { fistp n } return n;}
static __forceinline void rotateParticleY(Matrix3D&m,const float&s,float c){m.Rotate_Y(s,c);}
void Rva001E19E8CallView::call(const Coord3D*primary,const Matrix3D*mtx,const Object*thingToAttachTo,const Object*secondary)const {
 Vector3 localOffset=*(const Vector3*)&offset;
 if(mtx)adjustVector((Coord3D*)&localOffset,mtx);
 const ParticleSystemTemplate*tmp=TheParticleSystemManager->findTemplate(name);
 if(tmp)for(int i=0;i<count;++i){
  BfmeParticleSystemHandle sys=TheParticleSystemManager->createParticleSystem(tmp,true);
  if(sys){
   Coord3D newPos={0,0,0};
   float rad=radius.getValue();
   float angle=GetGameClientRandomValueReal(0,6.28318530717958647692f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\FXList.cpp",1698);
   bool needsHeight=true;
   if(!((const StringBase<char>*)&createBone)->isEmpty()&&thingToAttachTo){
    Matrix3D bm(true);
    if(secondaryBone&&secondary)boneTransform(secondary,createBone,bm);
    else boneTransform(thingToAttachTo,createBone,bm);
    Vector3 translation=bm.Get_Translation(); newPos=*(const Coord3D*)&translation; needsHeight=false;
   } else {
    newPos.x=rad*cos(angle)+primary->x+localOffset.X;
    newPos.y=rad*sin(angle)+primary->y+localOffset.Y;
   }
   if(ground&&TheTerrainLogic){if(needsHeight){PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,&newPos);newPos.z=TheTerrainLogic->s07(newPos.x,newPos.y,layer,0,true);}}
   else if(needsHeight)newPos.z=height.getValue()+primary->z+localOffset.Z;
   if(orient&&mtx){
    Matrix3D orientation=*mtx;
    if(aimSecondary&&secondary){
     const Coord3D*sp=objectPos(secondary);
     Vector3 delta=Vector3(-newPos.x,-newPos.y,-newPos.z)+Vector3(sp->x,sp->y,sp->z);
     float len=WWMath::Sqrt(delta.X*delta.X+delta.Y*delta.Y);delta.Z+=10.0f;float angleToTarget=(float)atan2((double)delta.Z,(double)len);float a=1.5707963267948966f-angleToTarget;
     float s;Matrix3D rotation(true);rotateParticleY(rotation,s,(s=(float)sin(a),(float)cos(a)));orientation.postMul(rotation);
    }
    sys->setLocalTransform(&orientation);
   }
   if(rotateX!=0)sys->rotateLocalTransformX(rotateX);
   if(rotateY!=0)sys->rotateLocalTransformY(rotateY);
   if(rotateZ!=0)sys->rotateLocalTransformZ(rotateZ);
   if(killWater){
    bool water=TheTerrainLogic->s19(newPos.x,newPos.y,0,0,0);
    if(water&&TheAI&&TheAI->path&&TheAI->path->GetGroundLayer(&newPos)!=1)water=false;
    if(thingToAttachTo&&thingToAttachTo->rva0028B511()!=1)water=false;
    if(water){sys->destroy();continue;}
   }else if(killLand){
    bool water=TheTerrainLogic->s19(newPos.x,newPos.y,0,0,0);
    if(water&&TheAI&&TheAI->path&&TheAI->path->GetGroundLayer(&newPos)!=1)water=false;
    if(thingToAttachTo&&thingToAttachTo->rva0028B511()!=1)water=false;
    if(!water){sys->destroy();continue;}
   }
   if(attach&&thingToAttachTo)sys->attachToObject(thingToAttachTo);else sys->setPosition(&newPos);
   if(!((const StringBase<char>*)&bone)->isEmpty())((Rva001F3C60Slot*)sys.operator->())->set(bone);
   if(!((const StringBase<char>*)&targetBone)->isEmpty()&&secondary){
    Matrix3D bm(true);Vector3 p;
    if(boneTransform(secondary,targetBone,bm)){p.X=bm.Get_X_Translation();p.Y=bm.Get_Y_Translation();p.Z=bm.Get_Z_Translation();}else {const Coord3D *sp=objectPos(secondary);p=Vector3(sp->x,sp->y,sp->z);}
    sys->setTarget(p);
   }
   if(useTarget){Vector3 p(targetOffset.x+newPos.x,targetOffset.y+newPos.y,targetOffset.z+newPos.z);sys->setTarget(p);}
   if(field1a8>=0){ParticleSystem *raw=sys.operator->();int field=field1a8;raw->field128=field;}
   float wait=delay.getValue();if(wait>=0)sys->delay=roundDelay((float)ceil((double)(wait*g_msecToFrames)));
  }
 }
}
