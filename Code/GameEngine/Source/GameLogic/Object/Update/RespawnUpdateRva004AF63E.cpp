// ?triggerDeathBeforeRespawn@RespawnUpdate@@QAEXXZ @0x004AF63E 350B.
// RespawnUpdate death entry called by RespawnBody::apply. State 0 or 4
// looks the object's experience level up in the module-data rule tree at
// +0x10C (the same RespawnRule ctor the parser uses: cost 0 time 0 health
// 1.0 autoSpawn false). A miss retries level 1 and otherwise sleeps forever.
// A hit applies the +0x0C condition words, the death FX at +0xF0, the hero
// death UI, disabled-4, effectively-dead, and status 3, then copies the
// rule into this module. The controlling player's +0x738 table records the
// tracker's +0x28 into the slot chosen by the unrowed helper 0x0037F2C0.

enum DisabledType;
enum ObjectStatusTypes;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Object;
class Player;
class FXList;
class InGameUI;

class ExperienceTracker
{
public:
	char m_pad00[0x24];
	int m_level;
	int m_28;
};

class Object
{
public:
	void rva001E431E(const int *conditions);
	void setDisabled(DisabledType type);
	void setEffectivelyDead(bool dead);
	void setStatus(ObjectStatusTypes bit, bool flag);
	Player *getControllingPlayer() const;

	char m_pad00[0x264];
	ExperienceTracker *m_experienceTracker;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class InGameUI
{
public:
	void rva002A1283(Object *obj);
};

extern InGameUI *TheInGameUI;

struct RespawnRule
{
	unsigned level;
	unsigned cost;
	int time;
	float health;
	bool autoSpawn;

	RespawnRule(unsigned ruleLevel = 1)
		: level(ruleLevel), cost(0), time(0), health(1.0f), autoSpawn(false) {}
};

class BFME2RespawnRuleTree
{
public:
	void *find(const unsigned int &key) const;
	void *sentinel;
};

struct RespawnRuleNode
{
	char m_pad00[0x10];
	unsigned m_level;
	unsigned m_cost;
	int m_time;
	unsigned m_healthBits;
	bool m_autoSpawn;
};

class RespawnUpdateModuleData
{
public:
	char m_pad00[0x0C];
	int m_conditions0C[19];
	int m_conditions58[19];
	char m_padA4[0xF0 - 0xA4];
	const FXList *m_fx;
	char m_padF4[0x10C - 0xF4];
	BFME2RespawnRuleTree m_rules;
};

class Rva0037F2C0
{
public:
	int rva0037F2C0(Object *obj, bool autoSpawn);
};

class Rva0037E421
{
public:
	void *rva0037E421(int index);
};

struct RevivalSlot
{
	char m_pad00[0xC8];
	int m_c8;
};

class UpdateModule
{
public:
	void *m_vtable;
	const RespawnUpdateModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

class RespawnUpdate : public UpdateModule
{
public:
	void triggerDeathBeforeRespawn();

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

void RespawnUpdate::triggerDeathBeforeRespawn()
{
	const RespawnUpdateModuleData *data = m_moduleData;
	Object *obj = m_object;
	if (m_2C != 0 && m_2C != 4)
		return;

	RespawnRule rule((unsigned)obj->m_experienceTracker->m_level);
	RespawnRuleNode *found = (RespawnRuleNode *)data->m_rules.find(rule.level);
	RespawnRuleNode *end = (RespawnRuleNode *)data->m_rules.sentinel;
	if (found == end)
	{
		rule.RespawnRule::RespawnRule(1);
		found = (RespawnRuleNode *)data->m_rules.find(rule.level);
		if (found == end)
		{
			setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
			return;
		}
	}

	obj->rva001E431E(data->m_conditions0C);
	FXList::doFXObj(data->m_fx, obj, 0);
	if (TheInGameUI)
		TheInGameUI->rva002A1283(obj);
	obj->setDisabled((DisabledType)4);
	obj->setEffectivelyDead(true);
	obj->setStatus((ObjectStatusTypes)3, true);

	m_40 = found->m_autoSpawn == 0;
	m_38 = (unsigned)found->m_time;
	m_3C = found->m_cost;
	*(unsigned *)&m_20 = found->m_healthBits;

	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;

	char *table = (char *)player + 0x738;
	int index = ((Rva0037F2C0 *)table)->rva0037F2C0(obj, m_40 == 0);
	ExperienceTracker *tracker = obj->m_experienceTracker;
	if (tracker == 0)
		return;
	RevivalSlot *slot = (RevivalSlot *)((Rva0037E421 *)table)->rva0037E421(index);
	if (slot == 0)
		return;
	slot->m_c8 = tracker->m_28;
}
