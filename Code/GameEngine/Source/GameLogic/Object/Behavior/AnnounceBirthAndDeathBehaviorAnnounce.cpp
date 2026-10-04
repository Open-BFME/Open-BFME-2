// cl: /O1 /DNDEBUG /MD
//
// AnnounceBirthAndDeathBehavior's two announcements (vtables installed by the
// matched ctor 0x00485125 over the CreateModule base):
// onCreate, retail 0x004851AD (26 bytes): slot 0 of the +0x10 create-module
// interface table 0x00C4A550, and onDie, retail 0x004851C7 (28 bytes): slot 0
// of the +0x18 die-module interface table 0x00C4A54C. Each is compiled with
// its subobject this (the Object at +0x08 is [this-8] / [this-0x10]) and,
// when TheInGameUI and the Object exist, hands the Object to the InGameUI
// announcer for the "HeroInitialSpawn" (0x002A123F) or "HeroDeath"
// (0x002A1283) event; both InGameUI members are pinned by address on these
// call sites (each passes its event name literal and the UI's +0x9D0/+0x9E0
// settings to 0x0029F954).
class Object;
class DamageInfo;
class ModuleData;

class InGameUI
{
public:
	void rva002A123F(Object *obj);
	void rva002A1283(Object *obj);
};
extern InGameUI *TheInGameUI;

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
class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;
};
class CreateModule : public ModuleBase, public BehaviorModuleInterface, public CreateModuleInterface
{
protected:
	bool m_needToRunOnBuildComplete;	// +0x14
};
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};
class AnnounceBirthAndDeathBehavior : public CreateModule, public DieModuleInterface
{
public:
	virtual void onCreate();
	virtual void onDie(const DamageInfo *damageInfo);
};

void AnnounceBirthAndDeathBehavior::onCreate()
{
	if (TheInGameUI && m_object)
		TheInGameUI->rva002A123F(m_object);
}

void AnnounceBirthAndDeathBehavior::onDie(const DamageInfo *damageInfo)
{
	if (TheInGameUI && m_object)
		TheInGameUI->rva002A1283(m_object);
}
