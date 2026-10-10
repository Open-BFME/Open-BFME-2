// ?rva002CBBF5@WeaponTemplate@@QAEXPAVObject@@HHH0HPBUCoord3D@@H_NPAVWeapon@@H@Z
// partial score=0.665828 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /ICode/GameEngine/Source
// Retail2CBBF5..2CC20E RET44. WB BB0E40 independently names this
// WeaponTemplate::fireWeaponTemplate. ZH Weapon.cpp is the primary semantic
// guide, with retail-specific eleven-word ABI and nugget dispatch. Unknown
// original type/name spellings for unused arguments remain neutral words.
#include "Lib/Coord3D.h"
#include "Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Object;class Player;class FXList;class Drawable;
extern "C" float atan2f(float,float);
float GetGameLogicRandomValueReal(float,float,char*,int);
class Drawable {public:bool handleWeaponFireFX(int,int,int,float,float,float,int);};
struct WeaponObjectTemplate{char pad[0x108];unsigned char kind[28];};
class WeaponAI {public:
virtual void s000();
virtual void s004();
virtual void s008();
virtual void s00C();
virtual void s010();
virtual void s014();
virtual void s018();
virtual void s01C();
virtual void s020();
virtual void s024();
virtual void s028();
virtual void s02C();
virtual void s030();
virtual void s034();
virtual void s038();
virtual void s03C();
virtual void s040();
virtual void s044();
virtual void s048();
virtual void s04C();
virtual void s050();
virtual void s054();
virtual void s058();
virtual void s05C();
virtual void s060();
virtual void s064();
virtual void s068();
virtual void s06C();
virtual void s070();
virtual void s074();
virtual void s078();
virtual void s07C();
virtual void s080();
virtual void s084();
virtual void s088();
virtual void s08C();
virtual void s090();
virtual void s094();
virtual void s098();
virtual void s09C();
virtual void s0A0();
virtual void s0A4();
virtual void s0A8();
virtual void s0AC();
virtual void s0B0();
virtual void s0B4();
virtual void s0B8();
virtual void s0BC();
virtual void s0C0();
virtual void s0C4();
virtual void s0C8();
virtual void s0CC();
virtual void s0D0();
virtual void s0D4();
virtual void s0D8();
virtual void s0DC();
virtual void s0E0();
virtual void s0E4();
virtual void s0E8();
virtual void s0EC();
virtual void s0F0();
virtual void s0F4();
virtual void s0F8();
virtual void s0FC();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10C();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11C();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12C();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13C();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14C();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15C();
virtual void s160();
virtual void s164();
virtual void s168();
virtual void s16C();
virtual void s170();
virtual void s174();
virtual void s178();
virtual void s17C();
virtual void s180();
virtual int s184();
virtual void s188();
virtual void s18C();
virtual void s190();
virtual void s194();
virtual void s198();
virtual void s19C();
virtual void s1A0();
virtual void s1A4();
virtual void s1A8();
virtual void s1AC();
virtual void s1B0();
virtual void s1B4();
virtual void s1B8();
virtual void s1BC();
virtual void s1C0();
virtual void s1C4();
virtual void s1C8();
virtual void s1CC();
virtual void s1D0();
virtual void s1D4();
virtual void s1D8();
virtual void s1DC();
virtual void s1E0();
virtual void s1E4();
virtual void s1E8();
virtual void s1EC();
virtual void s1F0();
virtual void s1F4();
virtual void s1F8();
virtual void s1FC();
virtual bool s200(Coord3D*);
};
class WeaponBody {public:
virtual void s000();
virtual void s004();
virtual void s008();
virtual void s00C();
virtual void s010();
virtual void s014();
virtual void s018();
virtual void s01C();
virtual void s020();
virtual void s024();
virtual void s028();
virtual void s02C();
virtual void s030();
virtual void s034();
virtual void s038();
virtual void s03C();
virtual void s040();
virtual void s044();
virtual void s048();
virtual void s04C();
virtual void s050();
virtual void s054();
virtual void s058();
virtual void s05C();
virtual void s060();
virtual void s064();
virtual void s068();
virtual void s06C();
virtual void s070();
virtual void s074();
virtual void s078();
virtual void s07C();
virtual void s080();
virtual void s084();
virtual void s088();
virtual float s8C();
};
class WeaponContain {public:
virtual void s000();
virtual void s004();
virtual void s008();
virtual void s00C();
virtual void s010();
virtual void s014();
virtual void s018();
virtual void s01C();
virtual void s020();
virtual void s024();
virtual void s028();
virtual void s02C();
virtual void s030();
virtual void s034();
virtual void s038();
virtual void s03C();
virtual void s040();
virtual void s044();
virtual void s048();
virtual void s04C();
virtual void s050();
virtual void s054();
virtual void s058();
virtual void s05C();
virtual void s060();
virtual void s064();
virtual void s068();
virtual void s06C();
virtual void s070();
virtual void s074();
virtual void s078();
virtual int s7C();
virtual void s080();
virtual void s084();
virtual void s088();
virtual void s08C();
virtual void s090();
virtual void s094();
virtual void s098();
virtual void s09C();
virtual void s0A0();
virtual void s0A4();
virtual void s0A8();
virtual void s0AC();
virtual void s0B0();
virtual void s0B4();
virtual void s0B8();
virtual void s0BC();
virtual void s0C0();
virtual void s0C4();
virtual void s0C8();
virtual void s0CC();
virtual void s0D0();
virtual void s0D4();
virtual void s0D8();
virtual void s0DC();
virtual void s0E0();
virtual void s0E4();
virtual void s0E8();
virtual void s0EC();
virtual void s0F0();
virtual Object *sF4();
};
class Object {public:
 float rva002C97E8(const Coord3D*,const Coord3D*)const;float rva00263763(const void*)const;
 bool rva0028F44C(const Object*)const;bool isLocallyControlled()const;bool rva002943B2(const Player*);
 char pad00[4];WeaponObjectTemplate *data;char pad08[0x38-8];Coord3D pos;
 char pad44[0x74-0x44];int id74;char pad78[0x250-0x78];WeaponContain *contain250;WeaponBody *body254;WeaponAI *ai258;
};
class Thing {public:Drawable *getDrawable()const;};
struct TBridgeAttackInfo{Coord3D point1,point2;};
class TerrainLogic {public:void getBridgeAttackPoints(const Object*,TBridgeAttackInfo*);};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {public:bool IsPointOnWall(int,bool);};
class AI{public:char pad[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
class Rva002C9B80Owner {public:float rva002C9B80(void*,float);bool isWithinAttackRange(Object*,const Coord3D*,Object*,const Coord3D*,float,bool);};
class Weapon {public:char pad[0x30];unsigned fxUntil;char pad34[0x50-0x34];unsigned rangeUntil;};
class FXList {public:static void doFXObj(const FXList*,const Object*,const Object*);};
class WeaponNugget {public:
virtual void s000();
virtual bool s04(Weapon*,Object*);
virtual bool s08(Weapon*,const Coord3D*);
virtual void s00C();
virtual void s010();
virtual void s14(Weapon*,Object*);
virtual void s18(Weapon*,const Coord3D*);
virtual void s01C();
virtual void s020();
virtual void s024();
virtual void s028();
virtual void s02C();
virtual bool s30();
};
struct WeaponNuggetNode{WeaponNuggetNode *next,*prev;WeaponNugget *nugget;};
class WeaponTemplate {public:
 void rva002CBBF5(Object*,int,int,int,Object*,int,const Coord3D*,int,bool,Weapon*,int);
 float getMinimumAttackRange()const;
 Coord3D *getAimPosition(Coord3D*,const Object*,const Object*,int);
 Coord3D bfmeCalcScatterTargetPos(const Object*,const Object*,Coord3D);
 char pad00[0x3C];bool eachNugget3C,wall3D;char pad3E[0x68-0x3E];float sound68;
 char pad6C[0x75-0x6C];bool dodge75;char pad76[0x84-0x76];float pitch84;
 char pad88[0xA4-0x88];FXList *fxA4;char padA8[0xB4-0xA8];FXList *fxB4;
 char padB8[0x11C-0xB8];bool self11C;char pad11D[0x135-0x11D];bool localFX135;
 char pad136[0x14C-0x136];float infantry14C;char pad150[8];float chance158,chance15C;
 char pad160[0x17C-0x160];WeaponNuggetNode *nuggets;
};
void WeaponTemplate::rva002CBBF5(Object *source,int wordC,int barrel,int word14,Object *victim,int word1C,const Coord3D *position,int word24,bool ignore,Weapon *weapon,int word30)
{
 if(!source||(!victim&&!position))return;
 float distance;
 Coord3D shifted;TBridgeAttackInfo bridge;
 if(victim){
  position=&victim->pos;
  Coord3D offset;
  if(victim->ai258&&victim->ai258->s200(&offset)){
   shifted=*position;
   shifted.x+=offset.x;shifted.y+=offset.y;shifted.z+=offset.z;
   position=&shifted;victim=0;
   distance=source->rva002C97E8(&source->pos,position);
  }else if(victim->data->kind[2]&0x40){
   TheTerrainLogic->getBridgeAttackPoints(victim,&bridge);
   distance=source->rva002C97E8(&source->pos,&bridge.point1);
   float other=source->rva002C97E8(&source->pos,&bridge.point2);
   if(other<distance){distance=other;position=&bridge.point2;}
  }else distance=source->rva00263763(victim);
 }else distance=source->rva002C97E8(&source->pos,position);
 if(!ignore&&weapon->rangeUntil<=TheGameLogic->getFrame()){
  float range=((Rva002C9B80Owner*)weapon)->rva002C9B80(source,position->z-source->pos.z);
  if(distance>range*range&&!((Rva002C9B80Owner*)weapon)->isWithinAttackRange(source,&source->pos,victim,position,0.f,true))return;
  float minimum=getMinimumAttackRange();
  if(distance<minimum*minimum)return;
 }
 if(((const Thing*)source)->getDrawable()){
  Coord3D firePosition;
  if(victim){Coord3D adjusted;firePosition=*getAimPosition(&adjusted,source,victim,1);}
  else {firePosition.x=position->x;firePosition.y=position->y;firePosition.z=position->z;}
  float pitch=pitch84;
  float heading=pitch==0.f?0.f:atan2f(position->y-source->pos.y,position->x-source->pos.x);
  FXList *fx=0;
  if(victim&&victim->rva0028F44C(source))fx=fxB4;
  if(!fx)fx=fxA4;
  if(TheGameLogic->getFrame()<weapon->fxUntil)fx=0;
  if(source->isLocallyControlled()||!source->rva002943B2(0)||localFX135){
   if(!((const Thing*)source)->getDrawable()->handleWeaponFireFX(barrel,word14,(int)fx,sound68,pitch,heading,(int)&firePosition)&&fx)FXList::doFXObj(fx,source,victim);
  }
 }
 float oldZ=position->z;
 if(self11C){position=&source->pos;victim=0;}
 const Coord3D *aim=position?position:&victim->pos;
 Coord3D target;target.x=aim->x;target.y=aim->y;target.z=aim->z;
 if(self11C&&source->ai258->s184())target.z=oldZ;
 bool scatter=false;
 if(infantry14C>0.f&&victim&&(victim->data->kind[1]&1)&&(!wall3D||!TheAI->pathfinder->IsPointOnWall((int)&victim->pos,false)))scatter=true;
 char *filename="C:\\Projects\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp";
 if(chance158<1.f){float chance=chance158;if(GetGameLogicRandomValueReal(0,1,filename,0x5D1)>=chance)scatter=true;}
 if(dodge75&&victim&&victim->body254->s8C()>0.f){
  float random=GetGameLogicRandomValueReal(0,1,filename,0x5D7);
  if(victim->body254->s8C()>=random)scatter=true;
 }
 bool useContained=false;
 if(!scatter&&victim&&victim->contain250&&!victim->contain250->s7C()&&chance15C>0.f){
  float chance=chance15C;
  if(chance>=GetGameLogicRandomValueReal(0,1,filename,0x5E1)){useContained=true;scatter=false;}
 }
 if(eachNugget3C){
  for(WeaponNuggetNode *it=nuggets->next;it!=nuggets;it=it->next){
   WeaponNugget *nugget=it->nugget;
   if(scatter){target=bfmeCalcScatterTargetPos(source,victim,target);victim=0;}
   if(nugget->s08(weapon,&target))nugget->s18(weapon,&target);
  }
 }else{
  if(scatter){target=bfmeCalcScatterTargetPos(source,victim,target);victim=0;}
  else if(useContained&&victim->contain250){Object *inside=victim->contain250->sF4();if(inside)victim=inside;}
  for(WeaponNuggetNode *it=nuggets->next;it!=nuggets;it=it->next){
   WeaponNugget *nugget=it->nugget;
   if(victim&&!nugget->s30()){if(nugget->s04(weapon,victim))nugget->s14(weapon,victim);}
   else if(nugget->s08(weapon,&target))nugget->s18(weapon,&target);
  }
 }
}
