// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// Target B5D7F..B5FB3. Eight args, standard thiscall; native caller BEE25.
// ZH adjustAnimation establishes purpose; BFME2 three-lane blending is target-specific.
class HAnimClass;
class RefCounted{public:virtual void v0();int ref;};
class Rva000B3C61 {public:void rva000B3BCF(int,RefCounted*,unsigned char,int,float,float,float,unsigned char,int);void rva000B3C61(int);void rva000B3CCF(int,int);};
class Rva000B3BA8Arg;
class Rva000B3BA8 {public:void rva000B3BA8(Rva000B3BA8Arg*);};
class HAnimClass:public RefCounted{public:virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual int frameCount();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual unsigned signature();};
struct Rva000B5D7FSlot {HAnimClass *motion;float f04,f08,f0c;int i10,i14;unsigned char b18,b19;char pad1a[2];};
class W3DScriptedModelDraw {
 char pad0[0x50];Rva000B3BA8Arg *render;char pad54[0x90-0x54];float blendRemaining,blendDuration,rate;
 char pad9c[0x110-0x9c];Rva000B5D7FSlot slots[3];
public:void rva000B5D7F(HAnimClass*,unsigned char,int,float,float,float,unsigned char,float);
};
static __forceinline float BlendClamp(float value,float maximum){float v=maximum>value?value:maximum;return 1.0f>v?1.0f:v;}
void W3DScriptedModelDraw::rva000B5D7F(HAnimClass *motion,unsigned char mode,int arg2,float blend,float start,float end,unsigned char flag,float speed){
 rate=speed;if(!motion)return;
 bool compatible=true;unsigned signature=motion->signature();
 if(slots[0].motion && signature!=slots[0].motion->signature())compatible=false;
 if(slots[1].motion && signature!=slots[1].motion->signature())compatible=false;
 Rva000B3C61 *lanes=reinterpret_cast<Rva000B3C61*>(this);
 if(blend!=0.0f && compatible){
  if(!slots[0].motion && !slots[1].motion){lanes->rva000B3BCF(0,motion,mode,arg2,blend,start,end,flag,1);blendDuration=1.0f;blendRemaining=0.0f;}
  else {
   if(slots[0].motion && slots[1].motion){
    if(slots[1].b19){lanes->rva000B3BCF(2,motion,mode,arg2,blend,start,end,flag,1);return;}
    if(blendRemaining/blendDuration<0.5f)lanes->rva000B3CCF(0,1);
   }else if(!slots[0].motion)lanes->rva000B3CCF(0,1);
   lanes->rva000B3BCF(1,motion,mode,arg2,blend,start,end,flag,1);
   if(blend>0.0f)blendRemaining=blendDuration=BlendClamp(blend,(float)motion->frameCount()-1.0f);
   else blendRemaining=blendDuration=BlendClamp(5.0f,(float)motion->frameCount()-1.0f);
  }
 }else{
  lanes->rva000B3BCF(0,motion,mode,arg2,blend,start,end,flag,1);lanes->rva000B3C61(1);blendDuration=1.0f;blendRemaining=0.0f;
 }
 reinterpret_cast<Rva000B3BA8*>(this)->rva000B3BA8(render);
}
