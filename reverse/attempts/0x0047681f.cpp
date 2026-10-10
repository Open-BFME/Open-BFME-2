// ?_horseUpdatePosition@HorseHordeContain@@QAEXPAVObject@@PBUCoord3D@@M@Z
// partial score=0.8029213121 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include <math.h>
class Object;class Thing;class Locomotor;class Path;
struct Rva001E4194A;bool __stdcall Rva001E4194Get(Rva001E4194A*);
float normalizeAngle(float);
class Rva0008BB38FloatField {public:float get()const;};
class Rva00363D20 {public:double rva00363D20();};
struct Rva003642DFNode;
struct Rva003642DFResult {Rva003642DFNode*m_node;Coord3D m_pos;};
class Path {public:Rva003642DFResult rva00364521(const Rva0008BB38FloatField*);};
enum CommandSourceType {COMMAND_SOURCE_2=2};
class AICommandInterface {public:void aiIdle(CommandSourceType);void rva0045003E(int,CommandSourceType);};
class AIUpdateInterface {public:
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
virtual void s184();
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
virtual bool s1B8();
virtual bool s1BC();
virtual void s1C0();
virtual bool s1C4();
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
virtual void s200();
virtual void s204();
virtual void s208();
virtual void s20C();
virtual void s210();
virtual void s214(const Coord3D*);
virtual void s218();
virtual void s21C(float);
virtual void s220();
int rva00260DED()const;bool isMoving()const;void setPathExtraDistance(float);
char pad04[0x140-4];Path*path;char pad144[0x1dc-0x144];int movementType;char pad1e0[0x1f0-0x1e0];Locomotor*loco;
AICommandInterface*command(){return (AICommandInterface*)((char*)this+0x20);}
};
struct LocoTemplate {char pad[0x70];int appearance;};
class Locomotor {public:char pad[4];const LocoTemplate*data;};
class Rva001E46E1 {public:float rva001E4845(Object*);float rva001E46E1(Object*);};
class View {public:virtual void setHeightAboveGround(float);};
class Thing {public:void setPosition(const Coord3D*);};
enum KindOfType {KINDOF_0088=0x88};
class Object {public:
void rva0028ACCA(int);void rva0028ACEE(int,int);void rva0028AE6D();int rva0028B511()const;bool isKindOf(KindOfType)const;
char pad00[0x38];Coord3D pos;float angle;char pad48[0x110-0x48];unsigned model110;char pad114[8];unsigned model11C;char pad120[0x198-0x120];Coord3D future;char pad1a4[2];bool futureValid;char pad1a7[0x258-0x1a7];AIUpdateInterface*ai;
void nextPosition(const Coord3D*p){future=*p;futureValid=true;}
__forceinline void clear110(unsigned mask){if(model110&mask){model110 &=~mask;rva0028AE6D();}}
__forceinline void set110(unsigned mask){if(!(model110&mask)){model110|=mask;rva0028AE6D();}}
__forceinline void clear11C(unsigned mask){if(model11C&mask){model11C &=~mask;rva0028AE6D();}}
__forceinline void set11C(unsigned mask){if(!(model11C&mask)){model11C|=mask;rva0028AE6D();}}
};
class Pathfinder {public:bool IsValidMovementPositionForObject(const Coord3D*,int,int,const Object*);};
class AI {public:char pad[0x10];Pathfinder*pathfinder;};extern AI*TheAI;
class TerrainLogic {public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual float s1C(float,float,int,Coord3D*,bool);
};extern TerrainLogic*TheTerrainLogic;
class HorseHordeContain {public:
void _horseUpdatePosition(Object*,const Coord3D*,float);
char pad00[8];Object*owner;char pad0c[0x120-0xc];bool moving;bool state121;char pad122[0x2a0-0x122];int mode;
};
void HorseHordeContain::_horseUpdatePosition(Object*obj,const Coord3D*destination,float angle)
{
 Object *horde=owner;
 Coord3D goal;goal.x=destination->x;goal.y=destination->y;goal.z=destination->z;
 Coord3D current;current.x=obj->pos.x;current.y=obj->pos.y;current.z=obj->pos.z;
 AIUpdateInterface*leaderAI=horde->ai;
 AIUpdateInterface*unitAI=obj->ai;
 if(!leaderAI||!unitAI)return;
 if(leaderAI->rva00260DED()==7)state121=true;
 Locomotor*unitLoco=unitAI->loco;Locomotor*leaderLoco=leaderAI->loco;
 if(!unitLoco||!leaderLoco)return;
 if(Rva001E4194Get((Rva001E4194A*)obj)){obj->clear110(0x20000000);return;}
 Coord3D delta;delta.x=goal.x-current.x;delta.y=goal.y-current.y;delta.z=0;
 float distance=delta.length();
 float extendedDistance=distance;
 if(leaderAI->path){
  Rva003642DFResult result=leaderAI->path->rva00364521((const Rva0008BB38FloatField*)leaderAI->loco);
  extendedDistance+=((Rva00363D20*)&result)->rva00363D20();
  extendedDistance-=((const Rva0008BB38FloatField*)leaderLoco)->get();
 }
 bool shouldIdle=false,shouldSpecial=false;
 if(mode==0){
  if(!(unitAI->s1BC()&&leaderAI->s1BC())&&(leaderAI->isMoving()||unitAI->s1B8())){
   if(leaderAI->s1BC())shouldIdle=true;else shouldSpecial=true;
  }
 }else shouldIdle=true;
 if(shouldIdle&&!unitAI->s1B8()&&!unitAI->s1BC())unitAI->command()->aiIdle(COMMAND_SOURCE_2);
 if(shouldSpecial&&!unitAI->s1C4())unitAI->command()->rva0045003E(0,COMMAND_SOURCE_2);
 float closeDistance=((Rva001E46E1*)unitLoco)->rva001E4845(obj);
 float maxSpeed=((Rva001E46E1*)unitLoco)->rva001E46E1(obj);
 if(closeDistance>maxSpeed*0.2f)closeDistance=maxSpeed*0.2f;
 obj->rva0028ACCA((int)&goal);
 if(closeDistance>distance){
  Coord3D desired;desired.x=goal.x;desired.y=goal.y;desired.z=goal.z;
  if(unitLoco->data->appearance!=8){
   desired.z=current.z;
   if(TheAI->pathfinder->IsValidMovementPositionForObject(&desired,obj->rva0028B511(),unitAI->movementType,owner))
    desired.z=TheTerrainLogic->s1C(desired.x,desired.y,obj->rva0028B511(),0,true);
  }
  float relative=normalizeAngle((double)angle-obj->angle);
  if(mode==0 && fabs(relative)>0.17453294f){unitAI->s21C(angle);moving=true;return;}
  obj->clear110(0x20000000);
  unitAI->s220();
  if(leaderAI->isMoving()){moving=true;return;}
  ((Thing*)obj)->setPosition(&desired);
  obj->nextPosition(&desired);
  obj->rva0028ACEE((int)&obj->pos,obj->rva0028B511());
  obj->clear11C(0x100);
 }else{
  float speed=((const Rva0008BB38FloatField*)unitLoco)->get();
  closeDistance=((Rva001E46E1*)unitLoco)->rva001E4845(obj);
  if(speed==0.0f&&closeDistance>distance)return;
  Coord3D desired;desired.x=goal.x;desired.y=goal.y;desired.z=goal.z;
  moving=true;
  unitAI->s214(&desired);
  unitAI->setPathExtraDistance(extendedDistance);
  ((View*)unitAI)->View::setHeightAboveGround(distance);
  obj->set110(0x20000000);
  obj->clear11C(0x80);
  bool special=false;
  if(obj->isKindOf(KINDOF_0088)&&((horde->model11C&0x100)||!leaderAI->isMoving()))special=true;
  float fastSpeed=maxSpeed*0.66f;
  (void)fabs(distance-speed);
  if(distance>speed&&fastSpeed>speed){obj->clear11C(0x100);}
  else if(speed>distance&&fastSpeed>speed){
   obj->clear11C(0x80);
   if((horde->model11C&0x100)||!leaderAI->isMoving())obj->set11C(0x100);else obj->clear11C(0x100);
  }else{obj->clear11C(0x80);obj->clear11C(0x100);}
  if(special&&speed>0.0f)obj->set11C(0x100);
 }
}
