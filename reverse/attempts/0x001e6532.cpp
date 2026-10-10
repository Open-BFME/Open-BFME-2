// ?rva001E6532@Rva001E46E1@@QAEMPAVObject@@PBUCoord3D@@M@Z
// partial score=0.9358291267987644 date=2026-10-10
// ?rva001E6532@Rva001E46E1@@QAEMPAVObject@@PBUCoord3D@@M@Z
// partial score=0.9101746199006473 date=2026-10-10
// ?rva001E6532@Rva001E46E1@@QAEMPAVObject@@PBUCoord3D@@M@Z
// Native 001E6532..001E6731 RET12; sole caller 001E7ECA at 001E836E
// passes Object, goal Coord3D and terrain surface height on the Locomotor.
// BF1 575ba2b04/ZH Locomotor height code supplies subsystem context only:
// this weapon/three-state height selection is established from target bytes.
// Original method/field/type names remain unresolved; descriptive names below
// express observed accesses. Data+64 is a distance range, receiver+48/+4C
// heights and +9C dispatches three states. Object+258 query slot111 and its
// owned getCurrentWeapon/getStatus calls are target facts; original query name
// is unknown. Model condition bit122 is directly observed.
// Actual complete510B versus native511B. Native preload/coordinate construction,
// frame1C, reference clamp homes and Boolean flag extraction reproduced.
// Remaining: state2 range reused in XMM0 rather than native memory DIVSS via EDX.
// Round8 removing the old fence closes EDX/ESI pointer and switch register roles.
extern "C" void 
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
#include <math.h>
#include "Coord3D.h"
inline __declspec(noinline) float Coord3D::length() const {return (float)sqrt(x*x+y*y+z*z);}
__forceinline const float& minRef(const float&a,const float&b){return a>b?b:a;}
struct PointDiff:Coord3D{PointDiff(){}PointDiff(float a,float b,float c){x=a;y=b;z=c;}PointDiff(const Coord3D&r){x=r.x;y=r.y;z=r.z;}PointDiff operator-(const PointDiff&r)const{return PointDiff(x-r.x,y-r.y,z-r.z);}};
struct MemberwisePoint:Coord3D{MemberwisePoint(){}MemberwisePoint(const Coord3D&r){x=r.x;y=r.y;z=r.z;}};
struct ModelFlags {unsigned words[20];unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}void set(int bit){words[bit>>5]|=1U<<(bit&31);}};
struct LocoHeightData {char pad[0x64];float range64;};
enum WeaponSlotType{WEAPONSLOT0=0};enum WeaponStatus{WEAPONSTATUS0=0};
class Weapon{public:WeaponStatus getStatus()const;};
class LocoHeightAI{public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual bool query111();
};
class Object{public:const Weapon*getCurrentWeapon(WeaponSlotType*)const;void rva0028AE6D();char pad00[0x38];Coord3D pos38;char pad44[0xC8];ModelFlags model10C;char pad15C[0xFC];LocoHeightAI*ai258;char pad25C[0x1DC];unsigned char flags438;};
class Rva001E46E1{public:float rva001E6532(Object*,const Coord3D*,float);char pad00[4];LocoHeightData*data4;char pad08[0x3C];unsigned flags44;float height48,min4C;char pad50[0x4C];int state9C;};
float Rva001E46E1::rva001E6532(Object*obj,const Coord3D*goal,float surface){
 if(min4C>0){
 LocoHeightAI*ai=obj->ai258;
 if(ai){
  PointDiff goalPoint(*goal);PointDiff pos(obj->pos38);PointDiff delta=goalPoint-pos;delta.z=0;float z=pos.z;float distance=delta.length();float above=z-surface;
  const Weapon*weapon=obj->getCurrentWeapon(0);
  if(obj->flags438&1){
   if(above<=0 && !obj->model10C.test(122)){obj->model10C.set(122);obj->rva0028AE6D();}
   return 0;
  }
  int zero=0;
  if(weapon!=(const Weapon*)zero && data4->range64>0){
   switch(state9C){
   case 0:if(!((bool)((flags44>>2)&1)) && data4->range64>distance && ai->query111())state9C=1;break;
   case 1:{float ratio=distance/data4->range64;float one=1;float dh=height48-min4C;float height=min4C+dh*minRef(ratio,one);
    if(weapon->getStatus()!=WEAPONSTATUS0 || !ai->query111())state9C=2;
    return height;}
   case 2:{float ratio=(distance/data4->range64)*2;float one=1;float dh=height48-min4C;float height=min4C+dh*minRef(ratio,one);
    if(above>=height48)state9C=zero;return height;}
   }
  }else state9C=zero;
 }
 }
 return height48;
}
