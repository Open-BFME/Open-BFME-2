// cl: /DNDEBUG /MD /EHsc

// ?getModuleNameKey@AIGateUpdate@@UBE?AW4NameKeyType@@XZ @0x4B087C
// (69B): cached pool-name key for AIGateUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AIGateUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

class Thing;
class ModuleData;
class GateOpener;
class Vector2;
class AIGateUpdateModuleData;

enum NameKeyType { NK_UNKNOWN = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_INVALID = 0, UPDATE_SLEEP_FOREVER = 0x3fffffff };

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void slot0() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

private:
	unsigned nextWake;
	int index;
	int reserved;
};

class AIGateUpdate : public UpdateModule
{
public:
	AIGateUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AIGateUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	GateOpener *getOpener();
	void loadTrigger();
	Vector2 rva004B0A24(float, float);
	static void triggerCallback(Object *, AIGateUpdate *, bool);

private:
	GateOpener *m_opener; // +0x20
	unsigned m_24;
	int count28;
	int count2C;
	bool loaded;
	unsigned char enabled;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@AIGateUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AIGateUpdate::getModuleNameKey() const
{
	static NameKeyType TheAIGateUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AIGateUpdate");
	return TheAIGateUpdatePoolKey;
}
