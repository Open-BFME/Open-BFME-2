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

#include "../../../../../Libraries/Include/Lib/Region3D.h"

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
// Target model-condition words begin at Object+0x10C. The indexed accessor
// preserves the shared mask calculation used by the retail setter.
class FacingConditionBits {
public:
 unsigned int test(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 void set(int bit) { words[bit>>5] |= 1U<<(bit&31); }
 unsigned int words[19];
};

class Object : public Thing
{
public:
	Int rva0028B511() const;
 void rva0028AE6D();
 __forceinline unsigned int hasFacingMask(unsigned int bit) const { return m_conditions.test(bit); }
 __forceinline void addFacingMask(unsigned int bit) { m_conditions.set(bit); }
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 Bool isSignificantlyAboveTerrain() const;
 Real rva002637E2(const Coord3D*,const Coord3D*)const;
 void rva0028AD32();
 void rva0028ACDC(int); // the layer
	signed char rva0028CE7B() const; // the crushable level
	Bool testStatus(ObjectStatusTypes status) const;
	Bool isKindOf(KindOfType kind) const;
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_pad44[0x74 - 0x44];
	UnsignedInt m_id; // +0x74
 unsigned char m_pad078[0x10c - 0x78];
 FacingConditionBits m_conditions; // +0x10c
};

class Locomotor
{
public:
	Bool isUltraAccurate() const { return (m_flags >> 6) & 1; }
 __declspec(dllimport) __forceinline void setNoSlowDownAsApproachingDest(Bool x) { if(x)m_flags|=16;else m_flags&=~16; }
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
 void prependNode(const Coord3D*,PathfindLayerEnum,int);
 unsigned int pad; PathNode *head,*tail; Bool optimized, m_blockedByAlly; char rest[0x28-14];
};
class WeaponTemplate { public: Bool isContactWeapon()const; };
#include "../../../../Include/GameLogic/Weapon.h"
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
	Bool MoveAllies(Object *obj, Path *path, Bool flag);
 Bool isAttackViewBlockedByObstacle(const Object*,const Coord3D&,const Object*,const Coord3D&);
 Bool AdjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);
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
	__declspec(dllimport) __forceinline UnsignedInt getCurrentStateID() const { return m_currentState ? m_currentState->getID() : 999999; }
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
 void rva0026717B();
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


class Rva00265254 {
public:
 Rva00265254(unsigned int,unsigned int,unsigned int,unsigned int);
 int bits[19];
};
class Rva001E42F2 { public: void rva001E42F2(const int *); };

struct FacingDirection : Coord3D {
 FacingDirection(float a,float b,float c) { x=a;y=b;z=c; }
 ~FacingDirection() {}
};

static __forceinline void setFacingCondition(Object *obj,unsigned int bit) {
 if(obj->hasFacingMask(bit)==0) { obj->addFacingMask(bit);obj->rva0028AE6D(); }
}

// Retail 0x0026717B..0x00267266, 235 bytes, RET 0. Direct callers in
// AIUpdateInterface::doLocomotor establish the owner and no-argument ABI.
// WorldBuilder 0x00E4B180 supplies the model-condition bit indices and object
// relationships; its assertion labels do not establish this helper's original
// name. Native reads prove module+8, template+0x11F bit7, matrix+0xC/+0x1C/+0x2C,
// and Object condition word+0x134. The static direction at 0x00DFEB40 has a
// guarded constructor and a registered empty cleanup at 0x007B77CD; the derived
// FacingDirection is a local lifetime view, not a claim about its original type.
// The canonical Coord3D Normalize and existing bitset/reset/notifier providers
// preserve all call identities. Dot-product order is Z+Y+X, including NaNs.
void AIUpdateInterface::rva0026717B()
{
 Object *obj=getObject();
 if(obj->getTemplate()->isKindOfByte(0x17,0x80)) {
  static FacingDirection direction(0.5f,0.5f,0.0f);
  direction.Normalize();
  ((Rva001E42F2*)obj)->rva001E42F2(Rva00265254(0,0x151,0x152,0x153).bits);
  const float *matrix=(const float*)((const char*)obj+0x0c);
  Coord3D axis;
  axis.x=matrix[0];axis.y=matrix[4];axis.z=matrix[8];
  float dot=direction.z*axis.z+direction.y*axis.y+direction.x*axis.x;
  if(dot>0.0f) setFacingCondition(obj,0x153); else setFacingCondition(obj,0x152);
 }
}
