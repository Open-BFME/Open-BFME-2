// cl: /O1 /DNDEBUG /MD
//
// Two WallUpgradeUpdate overrides on the interface vtables its matched ctor
// 0x004AB317 installs over UpdateModule: 0x00C54768 at +0x20 and 0x00C54764 at
// +0x24, each compiled with its subobject this. Names are by address.
//
// ?rva004AB3AE@WallUpgradeUpdate@@UAE_NXZ, retail 0x004AB3AE, 61 bytes: +0x24
// slot 0; whether our Object is of KindOf 0x109, 0x108 or 0x107.
// ?rva004AB3EB@WallUpgradeUpdate@@UAEXHHH@Z, retail 0x004AB3EB, 42 bytes:
// +0x20 slot 2; when the third argument rises above the second to 3, arms
// +0x2C with eight times the constant g_009BA4E4 and wakes the module
// (UpdateModule::setWakeFrame, UPDATE_SLEEP_NONE).

enum KindOfType
{
	KINDOF_107 = 0x107,
	KINDOF_108 = 0x108,
	KINDOF_109 = 0x109
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
};

extern const int g_009BA4E4;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva004AB3EBIface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void rva004AB3EB(int a1, int previous, int current) = 0;
};

class Rva004AB3AEIface
{
public:
	virtual bool rva004AB3AE() = 0;
};

class WallUpgradeUpdate : public UpdateModule, public Rva004AB3EBIface, public Rva004AB3AEIface
{
public:
	virtual void rva004AB3EB(int a1, int previous, int current);
	virtual bool rva004AB3AE();
private:
	int m_28;
	int m_2C; // +0x2C
	bool m_30;
	bool m_31;
};

// ?rva004AB3AE@WallUpgradeUpdate@@UAE_NXZ @0x004AB3AE
bool WallUpgradeUpdate::rva004AB3AE()
{
	Object *obj = m_object;
	return obj->isKindOf(KINDOF_109) || obj->isKindOf(KINDOF_108) || obj->isKindOf(KINDOF_107);
}

// ?rva004AB3EB@WallUpgradeUpdate@@UAEXHHH@Z @0x004AB3EB
void WallUpgradeUpdate::rva004AB3EB(int, int previous, int current)
{
	if (current > previous && current == 3)
	{
		m_2C = g_009BA4E4 * 8;
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}
