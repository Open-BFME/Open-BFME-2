// cl: /DNDEBUG /MD /GX
//
// ??1RainOfFireUpdate@@UAE@XZ, retail 0x004AC24D, 91 bytes.
// Dtor reinstalls primary 0x00854C74 plus secondaries 0x00854BB8/0x00854BA8
// plus +0x20 slot 0x00854BA0 then zeroes +0x2C and calls honest setter
// 0x004AC18D with 0.0 then rowed base 0x0024A797. Layout is the rowed
// 0x38-byte class (UpdateModule base 0x20 plus +0x20 secondary plus frame
// plus four floats); caller is the slot-0 deleting dtor at 0x004AC5D9.
// Recipe is the PartTheHeavensUpdateDtor MI pattern with the setter ride.

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class Secondary20
{
public:
	virtual void setFloat(float v);
};

class RainOfFireUpdate : public UpdateModule, public Secondary20
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual ~RainOfFireUpdate();
	void rva004AC18D(float value);

private:
	unsigned int frame;
	float darkness;
	float scale;
	float pending;
	float ramp;
};

RainOfFireUpdate::~RainOfFireUpdate()
{
	scale = 0.0f;
	rva004AC18D(0.0f);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?setFloat@Secondary20@@UAEXM@Z=?set@Rva00101CCCFloatField@@QAEXM@Z")
