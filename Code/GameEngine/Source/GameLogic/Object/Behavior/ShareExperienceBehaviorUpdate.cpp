// cl: /O1 /DNDEBUG /MD
//
// ?update@ShareExperienceBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x0047FF6B, 71 bytes: slot 0 of the update-interface vtable 0x00C485B0
// that ShareExperienceBehavior's ctors (0x0047FE32, 0x0047FF2B) install at
// +0x10. It only reports "ShareExperienceBehavior::update" through the Debug
// singleton (the DevastateSpecialPowerSlots.cpp reporting shape) and sleeps
// forever: the behavior does its work elsewhere.
typedef int Int;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Debug
{
public:
	static Bool SkipNext(Bool skip);
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(Int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug *slot6C(Int first, Int second, Int third);
};

extern Debug *theDebug;

Bool bfmeRva000387C0(void);

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
private:
	unsigned char m_pad04[0x10 - 4];
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ShareExperienceBehavior : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime ShareExperienceBehavior::update()
{
	if (bfmeRva000387C0())
	{
		Debug::SkipNext(true);
		theDebug->slot60();
		theDebug->slot6C(0, 0, 0)->slot38("ShareExperienceBehavior::update").slot4C(2);
	}
	return UPDATE_SLEEP_FOREVER;
}
