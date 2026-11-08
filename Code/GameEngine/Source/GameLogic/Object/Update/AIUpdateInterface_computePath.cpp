// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?computePath@AIUpdateInterface@@QAE_NPAVPathfindServicesInterface@@PAUCoord3D@@@Z
// Retail 0x00265E0B..0x00266AA2, 3223 bytes, RET 8.
// Identity: native CritterDesync computePath traces, owned doPathfind and attack-
// path callers, plus ZH AIUpdateInterface::computePath semantic structure.
// WorldBuilder 0x00E43A60 is an unnamed strings twin, not independent name proof.
// Guide: prior BFME2 bank, BFME1 f98983a7d game/.../AIUpdate.cpp and ZH.
// All object/module offsets and branch deltas follow the target accesses.
// Inline getValidSurfaces(), established by the matched attack-path sibling,
// restores the native NULL literal lifetime through the trace region.
// Cache original path before owner in patchPath; initialize tryClosest before
// retry in findPath. These produce native scheduling without new ABI bindings.
// IsLinePassable's existing Int declaration requires char narrowing for TEST AL.
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
extern int BfmeLogicFramesPerSecond;
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

#include "../../../../Include/Common/ThingTemplate.h"

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	Int rva0028B511() const; // the layer
	signed char rva0028CE7B() const; // the crushable level
	Bool testStatus(ObjectStatusTypes status) const;
	Bool isKindOf(KindOfType kind) const;
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_pad44[0x74 - 0x44];
	UnsignedInt m_id; // +0x74
};

#include "../../../../Include/GameLogic/LocomotorClass.h"

class LocomotorSet
{
public:
	unsigned char m_pad00[0x10];
	Int m_validSurfaces; // +0x10
 int getValidSurfaces()const{return m_validSurfaces;}
	unsigned char m_pad14[0x18 - 0x14];
	AsciiString m_name; // +0x18
};

struct Rva003642DFNode;
#include "../../../../Include/GameLogic/Rva003642DFResult.h"
class Rva0008BB38FloatField;
class Rva001E3511
{
public:
	int rva001E3511();
};

#include "../../../../Include/GameLogic/PathfindPath.h"

// updateLastNode, rowed under its address name.
class Rva003638BA
{
public:
	void rva003638FD(const Coord3D *pos);
};

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/TAiData.h"
#include "../../../../Include/GameLogic/AI.h"

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

Bool Rva001E3679(Int layer);
Int Rva002EDE5B(void *obj, Coord3D *pos);

#include "../../../../Include/Common/StateMachineClass.h"


class AIUpdateInterface
{
public:
	void rva00265667(const Coord3D *, int);
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

	Bool computePath(PathfindServicesInterface *pathServices, Coord3D *destination);
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
	unsigned char m_pad164[0x16C - 0x164];
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
};

Bool AIUpdateInterface::computePath(PathfindServicesInterface *pathServices, Coord3D *destination)
{
	CRITTER_TRACE("CritterDesync: ComputePath43");
	{
		Object *obj = getObject();
		if (g_00E03745) {
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "CritterDesync:  Object %s(%d) called AIUpdateInterface::computePath()",
					obj->getTemplate()->getName().str(), obj->getID());
			CRITTER_DETAIL();
		}
	}

	if (m_path) {
		Rva003642DFResult closest = m_path->rva00364521((const Rva0008BB38FloatField *)m_curLocomotor);
		if (((Rva001E3511 *)&closest)->rva001E3511() != 0x7fffffff) {
			m_pathTimestamp = TheGameLogic->getFrame();
			m_blockedFrames = 0;
			m_isBlockedAndStuck = false;
			CRITTER_TRACEDETAIL("CritterDesync:  return true because of portal.");
			return true;
		}
	}

	if (m_blockedFrames <= 0) {
		CRITTER_TRACEDETAIL("CritterDesync:  path destroyed.");
		destroyPath();
	}

	if (canComputeQuickPath()) {
		if (computeQuickPath(destination)) {
			CRITTER_TRACEDETAIL("CritterDesync:  computeQuickPath1 returned TRUE.");
			return true;
		} else {
			CRITTER_TRACEDETAIL("CritterDesync:  computeQuickPath1 returned FALSE.");
			return false;
		}
	}

	CRITTER_TRACEDETAIL("CritterDesync:  m_retryPath cleared.");
	m_retryPath = false;

	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent(&extent);
	if (!extent.isInRegionNoZ(destination)) {
		const Coord3D *p = getObject()->getPosition();
		Coord3D pos;
		pos.x = p->x;
		pos.y = p->y;
		pos.z = p->z;
		if (!extent.isInRegionNoZ(&pos)) {
			if (computeQuickPath(destination)) {
				CRITTER_TRACEDETAIL("CritterDesync:  computeQuickPath2 returned TRUE.");
				return true;
			} else {
				CRITTER_TRACEDETAIL("CritterDesync:  computeQuickPath2 returned FALSE.");
				return false;
			}
		}
	}

	if (getStateMachine()->getCurrentStateID() == 7 && m_canPathThrough) {
		Bool ok = computeQuickPath(destination);
		if (ok) {
			m_canPathThrough = false;
			rva00265667(destination, CMD_FROM_AI);
			CRITTER_TRACEDETAIL("CritterDesync:  computeQuickPath3 returned TRUE.");
			return ok;
		}
	}

	Path *theNewPath = 0;
	CRITTER_NEWDETAIL();

	Coord3D originalDestination;
	originalDestination.x = destination->x;
	originalDestination.y = destination->y;
	originalDestination.z = destination->z;
	Int surfaces = m_locomotorSet.getValidSurfaces();
	Bool specialLayer = Rva001E3679(getObject()->rva0028B511());
	if (!m_isFinalGoal && !specialLayer &&
			(char)TheAI->pathfinder()->IsLinePassable(getObject(), (void *)surfaces, (PathfindLayerEnum)getObject()->rva0028B511(),
				getObject()->getPosition(), &originalDestination, 0, 1, 0)) {
		if (computeQuickPath(destination)) {
			CRITTER_TRACENEW("CritterDesync:  computeQuickPath4 returned TRUE.");
			return true;
		} else {
			CRITTER_TRACENEW("CritterDesync:  computeQuickPath4 returned FALSE.");
			return false;
		}
	}

	Bool tryClosest = true;
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(getObject(), destination);
	if (!TheAI->pathfinder()->IsValidMovementPositionForObject(destination, destinationLayer, m_locomotorSet.getValidSurfaces(), getObject())) {
		theNewPath = 0;
		CRITTER_TRACE("CritterDesync:  theNewPath = NULL;");
		if (g_00E03745) {
			CRITTER_NEWDETAIL();
		}
	} else if (m_blockedFrames > 0) {
		Path *original=m_path; Object *owner=getObject(); theNewPath = pathServices->slot04(owner, m_locomotorSet, original, m_blockedFrames > 0);
		CRITTER_TRACENEW("CritterDesync:  m_isBlockedAndStuck check.");
	} else {
		Bool retry;
		tryClosest = false;
		retry = false;
		theNewPath = pathServices->slot00(getObject(), m_locomotorSet, getObject()->getPosition(), destination, &retry);
		if (retry)
			m_retryPath = true;
		CRITTER_TRACENEW("CritterDesync:  m_isBlockedAndStuck failed check.");
	}

	if (theNewPath == 0 && m_path == 0 && tryClosest) {
		theNewPath = pathServices->slot01(getObject(), m_locomotorSet, getObject()->getPosition(), destination,
			m_blockedFrames > 0, 0.0f, false);
		CRITTER_TRACENEW("CritterDesync:  m_retryPath set.");
		m_retryPath = true;
	}

	if (theNewPath) {
		CRITTER_TRACE("CritterDesync:  There is a theNewPath");
		destroyPath();
		m_path = theNewPath;
		if (m_curLocomotor && m_curLocomotor->isUltraAccurate()) {
			((Rva003638BA *)theNewPath)->rva003638FD(&originalDestination);
			CRITTER_TRACE("CritterDesync:  bblah1");
		}
		setLocomotorGoalPositionOnPath();
		Bool moveAllies = m_path->m_blockedByAlly && !((getObject()->getTemplate()->m_kindof[0] & 0x40000000U) != 0);
		if (((getObject()->getTemplate()->m_kindof[3] & 0x2000U) != 0)) {
			CRITTER_TRACE("CritterDesync:  bblah2");
			if (!TheAI->getAiData()->m_hordesWaitForHordes) {
				CRITTER_TRACE("CritterDesync:  bblah3");
				moveAllies = false;
			}
		}
		if (getObject()->getTemplate()->m_crushAllies || ((getObject()->getTemplate()->m_kindof[3] & 0x20000000U) != 0)) {
			CRITTER_TRACE("CritterDesync:  bblah4");
			moveAllies = true;
		}
		if (((getObject()->getTemplate()->m_kindof[4] & 0x800U) != 0)) {
			CRITTER_TRACE("CritterDesync:  bblah5");
			moveAllies = false;
		}
		Object *obj = getObject();
		if (obj->testStatus(OBJECT_STATUS_39) || obj->testStatus(OBJECT_STATUS_32) || obj->isKindOf(KINDOF_84))
			moveAllies = false;
		if (moveAllies) {
			CRITTER_TRACE("CritterDesync:  bblah6");
			Object *mover = getObject();
			TheAI->pathfinder()->MoveAllies(mover, m_path, mover->rva0028CE7B() >= 4);
		}
	} else {
		CRITTER_TRACE("CritterDesync:  There isn't a theNewPath");
		if (m_path && m_blockedFrames > 0) {
			CRITTER_TRACE("CritterDesync:  bblah7");
			destroyPath();
			setQueueForPathTime(BfmeLogicFramesPerSecond);
			Coord3D goalPos = *getObject()->getPosition();
			Rva002EDE5B(getObject(), &goalPos);
			setFinalPosition(&goalPos);
			setLocomotorGoalNone();
			m_blockedFrames = 0;
			m_isBlockedAndStuck = false;
		}
	}

	m_pathTimestamp = TheGameLogic->getFrame();
	m_blockedFrames = 0;
	m_isBlockedAndStuck = false;
	if (m_path) {
		CRITTER_TRACE("CritterDesync:  Returning true because m_path");
		return true;
	}
	CRITTER_TRACE("CritterDesync:  Returning false because !m_path");
	return false;
}
