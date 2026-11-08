// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2
// Clean BFME1 donor cee35b7d8c, game/GameEngineDevice/Source/W3DDevice/
// GameClient/Drawable/Draw/W3DModelDraw.cpp::handleClientTurretPositioning,
// and the donor WWMath/matrix3d.h inline rotations guide the purpose/math.
// Target native B77B2..B7C18 RET0 and WB92F270 establish W3DModelDraw's
// client turret positioning and BFME2 additions: variable turret list,
// fallback Object::GetRelativeAngle and interpolation through GameEngine+3C.
// Native independently proves drawable+8/Object+FC/AI+258/AI goal+30,
// goal Coord+24; state+14/list+D0/valid byte+F5; loaded state+18/render+50;
// previous/new angle 2C8/2D0 and pitch2CC/2D4. Turret record stride24,
// art angle/pitch8/C and bone IDs10/14; only observed prefixes are modeled.
// Render slots54/57 are Capture_Bone/Control_Bone (donor identity and native
// call contract); direct calls2626FA and B4542 have owned matching providers.
// TurretVector is an observed three-pointer storage view, not STL ownership.
// Real donor Matrix3D header is required for its mixed x87/SSE math shape;
// point copy by pointer helper reproduces native ADD24 then member loads.
// Recoil B4E43..B508A RET0, WB92FC00, and donor handleClientRecoil
// establish the second method. Target adds nullable animation state at18.
// Independently measured: MD4/maxRecoil58/damping5C/settle60, animation
// barrel vectorsAC (6x12)/flagsF4 bit8, state hasRecoil bytesF6..FB,
// recoil vectorsC8 (6x12), barrel stride60/bones0+8, recoil stride12
// state0/shift4/rate8. Muzzle-flash method is owned RvaB304B73B.
// Vector begin()+index staging preserves the native SIB byte order.
#include "matrix3d.h"
#include <math.h>
#include "Lib/Coord3D.h"
__forceinline void turretCoordCopy(Coord3D*out,const Coord3D*in){out->x=in->x;out->y=in->y;out->z=in->z;}
class GameEngine;
extern GameEngine *TheGameEngine;
struct TurretEngineView {char pad[0x3c];float fraction;};
enum WhichTurretType {TURRET_PRIMARY=0};
#include "../../../../../../GameEngine/Include/GameLogic/Module/AIUpdate.h"
#include "../../../../../../GameEngine/Include/GameLogic/AIStateMachineClass.h"
class Object {public:float GetRelativeAngle(const Coord3D*)const;char pad[0x258];AIUpdateInterface *ai;};
struct TurretDrawableView {char pad[0xfc];Object *object;};
class TurretRenderView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void Capture_Bone(int);
 virtual void s55();
 virtual void s56();
 virtual void Control_Bone(int,const Matrix3D&,bool);
};
struct TurretInfoView {int angleName,pitchName;float artAngle,artPitch;int angleBone,pitchBone;};
struct TurretStateView {char pad[0xd0];struct TurretVector {TurretInfoView *first,*last,*limit;unsigned size()const{return last-first;}const TurretInfoView &operator[](unsigned n)const{return first[n];}} turrets;char padDC[0xf5-0xdc];bool validTurrets;bool hasRecoil[6];};
class Rva000B304B {public:void setMuzzleFlashHidden(void*,bool);};
struct BarrelView {int recoilBone,fireBone,muzzleFlashBone;char rest[0x3c-12];};
struct RecoilView {int state;float shift,rate;};
template<class T>struct RecoilVectorView {T*first,*last,*limit;unsigned size()const{return last-first;}T*begin()const{return first;}T&operator[](int n)const{return *(begin()+n);}};
struct RecoilStateView {char pad[0xac];RecoilVectorView<BarrelView> barrels[6];unsigned flags;};
struct RecoilMDView {char pad[0x58];float maxRecoil,damping,settle;};
class W3DModelDraw {public:
 char pad00[4];const RecoilMDView *data;TurretDrawableView *drawable;char pad0c[8];TurretStateView *state;RecoilStateView *loadedState;char pad1c[0x50-0x1c];TurretRenderView *render;
 char pad54[0xc8-0x54];RecoilVectorView<RecoilView> recoils[6];char pad110[0x2c8-0x110];float prevAngle,prevPitch,newAngle,newPitch;
 protected:void handleClientTurretPositioning();void handleClientRecoil();
};
void W3DModelDraw::handleClientRecoil() {
 if(!loadedState)return;
 const RecoilMDView*recoilMDView=data;
 if(!(loadedState->flags&8))return;
 for(int wslot=0;wslot<6;++wslot) {
  if(!state->hasRecoil[wslot])continue;
  const RecoilVectorView<BarrelView>&barrels=loadedState->barrels[wslot];
  RecoilVectorView<RecoilView>&r=recoils[wslot];
  int count=barrels.size(),rc=r.size();
  count=(count>rc)?rc:count;
  for(int i=0;i<count;++i) {
   if(barrels[i].muzzleFlashBone!=0) ((Rva000B304B*)&barrels[i])->setMuzzleFlashHidden(render,r[i].state!=1);
   if(barrels[i].recoilBone) {
    switch(r[i].state) {
     case 0:break;
     case 1:case 2:
      r[i].shift+=r[i].rate;
      r[i].rate*=recoilMDView->damping;
      if(r[i].shift>=recoilMDView->maxRecoil){r[i].shift=recoilMDView->maxRecoil;r[i].state=3;}
      else if(fabs(r[i].rate)<0.01f)r[i].state=3;
      break;
     case 3:
      r[i].shift-=recoilMDView->settle;
      if(r[i].shift<=0){r[i].shift=0;r[i].state=0;}
      break;
    }
    Matrix3D m;m.Make_Identity();m.Translate_X(-r[i].shift);
    if(render){render->Capture_Bone(barrels[i].recoilBone);render->Control_Bone(barrels[i].recoilBone,m,false);}
   }else r[i].state=0;
  }
 }
}
void W3DModelDraw::handleClientTurretPositioning() {
 if(!state || !state->validTurrets)return;
 for(int tslot=0;tslot<1;++tslot) {
  if((unsigned)tslot>=state->turrets.size())break;
  const TurretInfoView &tur=state->turrets[tslot];
  float angle=0,pitch=0;
  if(tur.angleBone || tur.pitchBone) {
   float fraction=((TurretEngineView*)TheGameEngine)->fraction;
   const Object *obj=drawable->object;
   if(obj) {
    const AIUpdateInterface *ai=obj->ai;
    if(ai && !ai->getTurretRotAndPitch((WhichTurretType)tslot,&angle,&pitch)) {
     Coord3D pos;turretCoordCopy(&pos,ai->m_stateMachine->getGoalPosition());
     angle=obj->GetRelativeAngle(&pos);
    }
   }
   if(tur.angleBone) {
    float drawAngle=0;
    if(loadedState) {
     angle+=tur.artAngle;
     if(-1000.0f > prevAngle) {prevAngle=newAngle=angle;drawAngle=angle;}
     else if(fraction==1.0f) {prevAngle=newAngle;newAngle=angle;drawAngle=prevAngle;}
     else {
      float delta=newAngle-prevAngle;
      if(delta>3.14159265358979323846f)delta-=6.28318530717958647692f;
      else if(delta< -3.14159265358979323846f)delta+=6.28318530717958647692f;
      drawAngle=prevAngle+delta*fraction;
     }
    }
    Matrix3D matrix(1);matrix.Rotate_Z(drawAngle);
    if(render){render->Capture_Bone(tur.angleBone);render->Control_Bone(tur.angleBone,matrix,false);}
   }
   if(tur.pitchBone) {
    if(loadedState) {
     pitch+=tur.artPitch;
     if(-1000.0f > prevPitch)prevPitch=newPitch=pitch;
     else if(fraction==1.0f){prevPitch=newPitch;newPitch=pitch;}
    }
    Matrix3D matrix(1);matrix.Rotate_Y(-pitch);
    if(render){render->Capture_Bone(tur.pitchBone);render->Control_Bone(tur.pitchBone,matrix,false);}
   }
  }
 }
}
