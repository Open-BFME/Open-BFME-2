// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva002657CE@AIUpdateInterface@@QAEXXZ, retail 0x002657CE..0x0026594F (385B),
// thiscall, EH.
//
// Rebuilds the AI's path from the state machine's goal path: the old path is
// deleted (rowed ~Path 0x00364A89 and operator delete), a new 0x28-byte Path
// (rowed ctor 0x00363DC8) starts at the object's position on the ground layer
// (rowed appendNode 0x002655E3 with the 0x7FFFFFFF third argument), is
// prepared for the current locomotor's surfaces (pinned 0x00364551), then
// takes every goal path position (pinned AIStateMachine::getGoalPathPosition
// 0x00346FA5 over the 12-byte goal vector at +0x3C/+0x40 of the state machine
// at +0x30) on the layer TerrainLogic::getLayerForDestination 0x002802FE
// picks. With TheGlobalData +0x9B8 == 1 the path becomes the pathfinder's
// debug path (rowed SetDebugPath 0x002EDEAB). The path is finished along the
// object's 2D facing (rowed Thing::getUnitDirectionVector2D 0x0030A2A2, pinned
// 0x00365E98), the path timestamp +0x160 takes the logic frame, this's slot
// 131 runs and +0x16C is cleared.
//
// Evidence (target): the body follows setPathFromWaypoint 0x0026569F
// (AIUpdateInterface_setPathFromWaypoint.cpp: same object +0x08, m_path
// +0x140, Path node calls and TheAI pathfinder +0x10); the current locomotor
// is +0x1F0 with its template at +0x04 (surfaces +0x14). No direct caller or
// WorldBuilder name was found; the method name stays address-derived.

#include "Coord3D.h"

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

class Path
{
public:
	Path();
	~Path();
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int extra);	// appendNode
	void rva00364551(Object *obj, int surfaces, Bool flag, const float *extra);
	void rva00365E98(Object *obj, const Coord3D *dir, int surfaces, Bool flag);
private:
	unsigned char m_pad00[0x28];
};

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &dir) const;
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;						// +0x38
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva002EDEABArg;

class Pathfinder
{
public:
	void SetDebugPath(Rva002EDEABArg *path);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;				// +0x10
};
extern AI *TheAI;

class GlobalData
{
public:
	unsigned char m_pad000[0x9B8];
	Int m_debugAI;							// +0x9B8
};
extern GlobalData *TheWritableGlobalData;

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// STLport vector<Coord3D> view of the goal path.
struct GoalPathVector
{
	Int size() const { return _M_finish - _M_start; }
	Coord3D *_M_start;
	Coord3D *_M_finish;
	Coord3D *_M_end_of_storage;
};

class AIStateMachine
{
public:
	const Coord3D *getGoalPathPosition(Int i) const;
	Int getNumGoalPathPositions() const { return m_goalPath.size(); }
private:
	unsigned char m_pad00[0x3C];
	GoalPathVector m_goalPath;				// +0x3C
};

struct LocomotorTemplateView
{
	unsigned char m_pad00[0x14];
	Int m_surfaces;							// +0x14
};

struct LocomotorView
{
	unsigned char m_pad00[0x04];
	LocomotorTemplateView *m_template;		// +0x04
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterface
{
public:
	PAD_VIRTUALS10(a0) PAD_VIRTUALS10(a1) PAD_VIRTUALS10(a2) PAD_VIRTUALS10(a3)
	PAD_VIRTUALS10(a4) PAD_VIRTUALS10(a5) PAD_VIRTUALS10(a6) PAD_VIRTUALS10(a7)
	PAD_VIRTUALS10(a8) PAD_VIRTUALS10(a9) PAD_VIRTUALS10(b0) PAD_VIRTUALS10(b1)
	PAD_VIRTUALS10(b2)
	virtual void b30();
	virtual void slot131();					// +0x20C

	void rva002657CE();

protected:
	Object *getObject() const { return m_object; }

private:
	unsigned char m_pad04[0x08 - 0x04];
	Object *m_object;						// +0x08
	unsigned char m_pad0C[0x30 - 0x0C];
	AIStateMachine *m_stateMachine;			// +0x30
	unsigned char m_pad34[0x140 - 0x34];
	Path *m_path;							// +0x140
	unsigned char m_pad144[0x160 - 0x144];
	unsigned int m_pathTimestamp;			// +0x160
	unsigned char m_pad164[0x16C - 0x164];
	Int m_blockedFrames;					// +0x16C
	unsigned char m_pad170[0x1F0 - 0x170];
	LocomotorView *m_curLocomotor;			// +0x1F0
};

void AIUpdateInterface::rva002657CE()
{
	Object *obj = getObject();
	LocomotorView *locomotor = m_curLocomotor;
	if (m_path)
	{
		delete m_path;
		m_path = 0;
	}
	m_path = new Path;
	m_path->rva002655E3(obj->getPosition(), LAYER_GROUND, 0x7FFFFFFF);
	m_path->rva00364551(obj, locomotor->m_template->m_surfaces, false, 0);
	for (Int i = 0; i < m_stateMachine->getNumGoalPathPositions(); i++)
	{
		Coord3D pos;
		const Coord3D *goal = m_stateMachine->getGoalPathPosition(i);
		pos.x = goal->x;
		pos.y = goal->y;
		pos.z = goal->z;
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &pos);
		m_path->rva002655E3(&pos, layer, 0x7FFFFFFF);
	}
	if (TheWritableGlobalData->m_debugAI == 1)
		TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	Coord3D dir;
	obj->getUnitDirectionVector2D(dir);
	m_path->rva00365E98(obj, &dir, locomotor->m_template->m_surfaces, false);
	m_pathTimestamp = TheGameLogic->getFrame();
	slot131();
	m_blockedFrames = 0;
}
