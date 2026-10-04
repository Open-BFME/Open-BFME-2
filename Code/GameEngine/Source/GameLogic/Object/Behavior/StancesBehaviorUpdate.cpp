// cl: /O1 /DNDEBUG /MD
//
// StancesBehavior::update, retail 0x0045F290 (49 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00C424D0, so `this` is that
// subobject (the Object at -0x08). Awake every frame while the Object has
// status 0x5A; otherwise, while the value at +0x30 is still zero, the
// class's 0x0045F084 (pinned by address) runs with 1 on the primary this,
// and the module sleeps forever.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_10 = 0x10,
	OBJECT_STATUS_5A = 0x5a
};
class AIUpdateInterface
{
public:
	void rva00262D40(int mode);
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;	// +0x258
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned char m_pad14[0x30 - 0x14];
};
class StancesBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva0045F084(int value);
	void rva0045F21C();
	void rva0045F235();
private:
	int m_30;			// +0x30
};
UpdateSleepTime StancesBehavior::update()
{
	Object *obj = m_object;
	if (obj && obj->testStatus(OBJECT_STATUS_5A))
		return UPDATE_SLEEP_NONE;
	if (m_30 == 0)
		rva0045F084(1);
	return UPDATE_SLEEP_FOREVER;
}

// ?rva0045F21C@StancesBehavior@@QAEXXZ, retail 0x0045F21C, 25 bytes.
// Stance selector over +0x30: 3 -> rva0045F084(5), 4 -> rva0045F084(1).
// Evidence: neighbours 0x0045F068/0x0045F290 same TU class and flags;
// callee rowed via pin 0x0045F084; caller 0x002673F6; LINK BONUS via.
void StancesBehavior::rva0045F21C()
{
	if (m_30 == 3)
		rva0045F084(5);
	else if (m_30 == 4)
		rva0045F084(1);
}

// ?rva0045F235@StancesBehavior@@QAEXXZ @0x0045F235 (91B).
// Gap between 0x0045F21C and update in same TU. Stance-gated AI guard-mode
// set: 5 -> rva0045F084(3), then 3/1/4 filter, Object at +8, status 0x10
// reject, AI at Object+0x258, mode 1 for stance 3/4 else 0 via rowed
// ?rva00262D40@AIUpdateInterface@@QAEXH@Z. Caller 0x00341E66.
void StancesBehavior::rva0045F235()
{
	if (m_30 == 5)
		rva0045F084(3);
	int stance = m_30;
	if (stance != 3 && stance != 1 && stance != 4)
		return;
	Object *obj = m_object;
	if (!obj)
		return;
	if (obj->testStatus(OBJECT_STATUS_10))
		return;
	AIUpdateInterface *ai = obj->m_ai258;
	if (!ai)
		return;
	int mode;
	if (stance == 3 || stance == 4)
		mode = 1;
	else
		mode = 0;
	ai->rva00262D40(mode);
}
