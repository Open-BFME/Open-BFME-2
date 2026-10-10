// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
// ?doPathfind@AIUpdateInterface@@QAEXPAVPathfindServicesInterface@@@Z
// Retail 0x00269902..0x0026A05D, 1883 bytes, RET 4.
// Identity: all fifteen native doPathfind/ComputePath42 traces and the attack,
// approach, safe-path and final-goal call relationships. WorldBuilder 0x00E37A90
// is an unnamed trace twin; its address does not independently prove the name.
// Semantic guide: BFME1 f98983a7d game/.../AIUpdate.cpp:1533..1800 and ZH.
// Native layout: owner08, path140, victim144, destination148, ignored164,
// blocked16C, repulsors18C/190, locomotor1CC, waiting/attack/final/approach/safe
// flags3B1..3B5. Safe service is slot5; ground movement is slot137.
// Target Object extra-distance field1AC is float, explicitly converted to int.
// All globals/callees are existing owned definitions or existing checked pins.
// Short-circuit approach validation and cached adjust receiver reproduce native
// control flow and register scheduling; trace arguments retain the x87 ABI.
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
 Real getVisionRange()const;
 void rva0028ACEE(int,Int);
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

class PathNode { public: PathNode*next,*prev,*optimized; Coord3D pos; PathfindLayerEnum layer; };
class Path { public:
 Path(); Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);
 void rva00265596(const Coord3D*,PathfindLayerEnum,int);
 unsigned int pad; PathNode *head,*tail; Bool optimized, m_blockedByAlly; char rest[0x28-14];
};
class WeaponTemplate { public: Bool isContactWeapon()const; };
class Weapon { public:
 Bool isWithinAttackRange(const Object*,const Object*,float,int)const;
 unsigned int pad; WeaponTemplate *templ;
 Bool computeApproachTarget(const Object*,const Object*,const Coord3D*,float,Coord3D&) const;
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
	virtual Path *findSafePath(Object*,const LocomotorSet&,const Coord3D*,const Coord3D*,const Coord3D*,Real)=0;

};

class Pathfinder
{
public:
	Int IsLinePassable(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c, Int a20, Int a24);
	Bool IsValidMovementPositionForObject(const Coord3D *pos, Int layer, Int surfaces, const Object *obj);
	void moveAllies(Object *obj, Path *path, Bool flag);
 Bool isAttackViewBlockedByObstacle(const Object*,const Coord3D*,const Object*,const Coord3D*);
 Bool adjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);
 Bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);
 void rva003E3BFB(ObjectID);
 void SetDebugPath(struct Rva002EDEABArg*);
};

struct AIData
{
	unsigned char m_pad00[0x60];
 Real repulsedDistance;
 char m_pad064[0xB9-0x64];
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
 void doPathfind(PathfindServicesInterface*);
 void ignoreObstacle(const Object*);
	Bool computeQuickPath(const Coord3D *destination);
	Bool canComputeQuickPath();
	void destroyPath();
	void setQueueForPathTime(Int frames);
	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);
	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	void setFinalPosition(const Coord3D *pos) { m_finalPosition = *pos; m_doFinalPosition = false; }
protected:
 void wakeUpNow();
private:
	unsigned char m_pad004[0x08 - 0x04];
	Object *m_object; // +0x08
	unsigned char m_pad00C[0x30 - 0x0C];
	StateMachine *m_stateMachine; // +0x30
	unsigned char m_pad034[0x140 - 0x34];
	Path *m_path; // +0x140
 ObjectID m_requestedVictimID;
 Coord3D m_requestedDestination;
 char m_pad154[0x160-0x154];
	UnsignedInt m_pathTimestamp; // +0x160
	int m_ignoredObstacle;
 unsigned char m_pad168[0x16C-0x168];
	Int m_blockedFrames; // +0x16C
	unsigned char m_pad170[0x180 - 0x170];
	Coord3D m_finalPosition; // +0x180
 ObjectID m_repulsor1,m_repulsor2;
 char m_pad194[0x1CC-0x194];
	LocomotorSet m_locomotorSet; // +0x1CC
	unsigned char m_pad1E8[0x1F0 - 0x1E8];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B0 - 0x1F4];
	Bool m_doFinalPosition; // +0x3B0
 Bool m_waitingForPath,m_isAttackPath;
	Bool m_isFinalGoal; // +0x3B3
	Bool m_isApproachPath,m_isSafePath;
 char m_pad3B6[2];
	Bool m_isBlockedAndStuck; // +0x3B8
	unsigned char m_pad3B9[0x3BA - 0x3B9];
	Bool m_canPathThrough; // +0x3BA
	unsigned char m_pad3BB[0x3C0 - 0x3BB];
	Bool m_retryPath; // +0x3C0
 char m_pad3c1[12];
 Bool m_attackFlag; //3cd
};

class GlobalData { public: char pad[0x9b8]; int debugAI; }; extern GlobalData *TheWritableGlobalData;


#define PATH_TRACE(s) if(g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile,s,m_requestedDestination.x,m_requestedDestination.y,m_requestedDestination.z); }
void AIUpdateInterface::doPathfind(PathfindServicesInterface *services)
{
 PATH_TRACE("CritterDesync: doPathfind1 -- m_requestedDestination=%g,%g,%g");
 if(!m_waitingForPath)return;
 TheAI->pathfinder()->rva003E3BFB((ObjectID)m_ignoredObstacle);
 m_waitingForPath=false;
 if(m_isSafePath){
  destroyPath();Coord3D pos1,pos2;pos1.x=-1000.0f;pos1.y=-1000.0f;pos1.z=0.0f;
  Object *repulsor=TheGameLogic->findObjectByID(m_repulsor1);
  if(repulsor)pos1=*repulsor->getPosition();
  pos2=pos1;repulsor=TheGameLogic->findObjectByID(m_repulsor2);
  if(repulsor)pos2=*repulsor->getPosition();
  Object *object=m_object;const AIData *aid=TheAI->getAiData();
  Int extra=(Int)*(const volatile Real*)((const char*)object+0x1ac);
  m_path=services->findSafePath(object,m_locomotorSet,object->getPosition(),&pos1,&pos2,object->getVisionRange()+aid->repulsedDistance+extra);
  *(Real*)((char*)m_object+0x1ac)=0.0f;
  TheAI->pathfinder()->rva003E3BFB((ObjectID)0);
  PATH_TRACE("CritterDesync: doPathfind2 -- m_requestedDestination=%g,%g,%g");return;
 }
 if(m_isApproachPath && !isDoingGroundMovement())m_isApproachPath=false;
 if(m_isAttackPath){
  Object *victim=0;
  if(m_requestedVictimID!=(ObjectID)0)victim=TheGameLogic->findObjectByID(m_requestedVictimID);
  PATH_TRACE("CritterDesync: doPathfind3 -- m_requestedDestination=%g,%g,%g");
  if(computeAttackPath(services,victim,&m_requestedDestination)){
   PATH_TRACE("CritterDesync: doPathfind4 -- m_requestedDestination=%g,%g,%g");
   if(m_path){
    PathNode *last=m_path->tail;m_object->rva0028ACEE((int)&last->pos,(Int)last->layer);
    PATH_TRACE("CritterDesync: doPathfind5 -- m_requestedDestination=%g,%g,%g");
   }
   m_isAttackPath=true;TheAI->pathfinder()->rva003E3BFB((ObjectID)0);
   PATH_TRACE("CritterDesync: doPathfind6 -- m_requestedDestination=%g,%g,%g");return;
  }
  m_isAttackPath=false;
  if(victim){
   m_requestedDestination=*victim->getPosition();
   PATH_TRACE("CritterDesync: doPathfind7 -- m_requestedDestination=%g,%g,%g");
   Object *owner=m_object;Bool adjusted=TheAI->pathfinder()->adjustToPossibleDestination(owner,m_locomotorSet,&m_requestedDestination);
   PATH_TRACE("CritterDesync: doPathfind8 -- m_requestedDestination=%g,%g,%g");
   ignoreObstacle(victim);if(!adjusted)m_isApproachPath=true;
  }
 }
 if(m_isApproachPath){
  destroyPath();PATH_TRACE("CritterDesync: doPathfind8.5 -- m_requestedDestination=%g,%g,%g");
  m_path=services->findClosestPath(m_object,m_locomotorSet,m_object->getPosition(),&m_requestedDestination,m_blockedFrames>0,0.05f,false);
  PATH_TRACE("CritterDesync: doPathfind9 -- m_requestedDestination=%g,%g,%g");
  if(isDoingGroundMovement()&&m_path){
   PathNode *last=m_path->tail;m_object->rva0028ACEE((int)&last->pos,(Int)last->layer);
   PATH_TRACE("CritterDesync: doPathfind10 -- m_requestedDestination=%g,%g,%g");
   Bool move=m_path->m_blockedByAlly&&!m_object->getTemplate()->isKindOfByte(3,0x40);
   Object *obj=m_object;const ThingTemplate *t=obj->getTemplate();
   UnsignedInt kinds=*(const UnsignedInt*)(t->m_kindOf+12);AI *ai=TheAI;
   if((kinds&0x2000)&&!ai->getAiData()->m_fieldB9)move=false;
   if(t->m_moveAllies||(kinds&0x20000000))move=true;
   if(obj->testStatus(OBJECT_STATUS_39)||obj->testStatus(OBJECT_STATUS_32)||obj->isKindOf(KINDOF_84))move=false;
   if(move){
    ai->pathfinder()->moveAllies(obj,m_path,obj->rva0028CE7B()>=4);
    PATH_TRACE("CritterDesync: doPathfind11 -- m_requestedDestination=%g,%g,%g");
   }
  }
  TheAI->pathfinder()->rva003E3BFB((ObjectID)0);return;
 }
 PATH_TRACE("CritterDesync: ComputePath42 -- m_requestedDestination=%g,%g,%g");
 computePath(services,&m_requestedDestination);
 PATH_TRACE("CritterDesync: doPathfind12 -- m_requestedDestination=%g,%g,%g");
 if(m_isFinalGoal&&isDoingGroundMovement()&&m_path){
  PathNode *last=m_path->tail;m_object->rva0028ACEE((int)&last->pos,(Int)last->layer);
  PATH_TRACE("CritterDesync: doPathfind13 -- m_requestedDestination=%g,%g,%g");
 }
 if(!m_waitingForPath)wakeUpNow();
 TheAI->pathfinder()->rva003E3BFB((ObjectID)0);
}
