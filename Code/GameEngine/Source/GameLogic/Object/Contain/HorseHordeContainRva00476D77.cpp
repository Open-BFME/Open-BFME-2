#include "Lib/Coord3D.h"
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// ?rva00476D77@HorseHordeContain@@QAEXPAVObject@@PBUCoord3D@@M_N@Z @0x00476D77 647B
// Evidence: native 476D77..476FF7 RET16 HorseHordeContain motion dispatcher (between 47681F _horseUpdatePosition and HordeTransportContainModuleDataParse); WB1163200 caller/callee graph proves Horse family ABI; original method name unknown. Flag clear at +0x113 via TU-local byte-helper test(61)/clear(61) with barrier between (byte test/and, no lea); '==1' on the rva00469012 &&-operand gives retail cmp al,1. Callees 0x471464 (HordeContain::_updatePosition owner) and 0x47681F (WB-proven _horseUpdatePosition pin).
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <math.h>
class Object;class Thing;class Locomotor;class Path;
struct Rva0028AC4EEntry;class Rva001E3591 {public:bool rva001E3591();};class Rva00469012 {public:bool rva00469012(Object*,const Coord3D*);};class Rva0046AFDEReceiver {public:bool rva0046AFDE(Object*);};class HordeContain {public:void _updatePosition(Object*,const Coord3D*,float);};
struct Rva001E4194A;bool __stdcall Rva001E4194Get(Rva001E4194A*);
float normalizeAngle(float);
class Rva0008BB38FloatField {public:float get()const;};
struct Rva003642DFNode;
#include "../../../../Include/GameLogic/Rva003642DFResult.h"
#include "../../../../Include/GameLogic/PathfindPath.h"
enum CommandSourceType {COMMAND_SOURCE_2=2};
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
struct LocoTemplate {char pad[0x70];int appearance;};
#include "../../../../Include/GameLogic/LocomotorClass.h"
class Rva001E46E1
{
public:
	float rva001E4845(Object*);
	float rva001E46E1(Object*);
	bool rva001E543F(Object*);
};
#include "../../../Common/Thing/thing.h"
enum ObjectStatusTypes {STATUS_75=75};
enum KindOfType {KINDOF_0088=0x88};
struct FlagBytes{unsigned char w[8];
 unsigned char test(unsigned b)const{return (unsigned char)(w[b>>3]&(1<<(b&7)));}
 void clear(unsigned bit){w[bit>>3]=(unsigned char)(w[bit>>3]&~(1<<(bit&7)));}};
struct Rva00476D77Stun {char pad[0x5c];bool stunned;};
class Object {public:
const Rva0028AC4EEntry*rva0028AC4E()const;bool testStatus(ObjectStatusTypes)const;
void rva0028ACCA(int);void rva0028ACEE(int,int);void rva0028AE6D();int rva0028B511()const;bool isKindOf(KindOfType)const;
char pad00[0x38];Coord3D pos;float angle;char pad48[0x10C-0x48];FlagBytes flags10C;char pad114[0x11C-0x114];unsigned model11C;char pad120[0x198-0x120];Coord3D future;char pad1a4[2];bool futureValid;char pad1a7[0x258-0x1a7];AIUpdateInterface*ai;Rva00476D77Stun*stun;char pad260[0x438-0x260];unsigned char dead;
void nextPosition(const Coord3D*p){future=*p;futureValid=true;}
__forceinline void clear11C(unsigned mask){if(model11C&mask){model11C &=~mask;rva0028AE6D();}}
__forceinline void set11C(unsigned mask){if(!(model11C&mask)){model11C|=mask;rva0028AE6D();}}
};
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic*TheTerrainLogic;
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
 if(unitAI->rva00262D8F()){
  bool status=obj->testStatus(STATUS_75);
  if(!leaderAI->isMoving()||!status){
   if(unitAI->isMoving())unitAI->rva00262AEA();
   if(obj->flags10C.test(61)){_ReadWriteBarrier();obj->flags10C.clear(61);obj->rva0028AE6D();}unitAI->setLocomotorGoalNone();return;
  }
 }
 if(mode!=0){
  if(unitAI->m_field1FC==4 && unitAI->m_path && ((Rva001E3591*)unitAI->m_path)->rva001E3591()) {moving=true;return;}
  ((HordeContain*)this)->_updatePosition(obj,destination,angle);return;
 }
 if(unitAI->m_field1FC==4&&unitAI->m_path){moving=true;return;}
 if(!((Rva001E46E1*)horde->rva0028AC4E())->rva001E543F(horde)){
  float currentAngle=obj->angle;
  float turn=((const Locomotor*)obj->rva0028AC4E())->getMaxTurnRate(obj);
  float relative=normalizeAngle(angle-currentAngle);
  if(fabs(relative)>turn*0.5f){
   if(relative>turn)relative=turn;
   else if(relative < -turn)relative=-turn;
   unitAI->setLocomotorGoalOrientation(currentAngle+relative);moving=true;return;
  }
 }
 if(!force&&!state121&&((Rva00469012*)this)->rva00469012(obj,destination)==1&&flag1a4==0&&(leaderAI->isMoving()||((Rva0046AFDEReceiver*)this)->rva0046AFDE(obj))){
  if(unitAI->isMoving())unitAI->rva00262AEA();if(obj->flags10C.test(61)){_ReadWriteBarrier();obj->flags10C.clear(61);obj->rva0028AE6D();}unitAI->setLocomotorGoalNone();moving=true;return;
 }
 Coord3D goal;goal.x=destination->x;goal.y=destination->y;goal.z=destination->z;
 TheAI->m_pathfinder->rva002EF3EE(obj,&goal,horde,!force);
 _horseUpdatePosition(obj,&goal,angle);
}
