// cl: /MD
//
// ??1QueueProductionExitUpdate@@MAE@XZ, retail 0x0049FFF7, 32 bytes.
// Destructor completing the QueueProductionExitUpdate file-unit (ctor rowed
// at 0x4A010E, update/isFreeToExit/reserveDoor/getRallyPoint placed).
//
// Donor: ZH QueueProductionExitUpdate.cpp trivial dtor plus BFME1
// QueueProductionExitUpdateDestructorThunk shape. The body restores the four
// vtable pointers of the complete object -- the derived slot at +0x00 plus
// the BehaviorModuleOther slot at +0x0C, the UpdateModuleInterface slot at
// +0x10 and the ExitInterface slot at +0x20 -- then tail-jumps to the
// UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ at
// 0x0024A797). The ExitInterface base has a trivial destructor, so it
// contributes a store but no call. Recipe: InvisibilityUpdateDtor.cpp.

class Thing;
class ModuleData;
class Object;
class ThingTemplate;
struct Coord3D;
enum ExitDoorType
{
	DOOR_1 = 0,
	DOOR_NONE_AVAILABLE = -1
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
template<int N> class BitFlags
{
};
typedef BitFlags<11> DisabledMaskType;

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class UpdateModuleInterface
{
public:
	// Slot order copied from ZH GameLogic/Module/UpdateModule.h
	// (the header the kept QueueProductionExitUpdate.cpp compiles): update
	// first, then getDisabledTypesToProcess. The {for UpdateModule} vtable
	// slice must hold these two refs.
	virtual UpdateSleepTime update() = 0;
	virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
	virtual UpdateSleepTime update() = 0;
	virtual DisabledMaskType getDisabledTypesToProcess() const;
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

#include "../../../../Include/GameLogic/Module/ExitInterface.h"

class QueueProductionExitUpdate : public UpdateModule, public ExitInterface
{
protected:
	virtual ~QueueProductionExitUpdate();
public:
	// Redeclared (never defined here) so each secondary-vtable slot references
	// the QueueProductionExitUpdate:: body the kept QueueProductionExitUpdate.cpp
	// defines.
	virtual UpdateSleepTime update();
	virtual bool isExitBusy() const;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject);
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
	virtual void exitObjectByBudding(Object *newObj, Object *budHost);
	virtual void unreserveDoorForExit(ExitDoorType exitDoor);
	virtual void setRallyPoint(const Coord3D *pos);
	virtual const Coord3D *getRallyPoint() const;
	virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset) const;
	virtual bool getExitPosition(Coord3D &exitPosition, float &exitAngle) const;
};

QueueProductionExitUpdate::~QueueProductionExitUpdate()
{
}
