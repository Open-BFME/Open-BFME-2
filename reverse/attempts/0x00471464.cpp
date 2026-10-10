// ?rva00471464@Rva00471464@@QAEXPAVObject@@PBUCoord3D@@M@Z
// partial score=0.7790062185 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// Native 471464..471FFA / 2966B / RET12; WB10B9A60 names HordeContain::_updatePosition.
// The existing Rva00471464 pin and native Horse caller476D77 independently establish the primary-object ABI.
// Standalone complete reconstruction; all accessed layouts/slots come from native, not WB helper-name guesses.
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
virtual void s210(const Coord3D*);
virtual void s214(const Coord3D*);
virtual void s218();
virtual void s21C(float);
virtual void s220();
virtual void s224();
virtual void s228();
virtual void s22C();
virtual void s230();
virtual void s234();
virtual bool s238();
protected:void wakeUpNow();friend class Rva00471464;public:void rva00262AEA();int rva00260DED()const;bool isMoving()const;void setPathExtraDistance(float);
char pad04[0x140-4];Path*path;char pad144[0x1dc-0x144];int movementType;char pad1e0[0x1f0-0x1e0];Locomotor*loco;char pad1f4[8];int goalType;
AICommandInterface*command(){return (AICommandInterface*)((char*)this+0x20);}
};
struct LocoTemplate {char pad[0x70];int appearance;};
class Locomotor {public:float getMaxTurnRate(Object*)const;char pad[4];const LocoTemplate*data;};
class Rva001E46E1 {public:float rva001E4845(Object*);float rva001E46E1(Object*);};
class Drawable {public:void rva00272A02(bool);};
class Rva00373EC6 {public:char pad[0x3C];int state;};
class StealthUpdate {public:void markAsDetected(unsigned,int,Object*,bool);};
class Thing {public:void setPosition(const Coord3D*);void setOrientation(float);const Coord3D*getUnitDirectionVector2D()const;Drawable*getDrawable()const;};
class Rva0030A92C {public:void rva0030A92C(float);};
class Rva001E4912 {public:Rva001E4912*rva001E4912(int,unsigned,unsigned);unsigned bits[19];};
class Rva001E42F2 {public:void rva001E42F2(const int*);};
class Rva001E431E {public:void rva001E431E(const int*);};
struct Rva0028F59A {unsigned bits[19];Rva0028F59A(int,int);};
struct FlagBytes {unsigned char words[8];unsigned char test(unsigned bit)const{return (unsigned char)(words[bit>>3]&(1u<<(bit&7)));}void clear(unsigned bit){words[bit>>3]&=~(1u<<(bit&7));}void set(unsigned bit){words[bit>>3]|=(1u<<(bit&7));}};
struct Rva00471464Template {char pad[0x109];unsigned char flags109;};
class Object {public:
 void rva0028AD22();void rva0028AE6D();void rva0028ACCA(int);void rva0028ACEE(int,int);int rva0028B511()const;
 Rva00373EC6*rva0028F4BC();bool isLocallyControlled()const;
 char pad00[4];Rva00471464Template*data;char pad08[0x38-8];Coord3D pos;float angle;char pad48[0x74-0x48];int id;char pad78[0x110-0x78];union {FlagBytes flags110;unsigned word110;};unsigned model118;char pad11C[0x140-0x11C];unsigned status140;char pad144[0x198-0x144];Coord3D future;char pad1A4[2];bool futureValid;char pad1A7[0x258-0x1A7];AIUpdateInterface*ai;
 void nextPosition(const Coord3D*p){future=*p;futureValid=true;}
};
enum Relationship {RELATIONSHIP_ZERO=0};
class Player {public:Relationship getRelationship(const Object*)const;};
class PlayerList {public:char pad[0x10];Player*local;};extern PlayerList*ThePlayerList;
class GameLogic {public:Object*findObjectByID(int);};extern GameLogic*TheGameLogic;
class Eva {public:void reportEvaEvent(int,const Coord3D*,int);};extern Eva*TheEva;
bool __stdcall Rva002EE49BSameCell(void*,Coord3D,Coord3D);
class Pathfinder {public:int CountOverlapHordeGoalUnits(Object*,const Coord3D*);bool rva002EE64A(Object*,const Coord3D*,const Coord3D*);bool IsValidMovementPositionForObject(const Coord3D*,int,int,const Object*);void*rva001E4461(int,int);};
class AI {public:char pad[0x10];Pathfinder*pathfinder;};extern AI*TheAI;
class TerrainLogic {public:virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual float s18(float,float,bool);virtual float s1C(float,float,int,Coord3D*,bool);};extern TerrainLogic*TheTerrainLogic;
class Rva0046ACF6 {public:int rva0046ACF6(int);};
class Rva00471464Controller {public:virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual bool s1C(int);virtual bool s20(int);virtual bool s24(int);virtual void s28(int);virtual void s2C(int);};
class Rva00471464Iface {public:
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
virtual bool s0F0();
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
virtual void s200();
virtual void s204();
virtual void s208();
virtual void s20C();
virtual void s210();
virtual void s214();
virtual void s218();
virtual void s21C();
virtual void s220();
virtual void s224();
virtual void s228();
virtual void s22C();
virtual void s230();
virtual void s234();
virtual bool s238();
};
class Rva00471464 {public:
void rva00471464(Object*,const Coord3D*,float);
char pad00[8];Object*owner;char pad0C[0x11C-0x0C];Rva00471464Iface iface;bool moving;char pad121[0x2A0-0x121];int mode;char pad2A4[0x2C8-0x2A4];Rva00471464Controller*controller;char pad2CC[0x2F0-0x2CC];int eventObject;
};

void Rva00471464::rva00471464(Object*obj,const Coord3D*destination,float angle)
{
 Object*horde=owner;
 Coord3D old;old.x=obj->pos.x;old.y=obj->pos.y;old.z=obj->pos.z;
 AIUpdateInterface*unitAI=obj->ai;
 AIUpdateInterface*leaderAI=horde->ai;
 if(!leaderAI||!unitAI)return;
 Coord3D goal;goal.x=destination->x;goal.y=destination->y;goal.z=destination->z;
 Locomotor*unitLoco=unitAI->loco;
 Locomotor*leaderLoco=leaderAI->loco;
 if(!unitLoco||!leaderLoco)return;
 if(Rva001E4194Get((Rva001E4194A*)obj)){
  if(obj->flags110.test(29)){obj->flags110.clear(29);obj->rva0028AE6D();}
  return;
 }
 if(mode==0){
  if(!(unitAI->s1BC()&&leaderAI->s1BC()) && (leaderAI->isMoving()||unitAI->s1B8()) && !unitAI->s1C4())
   unitAI->command()->rva0045003E(0,COMMAND_SOURCE_2);
 }else if(!unitAI->s1B8()&&!unitAI->s1BC())unitAI->command()->aiIdle(COMMAND_SOURCE_2);
 if(unitLoco->data->appearance==9&&iface.s238()){
  obj->rva0028AD22();
  Coord3D delta;delta.x=goal.x-obj->pos.x;delta.y=goal.y-obj->pos.y;delta.z=0;
  float dz=goal.z-obj->pos.z;
  bool move=delta.length()>0.5f;
  bool rising=false,falling=false;
  if(!move){if(dz>0.5f)rising=true;else if(dz < -0.5f)falling=true;}
  float ground=TheTerrainLogic->s18(obj->pos.x,obj->pos.y,false);
  if(ground+0.01f>=obj->pos.z&&move&&(obj->status140&0x08000000)){
   ((unsigned char*)&obj->status140)[3]&=0xF7;obj->rva0028AE6D();
  }
  Drawable*drawable=((Thing*)obj)->getDrawable();
  if(rising){
   if(drawable)drawable->rva00272A02(false);
   if((obj->model118&0x200)||!(obj->model118&0x80)){
    ((unsigned char*)&obj->model118)[1]&=0xFD;((unsigned char*)&obj->model118)[0]|=0x80;obj->rva0028AE6D();
   }
   if(!(obj->status140&0x08000000)){obj->status140|=0x08000000;obj->rva0028AE6D();}
   Rva00373EC6*stealth=obj->rva0028F4BC();
   if(stealth&&stealth->state)((StealthUpdate*)stealth)->markAsDetected(0,1,0,true);
   Object*eventTarget=TheGameLogic->findObjectByID(eventObject);
   if(eventTarget&&eventTarget->isLocallyControlled()&&ThePlayerList->local->getRelationship(obj)==0)
    TheEva->reportEvaEvent(15,&eventTarget->pos,0);
  }else if(falling){
   if(drawable)drawable->rva00272A02(false);
   if((obj->model118&0x80)||!(obj->model118&0x200)){
    ((unsigned char*)&obj->model118)[0]&=0x7F;obj->model118|=0x200;obj->rva0028AE6D();
   }
   Rva00373EC6*stealth=obj->rva0028F4BC();
   if(stealth&&stealth->state)((StealthUpdate*)stealth)->markAsDetected(0,1,0,true);
  }else{
   if(drawable)drawable->rva00272A02(true);
   Rva001E4912 mask;((Rva001E42F2*)obj)->rva001E42F2((int*)mask.rva001E4912(0,103,105)->bits);
  }
  if(move){if(!(obj->word110&0x20000000)){obj->word110|=0x20000000;obj->rva0028AE6D();}}
  else if(obj->flags110.test(29)){obj->flags110.clear(29);obj->rva0028AE6D();}
  ((Thing*)obj)->setPosition(&goal);
  float newGround=TheTerrainLogic->s18(obj->pos.x,obj->pos.y,false);
  if(newGround>obj->pos.z)((Rva0030A92C*)obj)->rva0030A92C(newGround);
  moving=true;
  if(iface.s238()){
   Object*bridge=TheGameLogic->findObjectByID((int)TheAI->pathfinder->rva001E4461(1,(int)&obj->pos));
   if(bridge){
    const Coord3D*heading=((Thing*)owner)->getUnitDirectionVector2D();Coord3D direction;direction.x=heading->x;direction.y=heading->y;direction.z=heading->z;
    const Coord3D*other=((Thing*)bridge)->getUnitDirectionVector2D();
    float dot=other->z*direction.z+other->y*direction.y+other->x*direction.x;
    float result=dot>=0?bridge->angle:normalizeAngle(bridge->angle+3.1415927f);
    ((Thing*)obj)->setOrientation(result);return;
   }
  }
  angle=normalizeAngle(angle-obj->angle);
  float turn=unitLoco->getMaxTurnRate(obj);
  if(angle>turn)angle=turn;else if(angle < -turn)angle=-turn;
  ((Thing*)obj)->setOrientation(normalizeAngle(angle+obj->angle));return;
 }
 Coord3D delta;delta.x=goal.x-old.x;delta.y=goal.y-old.y;delta.z=0;
 float distance=delta.length();
 float extra=distance;
 if(leaderAI->path){
  Rva003642DFResult point=leaderAI->path->rva00364521((Rva0008BB38FloatField*)leaderLoco);
  extra=((Rva00363D20*)&point)->rva00363D20()+distance;
  extra-=((Rva0008BB38FloatField*)leaderLoco)->get();
 }
 float tolerance=((Rva001E46E1*)unitLoco)->rva001E4845(obj);
 float speed=((Rva001E46E1*)unitLoco)->rva001E46E1(obj);
 if(tolerance>speed*0.2f)tolerance=speed*0.2f;
 if(distance<100.0f&&TheAI->pathfinder->CountOverlapHordeGoalUnits(obj,&goal)>2){
  Coord3D candidate;candidate.x=old.x;candidate.y=old.y;candidate.z=old.z;
  Coord3D direction;direction.x=goal.x-old.x;direction.y=goal.y-old.y;direction.z=0;
  direction.Normalize();direction.x*=10;direction.y*=10;
  float bestDistance=1.0e10f;
  for(int trial=0;trial<10;++trial){
   bool found=false;Coord3D best;
   for(int i=-1;i<=1;++i)for(int j=-1;j<=1;++j){
    if(i==0&&j==0)continue;
    Coord3D test;test.x=candidate.x+(i*direction.x+j*direction.y);test.y=candidate.y+j*direction.y-i*direction.x;test.z=candidate.z;
    Coord3D difference;difference.x=test.x-goal.x;difference.y=test.y-goal.y;difference.z=test.z-goal.z;
    float cost=difference.GetLength2D();
    if(cost>bestDistance)continue;
    int count=TheAI->pathfinder->CountOverlapHordeGoalUnits(obj,&test);
    if(count>(int)distance)continue;
    cost+=float(count*10)*0.25f;
    if(cost>bestDistance)continue;
    if(!TheAI->pathfinder->rva002EE64A(obj,&candidate,&test))continue;
    bestDistance=cost;best=test;found=true;
   }
   if(!found)break;
   candidate=best;
   if(Rva002EE49BSameCell(obj,candidate,goal))break;
   Coord3D difference;difference.x=candidate.x-old.x;difference.y=candidate.y-old.y;difference.z=candidate.z-old.z;
   float limit=speed*1.5f;
   if(difference.GetLength2D()>limit*limit)break;
  }
 }
 obj->rva0028ACCA((int)&goal);
 if(tolerance>distance){
  Coord3D target;target.x=goal.x;target.y=goal.y;target.z=goal.z;
  if(unitLoco->data->appearance!=8){
   target.z=old.z;
   if(TheAI->pathfinder->IsValidMovementPositionForObject(&target,obj->rva0028B511(),unitAI->movementType,owner))
    target.z=TheTerrainLogic->s1C(target.x,target.y,obj->rva0028B511(),0,true);
  }
  float relative=normalizeAngle(angle-obj->angle);
  bool turn=fabs(relative)>0.17453294f;
  if(mode!=0){
   int slot=((Rva0046ACF6*)this)->rva0046ACF6(obj->id);
   turn=false;
   if(controller->s1C(slot)){turn=fabs(relative)>1.5707964f;if(controller->s24(slot))turn=true;}
   if(controller->s20(slot)&&fabs(relative)>0.17453294f)turn=true;
   if(turn)controller->s28(slot);
  }
  if(turn){
   if(obj->data->flags109&0x40){((Thing*)obj)->setOrientation(angle);unitAI->s220();}
   else{
    if(obj->flags110.test(29)){obj->flags110.clear(29);obj->rva0028AE6D();}
    unitAI->s21C(angle);unitAI->wakeUpNow();
   }
   moving=true;return;
  }
  if(unitAI->isMoving())unitAI->rva00262AEA();
  if(obj->flags110.test(29)){obj->flags110.clear(29);obj->rva0028AE6D();}
  if(iface.s0F0()){Rva0028F59A mask(0,113);((Rva001E431E*)obj)->rva001E431E((int*)mask.bits);}
  unitAI->s220();
  if(mode!=0){int slot=((Rva0046ACF6*)this)->rva0046ACF6(obj->id);if(controller->s1C(slot)||controller->s20(slot))controller->s2C(slot);}
  if(leaderAI->isMoving()){moving=true;return;}
  ((Thing*)obj)->setPosition(&target);obj->nextPosition(&target);
  obj->rva0028ACEE((int)&obj->pos,obj->rva0028B511());return;
 }
 moving=true;
 if(mode!=0)unitAI->s210(&goal);else unitAI->s214(&goal);
 unitAI->setPathExtraDistance(extra);
 if(!(obj->word110&0x20000000)){obj->word110|=0x20000000;obj->rva0028AE6D();}
}
