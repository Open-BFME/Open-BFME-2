// ?rva0026CF11@AIUpdateInterface@@QAE_NPAVObject@@@Z
// partial score=0.9949072454397704 date=2026-10-09
// cl: /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
enum Relationship{ENEMIES=0,NEUTRAL=1,ALLIES=2};enum ObjectStatusTypes{};class Object;class AIUpdateInterface;class LocomotorSet;class Rva0008BB38FloatField;
class Thing {public:void getUnitDirectionVector2D(Coord3D&)const;};
struct Rva003642DFResult {float m_distance;Coord3D m_point;};
class Rva001E3511 {public:int rva001E3511();};
class Path {public:Rva003642DFResult rva00364521(const Rva0008BB38FloatField*);char pad[8];struct Node{char pad[12];Coord3D point;}*node;};
class Rva0008BB38FloatField {public:char pad[0x44];union{unsigned flags;struct{unsigned lower:7;unsigned ignored:1;unsigned upper:24;};};bool ignores()const{return ignored!=0;}};
class ThingTemplate {public:char pad[0x108];unsigned kind[7];__forceinline bool kindOf(int n)const{return (reinterpret_cast<const unsigned char*>(kind)[n>>3]&(1u<<(n&7)))!=0;}};
enum CommandSourceType{CMD_FROM_AI=2};
class CollisionConditionBits{public:unsigned test(int n)const{return words[n>>5]&(1u<<(n&31));}void clear(int n){words[n>>5]&=~(1u<<(n&31));}unsigned words[19];};
class Object:public Thing {public:
 Relationship getRelationship(const Object*)const;bool rva0029493F(Object*,int);int rva0028B511()const;
 bool testStatus(ObjectStatusTypes)const;float rva0028AC7D()const;void rva0028AE6D();
 char pad[4];ThingTemplate*templ;char pad8[0x38-8];Coord3D position;
 char pad44[0x74-0x44];int id;char pad78[0x10c-0x78];CollisionConditionBits conditions;
 char pad158[0x258-0x158];AIUpdateInterface*ai;char pad25c[0x410-0x25c];void*formation;float fx,fy;char pad41c[0x438-0x41c];unsigned flags438;

};
static __forceinline void clearCondition(Object*obj,int n){if(obj->conditions.test(n)){obj->conditions.clear(n);obj->rva0028AE6D();}}
bool Rva002629EACheck(const Thing*,const Thing*);int Rva00264237Check(const Coord3D*,const Coord3D*);
class Pathfinder{public:bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);bool rva002EBD65(ObjectID);};
class AI{public:char pad[0x10];Pathfinder*pathfinder;};extern AI*TheAI;
extern GameLogic*TheGameLogic;
class TerrainLogic{public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual bool isUnderwater(const Coord3D*);
};extern TerrainLogic*TheTerrainLogic;extern int g_Va00DBA4E4;
class State{public:char pad[4];int id;};class Machine{public:char pad[4];State*state;int getID()const{return state?state->id:999999;}};
class AICommandInterface{public:void aiMoveToPosition(const Coord3D*,CommandSourceType);char pad[0x10];};
class AIUpdateInterface{public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual void v83();
 virtual void v84();
 virtual void v85();
 virtual void v86();
 virtual void v87();
 virtual void v88();
 virtual void v89();
 virtual void v90();
 virtual void v91();
 virtual void v92();
 virtual void v93();
 virtual void v94();
 virtual void v95();
 virtual void v96();
 virtual void v97();
 virtual void v98();
 virtual void v99();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual bool isIdle();
 virtual void v111();
 virtual void v112();
 virtual void v113();
 virtual void v114();
 virtual void v115();
 virtual void v116();
 virtual void v117();
 virtual void v118();
 virtual void v119();
 virtual void v120();
 virtual void v121();
 virtual void v122();
 virtual void v123();
 virtual void v124();
 virtual void v125();
 virtual void v126();
 virtual Object*currentVictim();
 virtual void v128();
 virtual void v129();
 virtual void v130();
 virtual void v131();
 virtual void v132();
 virtual void v133();
 virtual void v134();
 virtual void v135();
 virtual void v136();
 virtual bool isDoingGroundMovement();
 bool isMoving()const;int rva00260DED()const;int rva0026417F(bool);unsigned char rva002641BA();bool rva0026CF11(Object*);
 char pad4[4];Object*owner;char padC[0x20-0xc];AICommandInterface command;Machine*machine;
 char pad34[0x140-0x34];Path*path;char pad144[0x16c-0x144];int blockedFrames;
 char pad170[8];unsigned ignoreUntil;char pad17c[0x1f0-0x17c];Rva0008BB38FloatField*loco;
 char pad1f4[0x3b1-0x1f4];bool waiting;char pad3b2[6];bool blocked;char pad3b9[4];bool dead;
 char pad3be[0x3dc-0x3be];int responseID;
 const LocomotorSet&getLocomotorSet()const{return *reinterpret_cast<const LocomotorSet*>(reinterpret_cast<const char*>(this)+0x1cc);}
};
bool AIUpdateInterface::rva0026CF11(Object*other)
{
 AIUpdateInterface*aiOther=other->ai;if(!aiOther)return false;
 Object*obj=owner;Relationship relationship=obj->getRelationship(other);
 if(relationship==0 && obj->rva0029493F(other,2))return false;
 if(loco && loco->ignores())return false;
 if(obj->templ->kindOf(0x6d)&&relationship==2){if(obj->rva0028B511()!=1)return false;if(TheTerrainLogic->isUnderwater(&obj->position))return false;}
 if(aiOther->currentVictim()==obj)return false;
 if(!isDoingGroundMovement())return false;if(!aiOther->isDoingGroundMovement())return false;
 if(obj->templ->kindOf(8)&&machine->getID()==0x13)return false;
 bool selfMoving=isMoving();bool otherMoving=aiOther->isMoving();
 if(selfMoving&&path&&(unsigned char)Rva00264237Check(&obj->position,&path->node->point))return false;
 if(otherMoving&&aiOther->path&&(unsigned char)Rva00264237Check(&other->position,&aiOther->path->node->point))return false;
 if(path){Rva003642DFResult p=path->rva00364521(loco);if(reinterpret_cast<Rva001E3511*>(&p)->rva001E3511()!=0x7fffffff)return false;}
 if(aiOther->path){Rva003642DFResult p=aiOther->path->rva00364521(aiOther->loco);if(reinterpret_cast<Rva001E3511*>(&p)->rva001E3511()!=0x7fffffff)return false;}
 if(!selfMoving){
  if(dead&&obj->templ->kindOf(8)&&other->rva0029493F(obj,1))return false;
  if(otherMoving)return false;if(rva00260DED()==0x2a)return false;
  if(obj->testStatus((ObjectStatusTypes)0x46))return false;if(obj->flags438&8)return false;if(obj->templ->kindOf(0xba))return false;
  if(!isIdle())return false;
  Coord3D safe,old;safe.x=obj->position.x;safe.y=obj->position.y;safe.z=obj->position.z;old.x=safe.x;old.y=safe.y;old.z=safe.z;
  TheAI->pathfinder->adjustToPossibleDestination(obj,getLocomotorSet(),&safe);
  if(!(safe==old))command.aiMoveToPosition(&safe,CMD_FROM_AI);
  return false;
 }
 if(obj->formation==other->formation&&obj->formation){
  struct FormationPoint{float x,y;FormationPoint(float x_,float y_):x(x_),y(y_){} };FormationPoint a(0,0),b(0,0);a=*reinterpret_cast<FormationPoint*>(&owner->fx);b=*reinterpret_cast<FormationPoint*>(&other->fx);if(a.x>b.x)return false;
 }else if(!otherMoving){
  if((unsigned)rva0026417F(relationship==0)>(unsigned)aiOther->rva0026417F(relationship==0))return false;
 }else{
  Coord3D a,b;obj->getUnitDirectionVector2D(a);other->getUnitDirectionVector2D(b);
  if(a.x*b.x+a.y*b.y+a.z*b.z>0.9f){
   if(Rva002629EACheck(obj,other)){if(obj->rva0028AC7D()>other->rva0028AC7D()*0.95f)return false;}
   else {float otherSpeed=other->rva0028AC7D();float selfSpeed=obj->rva0028AC7D();if(otherSpeed>=selfSpeed*0.95f)return false;}
  }else{
   int ap=rva0026417F(relationship==0),bp=aiOther->rva0026417F(relationship==0);
   if(ap>bp)return false;if(ap==bp&&obj->id>other->id)return false;
  }
 }
 blocked=true;if(blockedFrames==0)blockedFrames=1;
 if(otherMoving&&aiOther->waiting)return false;
 if(blockedFrames%g_Va00DBA4E4!=obj->id%g_Va00DBA4E4)return false;
 if(responseID==0){responseID=other->id;TheAI->pathfinder->rva002EBD65((ObjectID)obj->id);}
 if(blockedFrames>2*g_Va00DBA4E4+1){blocked=false;blockedFrames=0;ignoreUntil=TheGameLogic->getFrame()+2*g_Va00DBA4E4;return true;}
 if(!rva002641BA()){clearCondition(obj,0x3d);clearCondition(obj,0x9c);}
 return false;
}
