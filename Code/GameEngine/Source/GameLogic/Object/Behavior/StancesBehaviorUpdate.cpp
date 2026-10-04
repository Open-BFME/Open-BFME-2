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
	OBJECT_STATUS_5A = 0x5a
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
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
