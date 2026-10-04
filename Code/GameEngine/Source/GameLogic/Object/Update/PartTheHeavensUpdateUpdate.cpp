// cl: /O1 /DNDEBUG /MD
//
// PartTheHeavensUpdate::update, retail 0x004ACBB3 (53 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00C54D98, so `this` is that
// subobject (module data at -0x0C). Sleeps forever without module data;
// otherwise, with the frames since the start frame at +0x20 (TheGameLogic
// +0x40 is the frame), runs the pinned rva004ACADA first on the start frame
// itself and then the class's 0x004AC9FA (pinned by address) with that
// count, staying awake.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;		// +0x40
};
extern GameLogic *TheGameLogic;
class Object;
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
	unsigned char m_pad14[0x20 - 0x14];
};
class PartTheHeavensUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	void rva004ACADA();
	void rva004AC9FA(int elapsed);
	unsigned int m_startFrame;	// +0x20
};
UpdateSleepTime PartTheHeavensUpdate::update()
{
	if (m_moduleData == 0)
		return UPDATE_SLEEP_FOREVER;
	int elapsed = TheGameLogic->getFrame() - m_startFrame;
	if (elapsed == 0)
		rva004ACADA();
	rva004AC9FA(elapsed);
	return UPDATE_SLEEP_NONE;
}
