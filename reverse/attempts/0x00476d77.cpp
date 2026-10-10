// ?rva00476D77@HorseHordeContain@@QAEXPAVObject@@PBUCoord3D@@M_N@Z
// partial score=0.9672458745 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
#include "Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <math.h>
class Object;class Thing;class Locomotor;class Path;
struct Rva0028AC4EEntry;class Rva001E3591 {public:bool rva001E3591();};class Rva00469012 {public:bool rva00469012(Object*,const Coord3D*);};class Rva0046AFDEReceiver {public:bool rva0046AFDE(Object*);};class Rva00471464 {public:void rva00471464(Object*,const Coord3D*,float);};struct Rva0046E6EAObject;struct Rva0046E6EACoord;class Rva002EF3EEView {public:bool rva002EF3EE(Rva0046E6EAObject*,const Rva0046E6EACoord*,Rva0046E6EACoord*,bool);};
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
void rva00262AEA();int rva00260DED()const;bool isMoving()const;void setPathExtraDistance(float);
char pad04[0x140-4];Path*path;char pad144[0x1dc-0x144];int movementType;char pad1e0[0x1f0-0x1e0];Locomotor*loco;char pad1f4[8];int goalType;
AICommandInterface*command(){return (AICommandInterface*)((char*)this+0x20);}
};
struct LocoTemplate {char pad[0x70];int appearance;};
class Locomotor {public:float getMaxTurnRate(Object*)const;char pad[4];const LocoTemplate*data;};
class Rva001E46E1 {public:bool rva001E543F(Object*);float rva001E4845(Object*);float rva001E46E1(Object*);};
class View {public:virtual void setHeightAboveGround(float);};
class Thing {public:void setPosition(const Coord3D*);};
enum ObjectStatusTypes {STATUS_75=75};
enum KindOfType {KINDOF_0088=0x88};
struct Rva00476D77Stun {char pad[0x5c];bool stunned;};
class Object {public:
const Rva0028AC4EEntry*rva0028AC4E()const;bool testStatus(ObjectStatusTypes)const;
void rva0028ACCA(int);void rva0028ACEE(int,int);void rva0028AE6D();int rva0028B511()const;bool isKindOf(KindOfType)const;
char pad00[0x38];Coord3D pos;float angle;char pad48[0x110-0x48];unsigned model110;char pad114[8];unsigned model11C;char pad120[0x198-0x120];Coord3D future;char pad1a4[2];bool futureValid;char pad1a7[0x258-0x1a7];AIUpdateInterface*ai;Rva00476D77Stun*stun;char pad260[0x438-0x260];unsigned char dead;
void nextPosition(const Coord3D*p){future=*p;futureValid=true;}
__forceinline void clear110(unsigned mask){unsigned char &b=((unsigned char*)&model110)[3];if(b&0x20){b &=0xdf;rva0028AE6D();}}
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
void rva00476D77(Object*,const Coord3D*,float,bool);
char pad00[8];Object*owner;char pad0c[0x120-0xc];bool moving;bool state121;char pad122[0x1a4-0x122];unsigned flag1a4;char pad1a8[0x2a0-0x1a8];int mode;
};

void HorseHordeContain::rva00476D77(Object*obj,const Coord3D*destination,float angle,bool force)
{
 Object*horde=owner;
 AIUpdateInterface*leaderAI=horde->ai;
 AIUpdateInterface*unitAI=obj->ai;
 if(obj->stun&&obj->stun->stunned)return;
 if(obj->dead&1)return;
 if(!leaderAI||!unitAI)return;
 if(unitAI->s1BC()){
  bool status=obj->testStatus(STATUS_75);
  if(!leaderAI->isMoving()||!status){
   if(unitAI->isMoving())unitAI->rva00262AEA();
   obj->clear110(0x20000000);unitAI->s220();return;
  }
 }
 if(mode!=0){
  if(unitAI->goalType==4 && unitAI->path && ((Rva001E3591*)unitAI->path)->rva001E3591()) {moving=true;return;}
  ((Rva00471464*)this)->rva00471464(obj,destination,angle);return;
 }
 if(unitAI->goalType==4&&unitAI->path){moving=true;return;}
 if(!((Rva001E46E1*)horde->rva0028AC4E())->rva001E543F(horde)){
  float currentAngle=obj->angle;
  float turn=((const Locomotor*)obj->rva0028AC4E())->getMaxTurnRate(obj);
  float relative=normalizeAngle(angle-currentAngle);
  if(fabs(relative)>turn*0.5f){
   if(relative>turn)relative=turn;
   else if(relative < -turn)relative=-turn;
   unitAI->s21C(currentAngle+relative);moving=true;return;
  }
 }
 if(!force&&!state121&&((Rva00469012*)this)->rva00469012(obj,destination)&&flag1a4==0&&(leaderAI->isMoving()||((Rva0046AFDEReceiver*)this)->rva0046AFDE(obj))){
  if(unitAI->isMoving())unitAI->rva00262AEA();obj->clear110(0x20000000);unitAI->s220();moving=true;return;
 }
 Coord3D goal;goal.x=destination->x;goal.y=destination->y;goal.z=destination->z;
 ((Rva002EF3EEView*)TheAI->pathfinder)->rva002EF3EE((Rva0046E6EAObject*)obj,(const Rva0046E6EACoord*)&goal,(Rva0046E6EACoord*)horde,!force);
 _horseUpdatePosition(obj,&goal,angle);
}
