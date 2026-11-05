// cl: /DNDEBUG /MD /EHsc
//
// ??0FiringTracker@@QAE@PAVThing@@PBVModuleData@@@Z @0x004DEB10 (149B).
// FiringTracker ctor over rowed UpdateModule base 0x00253390 with
// setWakeFrame FOREVER via rowed 0x0044DF71. Layout from matched xfer
// 0x004DEBC1 (UpdateModule base 0x20 plus consecutiveShots plus victimID
// plus victimPosition plus victimIsPosition plus auxID plus three frames
// plus lastShotPosition plus stopLooping plus audioHandle) and donor
// BFME1 FiringTrackerBFMECtor (Thing plus ModuleData plus zero plus
// FOREVER). Identity via vtable 0x00861530 at +0 plus pool key 0x004DEACB
// with FiringTracker string plus deleting dtor 0x004DEBA5. Neighbours
// FiringTrackerPoolKey 0x004DEACB and FiringTrackerDtor share flags.

typedef int ObjectID;
typedef int AudioHandle;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

// Canonical UpdateModule, as FiringTrackerDtor.cpp (the first copy of the
// class's tables in link order) reads it, so both units emit the same tables.
#include "../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../Include/Common/ObjectModule.h"

// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"

class FiringTracker : public UpdateModule
{
public:
	FiringTracker(Thing *thing, const ModuleData *data);

private:
	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
	unsigned char m_pad35[3];
	ObjectID m_auxiliaryObjectID;
	unsigned int m_frameToStartCooldown;
	unsigned int m_frameToForceReload;
	unsigned int m_lastShotFrame;
	Coord3D m_lastShotPosition;
	unsigned int m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
public:
	virtual ~FiringTracker();	// rowed elsewhere; declared so this unit binds to it
public:
	// retail slot 4: the rowed ?getModuleNameKey@FiringTracker@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual const char * GetSnapshotName() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
};

FiringTracker::FiringTracker(Thing *thing, const ModuleData *data) :
	UpdateModule(thing, data)
{
	m_consecutiveShots = 0;
	m_victimID = 0;
	m_victimPosition.zero();
	m_lastShotPosition.zero();
	m_victimIsPosition = false;
	m_auxiliaryObjectID = 0;
	m_frameToStartCooldown = 0;
	m_frameToForceReload = 0;
	m_lastShotFrame = 0;
	m_frameToStopLoopingSound = 0;
	m_audioHandle = 1;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
