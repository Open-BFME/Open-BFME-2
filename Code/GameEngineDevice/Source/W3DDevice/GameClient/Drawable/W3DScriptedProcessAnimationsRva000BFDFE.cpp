// cl: /O1 /G7 /arch:SSE /MD
// Primary semantic references: pinned BF1 575ba2b04 ZH W3DModelDraw::doDrawModule
// completion/state selection and WW3D animobj.cpp::Compute_Current_Frame.
// Target-specific three-slot animation/blend handling is independently present
// in named WB944C80 W3DScriptedModelDraw::processAnimations and native BFDFE.
// Every accessed layout below is a scoped native ABI view; original field and
// secondary class names are unknown. Existing address-derived adjustment and
// state-application keys preserve their opaque argument contracts.
// The local completion function is compiled together with its caller: retail
// proves ECX object / ESI slot / caller-cleaned bool stack ABI, chosen by MSVC
// for this file-static C++ function. No ABI emulation or assembly is used.
// Volatile existing last-frame operand in the backward loop preserves retail's
// multiply then add and stack homes, without introducing an extra memory read.
// Named ping-pong intermediate and per-branch blend stores preserve native order;
// forceinline drawable getter retains pause payload DL and saved vtable EAX.
#include <math.h>
__forceinline float Min(const float&a,const float&b){return a<b?a:b;}
__forceinline float Max(const float&a,const float&b){return a>b?a:b;}
extern int g_bfmeDisplayAnimationSyncClock;
class WW3D{static unsigned SyncTime,PreviousSyncTime;public:static unsigned Delta(){return SyncTime-PreviousSyncTime;}};
class AnimationMotion{public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual int NumFrames();virtual float FrameRate();};
class RenderAnimationObj{public:virtual void v0();virtual void v1();virtual void v2();virtual int ClassID();};
class PauseAnimationIface{public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();virtual void v27();virtual void Pause(bool);};

struct AnimSlot{AnimationMotion*motion;float frame,previous,unused;int mode,direction;bool completed,flag;char pad[2];};
static __declspec(noinline) bool Rva000B2E4CComplete(RenderAnimationObj*obj,AnimSlot*s,bool finish){
 if(obj && obj->ClassID()==25 && s->motion){
 switch(s->mode){case 0:case 1:case 3:case 5:return finish?s->completed:false;case 2:if(s->frame>=s->motion->NumFrames()-1.0f)return true;return false;case 6:if(s->frame<=0.0f)return true;return false;}
 }return true;
}
class Rva000B4BED{public:void*rva000B4BED(const void*);};
class Rva0027532F{public:bool rva0027532F(bool);};
class Rva000B3C61{public:void rva000B3CCF(int,int);};
class Rva000B3A68{public:unsigned char rva000B3A68();};
class Rva000B5C41{public:void rva000B5C41();};
class Rva000B7074{public:void rva000B7074();};
class Rva000B5A72{public:void rva000B5A72(void*);};
class ModelConditionFlags{public:bool rva000B3EB3()const;private:unsigned bits[19];};
struct ModelStateView{int pad;ModelConditionFlags flags;char rest[0x5c-0x50];unsigned stateFlags;};
struct ModelDataView{char pad[0x6b];bool requirePower;};
__forceinline unsigned char Flag(unsigned value){return (value>>5)&1;}
class Rva000B8F5AOuter{public:void rva000BF9FC(void*,int,int);void rva000BEE25(void*,float,int,int,int);};
class W3DScriptedModelDraw{public:void processAnimations();__forceinline Rva0027532F*GetDrawable(){return drawable;}
 char pad0[4];ModelDataView*data;Rva0027532F*drawable;char padc[0xc];ModelStateView*state;
 char pad1c[0x44-0x1c];int whichAnimation;bool changed;char pad49[7];RenderAnimationObj*render;
 char pad54[0x90-0x54];float blend,blendTotal,speed,multiplier;char pada0[0xb8-0xa0];unsigned lastSync;char padbc[0x110-0xbc];AnimSlot slots[3];
 char pad164[0x17c-0x164];char signature[0x4c];char pad1c8[3];bool transition;int nextState;char pad1d0[0x25c-0x1d0];bool firstFrame;char pad25d[0x28c-0x25d];bool pending;
 char pad28d[0x2d8-0x28d];bool reselect;
};
void W3DScriptedModelDraw::processAnimations(){
 if(!render || !state)return;
 ModelDataView*module=data;
 ((Rva000B5A72*)this)->rva000B5A72(module);
 if(!slots[0].motion && !slots[1].motion){
  if(transition){void*next=((Rva000B4BED*)module)->rva000B4BED(signature);if(next){pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);}transition=false;nextState=0;}return;
 }
 unsigned delta=(unsigned)g_bfmeDisplayAnimationSyncClock-lastSync;lastSync=g_bfmeDisplayAnimationSyncClock;
 if(firstFrame){firstFrame=false;delta=WW3D::Delta();}
 ((PauseAnimationIface*)((char*)this+0xc))->Pause(!GetDrawable()->rva0027532F(module->requirePower));
 if(!slots[0].motion && slots[1].motion){
  ((Rva000B3C61*)this)->rva000B3CCF(0,1);
  if(slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=slots[1].unused;
   float duration;
   if(limit>0.0f){float last=slots[1].motion->NumFrames()-1.0f;duration=Max(1.0f,Min(limit,last));}
   else{float last=slots[1].motion->NumFrames()-1.0f;duration=Max(1.0f,Min(5.0f,last));}
   blend=blendTotal=duration;
  }
 }
 for(int i=0;i<3;++i){AnimSlot&s=slots[i];if(s.motion){
  float step=s.motion->FrameRate()*multiplier*speed*delta*0.001f;
  float last=s.motion->NumFrames()-1.0f;
  s.previous=s.frame;s.completed=false;
  switch(s.mode){
  case 1:s.frame=step+s.frame;if(s.frame>last){s.frame-=int(s.frame/last)*last;s.completed=true;}break;
  case 2:s.frame=step+s.frame;if(s.frame>last){s.frame=last;s.completed=true;}break;
  case 3:{float frame=s.frame+s.direction*step;s.frame=frame;if(s.direction==1){if(frame>last){s.direction=-1;float repeated=int(frame/last)*last;repeated+=last;s.frame=repeated-frame;s.completed=true;}}else if(s.frame<0.0f){int repeats=(int)(fabs((double)s.frame)/last);if(repeats>0)s.frame+=repeats*last;s.frame=-s.frame;s.direction=1;s.completed=true;}break;}
  case 5:{s.frame-=step;if(s.frame<0.0f){float repeated=(int)(fabs((double)s.frame)/last)*(*(volatile float*)&last);repeated+=last;s.frame+=repeated;s.completed=true;}break;}
  case 6:s.frame-=step;if(s.frame<0.0f){s.frame=0.0f;s.completed=true;}break;
  }
 }}
 if(slots[0].motion && slots[1].motion){
  float step=slots[1].motion->FrameRate()*multiplier*speed*delta;
  blend-=step*0.001f;
  if(blend<0.0f){((Rva000B3C61*)this)->rva000B3CCF(0,1);if(slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=slots[1].unused;
   if(limit>0.0f){float last=slots[1].motion->NumFrames()-1.0f;blend=blendTotal=Max(1.0f,Min(limit,last));}
   else{float last=slots[1].motion->NumFrames()-1.0f;blend=blendTotal=Max(1.0f,Min(5.0f,last));}
  }else blend=0.0f;}
 }
 if(!((Rva000B3A68*)this)->rva000B3A68() && Rva000B2E4CComplete(render,&slots[0],transition) && render && state && whichAnimation!=-1){
  if(transition){void*next=((Rva000B4BED*)module)->rva000B4BED(signature);if(next){nextState=0;pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);if(!nextState)transition=false;return;}else{transition=false;nextState=0;}}
  ModelStateView*cur=state;
  if(!cur->flags.rva000B3EB3())((Rva000B8F5AOuter*)this)->rva000BEE25(cur,-1.0f,0,0,0);
  else if(Flag(cur->stateFlags)){((Rva000B8F5AOuter*)this)->rva000BEE25(cur,-1.0f,0,0,0);changed=true;}
 }
 if(reselect){reselect=false;((Rva000B8F5AOuter*)this)->rva000BEE25(0,-1.0f,0,0,0);}
 ((Rva000B5C41*)this)->rva000B5C41();((Rva000B7074*)this)->rva000B7074();
}
