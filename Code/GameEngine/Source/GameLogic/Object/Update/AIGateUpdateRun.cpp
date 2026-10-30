// cl: /O1 /DNDEBUG /MD

// WB122EF60 AIGateUpdate::update and native173B4B0C27..4B0CD4.
// The module update interface starts at10. The opener cache and two counters
// are native fields; Actor slot names and counters remain unasserted.
// WB enclosing enabled branch closes the old bank's early-fail placement.
class Player;

enum Relationship { RELATION_0,RELATION_1,RELATION_2 };
class Object
{
public:
	Relationship getRelationship(const Object *) const;
	Player *getControllingPlayer() const;
	char m_pad00[0x38];
	float px; // +0x38
	float py; // +0x3C
	float pz; // +0x40
	float angle; // +0x44
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class Actor
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual bool s6();
	virtual bool s7();
	virtual bool s8();
	virtual void s9();
	virtual bool s10();
};

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
UpdateSleepTime AIGateUpdate::update()
{
	if (enabled == 0) {
		Object *obj = getObject();
		Player *player = obj->getControllingPlayer();
		Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(player);
		int wide;
		if (rec != 0 && getOpener() != 0)
			wide = 1;
		else
			wide = 0;
		enabled = (unsigned char)wide;
	}
	if (enabled) {
	if (loaded == 0)
		loadTrigger();

	Actor *actor = (Actor *)getOpener();
	if (actor->s10()) {
		actor = (Actor *)getOpener();
		if (actor->s6()) {
			if (count28 == 0 && count2C > 0) {
				actor = (Actor *)getOpener();
				actor->s8();
			}
		} else if (count28 > 0) {
			actor = (Actor *)getOpener();
			actor->s7();
		}
	}
	return (UpdateSleepTime)1;
 }
 return UPDATE_SLEEP_FOREVER;
}
