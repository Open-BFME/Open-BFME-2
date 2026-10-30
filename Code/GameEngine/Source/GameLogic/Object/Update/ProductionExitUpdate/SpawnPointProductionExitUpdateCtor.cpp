// cl: /DNDEBUG /MD /GX
//
// ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A3C1B, 179 bytes. Behavior-side ctor completing the
// SpawnPointProductionExitUpdate file-unit (behavior instance factory
// rowed at 0x24ECEC news 0xF4 with this pinned 2-arg ctor as its sole
// caller; poolkey rowed at 0x4A3BD6; bone methods rowed at 0x4A3CEA,
// 0x4A3F04 and 0x4A3F3B).
//
// Shape follows the MI-virtual installer pattern over the rowed
// UpdateModule base 0x253390 (whose three internal vptrs the opaque call
// installs, then this TU's derived virtuals reinstall): the compiler
// places its +0/+0x0C/+0x10/+0x20 installs ahead of the member array,
// which is built through the rowed ehvec iterator 0x629512 (opaque
// element ctor/dtor keep the frame while the element addresses stay
// DIR32 slots; the element spells the folded Coord3D rows at
// 0x47A6A9/0xB3FD0). An int zero at +0x28 plus a byte zero at +0x24 ride
// the init list around the installs, then a fused zero loop over the
// points plus the float/int tails, then the setWakeFrame tail (m_object
// at +0x08, 0x3FFFFFFF never-wake literal; the loop fences its pushes
// together). /GX for the EH prologue plus the two state stores
// (and-early for the base, byte-mid for the array); the declared-only
// base dtor arms them with no emitted code. Zero new pins (base ctor,
// ehvec iterator and element ctor/dtor resolve via their rows;
// setWakeFrame resolves via the existing IAEX Object-uint pin at
// 0x44DF71). Row supersedes the ctor pin.

#define COORD3D_VIEW_DTOR
#include "../../../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../Common/Thing/thing.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

class Thing;
class ModuleData;
class Object;
class ThingTemplate;

enum { MAX_SPAWN_POINTS = 10 };

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

enum DisabledType
{
	DISABLED_HELD = 3
};

class Object
{
public:
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	void setDisabled(DisabledType type);
	char m_pad[0x74];
	ObjectID m_id;
};

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1,
	DOOR_1 = 0
};

class SpawnB1
{
public:
	virtual void spawnAnchor1() {}
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpawnB2
{
public:
	virtual void spawnAnchor2() {}
};

class SpawnB3
{
public:
	virtual void spawnAnchor3() {}
protected:
	char m_pad[0x0C];
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule : public SpawnB1, public SpawnB2, public SpawnB3
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

// +0x20: the exit interface (ExitInterface; slot 0 is not recovered here, and the
// placeholder name keeps its vtable apart from the other units' ExitInterface views).
class SpawnB4
{
public:
	virtual void spawnAnchor4() {}
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
};

class SpawnPointProductionExitUpdate : public UpdateModule, public SpawnB4
{
public:
	SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

	virtual NameKeyType getModuleNameKey() const;

	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject);
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);

protected:
	virtual ~SpawnPointProductionExitUpdate();

private:
	void initializeBonePositions();
	void revalidateOccupiers();

	bool m_bonesInitialized;								// +0x24
	int m_spawnPointCount;									// +0x28
	Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];		// +0x2C
	float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];		// +0xA4
	ObjectID m_spawnPointOccupier[MAX_SPAWN_POINTS];		// +0xCC
};


// ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A3C1B
SpawnPointProductionExitUpdate::SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_spawnPointCount(0)
	, m_bonesInitialized(false)
{
	float fzero = 0.0f;
	ObjectID *pointOccupier = &m_spawnPointOccupier[0];
	float *pointZ = &m_worldCoordSpawnPoints[0].z;
	for (int n = MAX_SPAWN_POINTS; n != 0; ++pointOccupier, pointZ += 3, --n)
	{
		pointZ[-2] = fzero;
		pointZ[-1] = fzero;
		pointZ[0] = fzero;
		*pointOccupier = INVALID_OBJECT_ID;
		((float *)pointOccupier)[-MAX_SPAWN_POINTS] = fzero;
	}
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
