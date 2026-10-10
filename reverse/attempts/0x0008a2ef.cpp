// ?rva0008A2EF@W3DView@@QAEXPBUV3@@PBUCameraGoalInfo@@H_NMM@Z
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /ICode /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "vector2.h"
#include "GameEngine/Source/GameClient/Rva000869CF.h"
struct V3 {float x,y,z; V3(){}  void sub(const V3&p){x-=p.x;y-=p.y;z-=p.z;} void add(const V3&p){x+=p.x;y+=p.y;z+=p.z;}};
class Rva00564E0D {public: Rva00564E0D &operator=(Rva00564E0D &other); V3 pos; AsciiString s;int v;};
struct CameraGoalInfo {char u00[8];V3 pos;int u14;int u18;float f1c;float f20;float f24;float f28;};
class Rva00089510 : public Rva000869CF {public:void rva00089510(bool orient,float firstAngle,int offset);};
class PathVirtual {public: virtual void s0();virtual void s1();virtual void init(int,int,float,float,int,int);};
class TerrainView {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual float ground(float,float,void*);};
extern TerrainView *TheTerrainLogic;
class Rva0030E7D0 {public:float rva0030E67C(float,float);};
class W3DView {public:
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
virtual void s28(bool);
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
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59(float,int,float,float);
virtual void s60(float,int,float,float);
virtual void s61(float,int,float,float);
virtual void s62(float,int,float,float);
virtual void s63();
virtual float s64();
virtual void s65();
virtual void s66();
virtual void s67();
virtual void s68();
virtual void s69();
virtual void s70();
virtual void s71();
virtual void s72();
virtual void s73();
virtual void s74();
virtual void s75();
virtual void s76();
virtual void s77();
virtual void s78();
virtual void s79();
virtual void s80();
virtual void s81();
virtual void s82();
virtual void s83();
virtual void s84();
virtual void s85();
virtual void s86();
virtual void s87();
virtual void s88();
virtual void s89();
virtual void s90();
virtual void s91();
virtual void s92();
virtual void s93();
virtual void s94();
virtual void s95();
virtual void s96();
virtual void s97();
virtual void s98();
virtual void s99();
virtual void s100();
virtual void s101();
virtual void s102();
virtual void s103();
virtual void s104();
virtual void s105();
virtual void s106();
virtual void s107();
virtual void s108();
virtual void s109();
virtual void s110();
virtual void s111();
virtual void s112();
virtual void s113();
virtual void s114();
virtual void s115();
virtual void s116();
virtual void s117();
virtual void s118();
virtual void s119();
virtual void s120();
virtual void s121();
virtual void s122();
virtual void s123();
virtual void s124();
virtual void s125();
virtual void s126();
virtual void s127();
virtual void s128();
virtual void s129();
virtual void s130();
virtual void s131();
virtual void s132();
virtual void s133();
virtual float s134(float);
void rva0008A2EF(const V3 *p,const CameraGoalInfo*info,int time,bool orient,float easeIn,float easeOut);
void rva00089C2D(int time,bool orient,float easeIn,float easeOut);
private: void moveAlongWaypointPath(int frames); public:
char pad04[8]; V3 position; char pad18[0x138-0x18];float f138;
char pad13c[0x284-0x13c];int time284;char pad288[0x2ac-0x288];
Rva00564E0D wp[259];
float angle[255];float segments[257];float totalDistance;int field1eec;union {int field1ef0;float ground1ef0;};
char pad1ef4[0x22f0-0x1ef4];int count22f0;
char pad22f4[0x2354-0x22f4];int mode2354;char pad2358[0x23d4-0x2358];int param23d4;char pad23d8[0x2408-0x23d8];int field2408;char pad240c[0x2458-0x240c];char sample[0x1c];bool customGround;
};
void W3DView::rva0008A2EF(const V3 *p,const CameraGoalInfo*info,int time,bool orient,float easeIn,float easeOut){
wp[256].pos=position; wp[1]=wp[256];segments[1]=0;
if(info){wp[257].pos=info->pos;wp[2]=wp[257];segments[2]=0;s59(info->f24,time,easeIn,easeOut);float height=s134(info->f28);s60(height,time,easeIn,easeOut);s61(info->f1c,time,easeIn,easeOut);s62(info->f20,time,easeIn,easeOut);}
else{if(!p)return;wp[257].pos=*p;wp[2]=wp[257];segments[2]=0;}
const V3 &a=wp[257].pos;const V3 &bb=wp[256].pos;V3 delta;delta.x=(a.x-bb.x);delta.y=(a.y-bb.y);delta.z=(a.z-bb.z);
V3 end(wp[256].pos);end.sub(delta);wp[255].pos=end;wp[0]=wp[255];
end=wp[257].pos;end.add(delta);wp[258].pos=end;wp[3]=wp[258];
count22f0=2;rva00089C2D(time,orient,easeIn,easeOut);
if(info){field1ef0=info->u14; *(int*)((char*)this+0x16f0)=info->u18;*(int*)((char*)this+0x16f4)=info->u18;}
if(time284==1){moveAlongWaypointPath(1);mode2354=1;f138=0;s28(false);}
}

void W3DView::rva00089C2D(int time,bool orient,float easeIn,float easeOut){
PathVirtual *path=reinterpret_cast<PathVirtual*>((char*)this+0x280);
path->init(param23d4,time,easeIn,easeOut,0,1);
totalDistance=0;
for(int i=1;i<count22f0;++i){const V3&a=wp[i].pos;const V3&bb=wp[i+1].pos;Vector2 dir(bb.x-a.x,bb.y-a.y);segments[i]=dir.Length();totalDistance+=segments[i];}
segments[0]=0;segments[count22f0]=0;segments[count22f0+1]=0;
reinterpret_cast<Rva00089510*>(path)->rva00089510((bool)orient,s64(),-1);
reinterpret_cast<Rva000869CF*>(path)->rva00086A94(0,0,s64());
angle[count22f0]=angle[count22f0-1];angle[count22f0+1]=angle[count22f0];
int i=count22f0-1;if(i>1){float*p=angle+i;int n=i-1;do{--n;float*q=p-1;*p=(*q+*p)*0.5f;p=q;}while(n);}
struct FinalPos{float x,y,z;FinalPos(const V3&p){x=p.x;y=p.y;z=p.z;}};FinalPos finalPos(wp[count22f0].pos);
field1eec=field2408;ground1ef0=TheTerrainLogic->ground(finalPos.x,finalPos.y,0);
if(customGround)ground1ef0=reinterpret_cast<Rva0030E7D0*>(sample)->rva0030E67C(finalPos.x,finalPos.y);
mode2354=count22f0>1;s28(false);*((bool*)this+0x1dc)=false;
}
