// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?computeAttackPath@AIUpdateInterface@@QAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// Retail 0x00266AA2..0x00267179, 1753 bytes, RET 0xC.
// Identity: WorldBuilder 0x00E45730 AIUpdateInterface::computeAttackPath,
// AIUpdate.cpp assertions 3262..3304 and matched call relationships.
// Semantic guide: Zero Hour AIUpdate.cpp and BFME1 f98983a7d game/AIUpdate.cpp.
// Target deltas: path-query completion, attack service flags, model kinds,
// state 16, ignored obstacle, and Object final-goal forwarding are native reads.
// Float gates prove native distance thresholds 400/100 and short-path length30.
// Native layout: AI path140/timestamp160/ignored164/blocked16C/locomotor1CC,
// current locomotor1F0/stuck3B8/attack3CD; node position0C/optimized08.
// Inline integer getValidSurfaces keeps MOV EAX+TEST AL8; direct field test folds.
// WorldBuilder names computeApproachTarget; computePath identity follows the donor
// contact-weapon callsite and its native body, with unnamed WB strings twin.
// Their bodies remain unrowed; bindings are candidate pins with target call evidence.
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_39 = 0x39
};
enum KindOfType
{
	KINDOF_84 = 0x84
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);
extern GameLogic *TheGameLogic;

#define CRITTER_TRACE(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); }
#define CRITTER_DETAIL() \
	if (theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, "m_path=%s, m_locomotorSet=%s, destination=%g,%g,%g", \
		m_path ? "VALID" : "NULL", m_locomotorSet.m_name.str(), destination->x, destination->y, destination->z); }
#define CRITTER_NEWDETAIL() \
	if (theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, "m_path=%s, theNewPath=%s, m_locomotorSet=%s, destination=%g,%g,%g", \
		m_path ? "VALID" : "NULL", theNewPath ? "VALID" : "NULL", m_locomotorSet.m_name.str(), destination->x, destination->y, destination->z); }
#define CRITTER_TRACEDETAIL(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); CRITTER_DETAIL(); }
#define CRITTER_TRACENEW(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); CRITTER_NEWDETAIL(); }

struct Region3D
{
	Coord3D lo, hi;
	Bool isInRegionNoZ(const Coord3D *p) const
	{
		return lo.x < p->x && p->x < hi.x && lo.y < p->y && p->y < hi.y;
	}
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	Bool isKindOfByte(Int index, unsigned char mask) const { return (m_kindOf[index] & mask) != 0; }
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x108 - 0x68];
	unsigned char m_kindOf[0x18]; // observed bytes +0x108..0x11F
	unsigned char m_pad120[0x614 - 0x120];
	Bool m_moveAllies; // +0x614
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
 Bool isAboveTerrain()const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Weapon;
enum WeaponSlotType { SLOT=0 };
class Object : public Thing
{
public:
	Int rva0028B511() const;
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 Bool isSignificantlyAboveTerrain() const;
 Real rva002637E2(const Coord3D*,const Coord3D*)const;
 void rva0028AD32();
 void rva0028ACDC(const Coord3D*); // the layer
	signed char rva0028CE7B() const; // the crushable level
	Bool testStatus(ObjectStatusTypes status) const;
	Bool isKindOf(KindOfType kind) const;
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_pad44[0x74 - 0x44];
	UnsignedInt m_id; // +0x74
};

class Locomotor
{
public:
	Bool isUltraAccurate() const { return (m_flags >> 6) & 1; }
 void setNoSlowDownAsApproachingDest(Bool x) { if(x)m_flags|=16;else m_flags&=~16; }
private:
	unsigned char m_pad00[0x44];
	UnsignedInt m_flags; // +0x44
};

class LocomotorSet
{
public:
	unsigned char m_pad00[0x10];
	Int m_validSurfaces;
 __forceinline int getValidSurfaces() const{return m_validSurfaces;} // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	AsciiString m_name; // +0x18
};

struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node;
	Coord3D m_pos;
};
class Rva0008BB38FloatField;
class Rva001E3511
{
public:
	int rva001E3511();
};

class PathNode { public: PathNode*next,*prev,*optimized; Coord3D pos; };
class Path { public:
 Path(); Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);
 void rva00265596(const Coord3D*,PathfindLayerEnum,int);
 unsigned int pad; PathNode *head,*tail; Bool optimized, m_blockedByAlly; char rest[0x28-14];
};
class WeaponTemplate { public: Bool isContactWeapon()const; };
class Weapon { public:
 Bool isWithinAttackRange(const Object*,const Object*,float,int)const;
 unsigned int pad; WeaponTemplate *templ;
 void computeApproachTarget(const Object*,const Object*,const Coord3D*,float,Coord3D&) const;
};
class Rva002C9B80Owner { public: Bool isWithinAttackRange(Object*,const Coord3D*,Object*,const Coord3D*,float,Bool); };
// updateLastNode, rowed under its address name.
class Rva003638BA
{
public:
	void rva003638FD(const Coord3D *pos);
};

class PathfindServicesInterface
{
public:
	virtual Path *findPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from, const Coord3D *to, Bool *retry) = 0;
	virtual Path *findClosestPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from, Coord3D *to,
		Bool blocked, Real pathCostMultiplier, Bool moveAllies) = 0;
	virtual Path *findAttackPath(Object*,const LocomotorSet&,const Coord3D*,const Object*,const Coord3D*,const Weapon*,Bool,Bool*)=0;
	virtual Path *findAttackPath2(Object*,const LocomotorSet&,const Coord3D*,const Object*,const Coord3D*,const Weapon*)=0;
	virtual Path *patchPath(const Object *obj, const LocomotorSet &locomotorSet, Path *originalPath, Bool blocked) = 0;
};

class Pathfinder
{
public:
	Int IsLinePassable(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c, Int a20, Int a24);
	Bool IsValidMovementPositionForObject(const Coord3D *pos, Int layer, Int surfaces, const Object *obj);
	void moveAllies(Object *obj, Path *path, Bool flag);
 Bool isAttackViewBlockedByObstacle(const Object*,const Coord3D*,const Object*,const Coord3D*);
 Bool adjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);
 void rva003E3BFB(ObjectID);
 void SetDebugPath(struct Rva002EDEABArg*);
};

struct AIData
{
	unsigned char m_pad00[0xB9];
	Bool m_fieldB9; // +0xB9
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() { return m_aiData; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	const AIData *m_aiData; // +0x18
};
extern AI *TheAI;

struct TBridgeAttackInfo { Coord3D attackPoint1,attackPoint2; };
class TerrainLogic { public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();
 virtual Real getLayerHeight(Real,Real,PathfindLayerEnum,void*,Bool);
 void getBridgeAttackPoints(const Object*,TBridgeAttackInfo*);
};
extern TerrainLogic *TheTerrainLogic;

Bool Rva001E3679(Int layer);
Int Rva002EDE5B(void *obj, Coord3D *pos);

class State
{
public:
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_pad00[4];
	UnsignedInt m_id; // +0x04
};

class StateMachine
{
public:
	UnsignedInt getCurrentStateID() const { return m_currentState ? m_currentState->getID() : 999999; }
private:
	unsigned char m_pad00[4];
	State *m_currentState; // +0x04
};

class AIUpdateInterface
{
public:
#define X1_V(n) virtual void slot##n();
#define X1_V10(n) X1_V(n##0) X1_V(n##1) X1_V(n##2) X1_V(n##3) X1_V(n##4) X1_V(n##5) X1_V(n##6) X1_V(n##7) X1_V(n##8) X1_V(n##9)
	X1_V10(10) X1_V10(11) X1_V10(12) X1_V10(13) X1_V10(14) X1_V10(15) X1_V10(16) X1_V10(17) X1_V10(18) X1_V10(19)
	X1_V10(20) X1_V10(21) X1_V10(22)
	X1_V(230)
#undef X1_V10
#undef X1_V
	virtual void setLocomotorGoalPositionOnPath(); // +0x20C
	virtual void slot233();
	virtual void slot234();
	virtual void slot235();
	virtual void slot236();
	virtual void setLocomotorGoalNone(); // +0x220
 virtual Bool isDoingGroundMovement();

	Bool computePath(PathfindServicesInterface *pathServices, Coord3D *destination);
 Bool computeAttackPath(PathfindServicesInterface*,const Object*,const Coord3D*);
	Bool computeQuickPath(const Coord3D *destination);
	Bool canComputeQuickPath();
	void destroyPath();
	void setQueueForPathTime(Int frames);
	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);
	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	void setFinalPosition(const Coord3D *pos) { m_finalPosition = *pos; m_doFinalPosition = false; }
private:
	unsigned char m_pad004[0x08 - 0x04];
	Object *m_object; // +0x08
	unsigned char m_pad00C[0x30 - 0x0C];
	StateMachine *m_stateMachine; // +0x30
	unsigned char m_pad034[0x140 - 0x34];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x160 - 0x144];
	UnsignedInt m_pathTimestamp; // +0x160
	int m_ignoredObstacle;
 unsigned char m_pad168[0x16C-0x168];
	Int m_blockedFrames; // +0x16C
	unsigned char m_pad170[0x180 - 0x170];
	Coord3D m_finalPosition; // +0x180
	unsigned char m_pad18C[0x1CC - 0x18C];
	LocomotorSet m_locomotorSet; // +0x1CC
	unsigned char m_pad1E8[0x1F0 - 0x1E8];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B0 - 0x1F4];
	Bool m_doFinalPosition; // +0x3B0
	unsigned char m_pad3B1[0x3B3 - 0x3B1];
	Bool m_isFinalGoal; // +0x3B3
	unsigned char m_pad3B4[0x3B8 - 0x3B4];
	Bool m_isBlockedAndStuck; // +0x3B8
	unsigned char m_pad3B9[0x3BA - 0x3B9];
	Bool m_canPathThrough; // +0x3BA
	unsigned char m_pad3BB[0x3C0 - 0x3BB];
	Bool m_retryPath; // +0x3C0
 char m_pad3c1[12];
 Bool m_attackFlag; //3cd
};

class GlobalData { public: char pad[0x9b8]; int debugAI; }; extern GlobalData *TheWritableGlobalData;

Bool AIUpdateInterface::computeAttackPath(PathfindServicesInterface *services,const Object *victim,const Coord3D *victimPos)
{
 if(m_path) {
  Rva003642DFResult result=m_path->rva00364521((const Rva0008BB38FloatField*)m_curLocomotor);
  if(((Rva001E3511*)&result)->rva001E3511()!=0x7fffffff){
   m_pathTimestamp=TheGameLogic->getFrame();m_blockedFrames=0;m_isBlockedAndStuck=false;return true;
  }
 }
 Bool landBound=false;
 if(!(m_locomotorSet.getValidSurfaces()&8))landBound=true;
 Object *source=getObject();
 if(!victim&&!victimPos)return false;
 PathfindLayerEnum victimLayer=LAYER_GROUND;
 if(victim)victimLayer=(PathfindLayerEnum)victim->rva0028B511();
 const Weapon *weapon=source->getCurrentWeapon(0);
 if(!weapon)return false;
 if(victim){
  if(weapon->isWithinAttackRange(source,victim,0.0f,1)){
   Bool viewBlocked=false;
   if(isDoingGroundMovement()&&!victim->isSignificantlyAboveTerrain())
    viewBlocked=TheAI->pathfinder()->isAttackViewBlockedByObstacle(source,source->getPosition(),victim,victim->getPosition());
   if(!viewBlocked){destroyPath();return true;}
  }
 }else if(victimPos){
  if(((Rva002C9B80Owner*)weapon)->isWithinAttackRange(source,source->getPosition(),0,victimPos,0.0f,true)){
   destroyPath();return true;
  }
 }
 if(weapon->templ->isContactWeapon()){
  Coord3D tmp;tmp.x=victimPos->x;tmp.y=victimPos->y;tmp.z=victimPos->z;
  destroyPath();
  if(m_curLocomotor)m_curLocomotor->setNoSlowDownAsApproachingDest(true);
  CRITTER_TRACE("CritterDesync: ComputePath44");
  Bool ok=computePath(services,&tmp);
  if(!m_path)return false;
  Real dx=victimPos->x-m_path->tail->pos.x,dy=victimPos->y-m_path->tail->pos.y;
  if(dx*dx+dy*dy<400.0f)((Rva003638BA*)m_path)->rva003638FD(victimPos);
  dx=source->getPosition()->x-m_path->tail->pos.x;dy=source->getPosition()->y-m_path->tail->pos.y;
  if(dx*dx+dy*dy<100.0f){destroyPath();return false;}
  return ok;
 }
 Coord3D localVictimPos;
 if(victim){
  if(victim->getTemplate()->isKindOfByte(2,0x40)){
   TBridgeAttackInfo info;TheTerrainLogic->getBridgeAttackPoints(victim,&info);
   Real dist1=source->rva002637E2(source->getPosition(),&info.attackPoint1);
   Real dist2=source->rva002637E2(source->getPosition(),&info.attackPoint2);
   if(dist2<dist1)localVictimPos=info.attackPoint2;else localVictimPos=info.attackPoint1;
  }else localVictimPos=*victim->getPosition();
 }else localVictimPos=*victimPos;
 localVictimPos.z=TheTerrainLogic->getLayerHeight(localVictimPos.x,localVictimPos.y,victimLayer,0,true);
 if(getObject()->isAboveTerrain()&&!landBound){
  weapon->computeApproachTarget(getObject(),victim,&localVictimPos,0.0f,localVictimPos);
  if(m_path){
   PathNode *close=m_path->head->optimized;
   if(close&&!close->optimized){
    Real dx=localVictimPos.x-close->pos.x;dx*=dx;
    Real dy=localVictimPos.y-close->pos.y;dy*=dy;
    if(dx+dy<0.25f)return true;
   }
  }
  destroyPath();m_path=new Path;
  m_path->rva00265596(&localVictimPos,LAYER_GROUND,0x7fffffff);
  Coord3D pos;const Coord3D *position=getObject()->getPosition();pos.x=position->x;pos.y=position->y;pos.z=localVictimPos.z;
  m_path->rva00265596(&pos,LAYER_GROUND,0x7fffffff);
  if(TheWritableGlobalData->debugAI==1)TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg*)m_path);
 }else{
  destroyPath();getObject()->rva0028AD32();
  TheAI->pathfinder()->rva003E3BFB((ObjectID)m_ignoredObstacle);
  Bool attackFlag=false;
  if(getStateMachine()&&getStateMachine()->getCurrentStateID()==16)attackFlag=m_attackFlag;
  Bool shortPath=false;
  if(getObject()->getTemplate()->isKindOfByte(0x17,0x80))
   m_path=services->findAttackPath2(getObject(),m_locomotorSet,getObject()->getPosition(),victim,&localVictimPos,weapon);
  else m_path=services->findAttackPath(getObject(),m_locomotorSet,getObject()->getPosition(),victim,&localVictimPos,weapon,attackFlag,&shortPath);
  if(m_path){
   Coord3D goal;const Coord3D *last=&m_path->tail->pos;goal.x=last->x;goal.y=last->y;goal.z=last->z;
   if(!shortPath&&!((Rva002C9B80Owner*)weapon)->isWithinAttackRange(getObject(),&goal,(Object*)victim,&localVictimPos,0.0f,true)&&!attackFlag){
    Coord3D objPos;const Coord3D *position=getObject()->getPosition();objPos.x=position->x;objPos.y=position->y;objPos.z=position->z;
    goal.x-=objPos.x;goal.y-=objPos.y;goal.z-=objPos.z;
    if(goal.length()<30.0f){
     destroyPath();TheAI->pathfinder()->adjustDestination(getObject(),m_locomotorSet,&objPos,0);
     m_path=services->findClosestPath(getObject(),m_locomotorSet,getObject()->getPosition(),&objPos,false,0.2f,true);
    }
    if(!m_path){TheAI->pathfinder()->rva003E3BFB((ObjectID)0);return false;}
   }
   PathNode *end=m_path->tail;
   goal=*(const Coord3D*)((const char*)end+12);getObject()->rva0028ACDC(&goal);
  }
  TheAI->pathfinder()->rva003E3BFB((ObjectID)0);
  if(attackFlag)return true;
  if(m_path){
   Bool move=m_path->m_blockedByAlly&&!getObject()->getTemplate()->isKindOfByte(3,0x40);
   Object *obj=getObject();
   const ThingTemplate *t=obj->getTemplate();
   UnsignedInt kinds=*(const UnsignedInt*)(t->m_kindOf+12);
   AI *ai=TheAI;
   if((kinds&0x2000)&&!ai->getAiData()->m_fieldB9)move=false;
   if(t->m_moveAllies||(kinds&0x20000000))move=true;
   if(obj->testStatus(OBJECT_STATUS_39)||obj->testStatus(OBJECT_STATUS_32)||obj->isKindOf(KINDOF_84))move=false;
   if(move)ai->pathfinder()->moveAllies(obj,m_path,obj->rva0028CE7B()>=4);
  }
 }
 m_pathTimestamp=TheGameLogic->getFrame();m_blockedFrames=0;m_isBlockedAndStuck=false;if(m_path)return true;return false;
}
