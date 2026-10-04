// cl: /O1 /DNDEBUG /MD /GX
//
// ?rva0045108D@UnleashSpecialPower@@UAEXXZ, retail 0x004CE18A, 187 bytes:
// slot 17 of UnleashSpecialPower's primary vtable 0x00C5FDC0 (ctor
// 0x004CE006), over the SpecialAbilityUpdate slot-17 base 0x0045108D (pinned;
// named by its address, like WoundArrowUpdateSlot17.cpp). After the base,
// through the owner's "SlaveWatcherBehavior" module (key cached in a function
// static, rowed nameToKey and Object::findModule) it finds the watched slaver
// (the module's +0x20 ObjectID, getter 0x0030D377 pinned) and, for each of
// the slaver's behavior modules (the null-terminated +0x244 list) whose +0x0C
// interface hands out an interface from slot 26, runs that interface's slot 6
// and sends the slaver's AI (+0x258) hunting (rowed AICommandInterface::aiHunt,
// command source 2).
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class UnleashSpecialPower;

class SlaveWatcherBehavior
{
public:
	ObjectID rva0030D377() const;
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiHunt(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};

class Rva004CE18AAnswer
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5();
	virtual void rva004CE18ASlot6();
};

class BehaviorModuleInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25();
	virtual Rva004CE18AAnswer *rva004CE18ASlot26();
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	BehaviorModuleInterface *getInterface() { return &m_interface; }
private:
	unsigned char m_pad04[0x0C - 4];
	BehaviorModuleInterface m_interface; // +0x0C
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	AIUpdateInterface *getAI() const { return m_ai; }
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai; // +0x258
protected:
	Module *findModule(NameKeyType key) const;
	friend class UnleashSpecialPower;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ModuleData;

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void rva0045108D();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class UnleashSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
};

void UnleashSpecialPower::rva0045108D()
{
	SpecialAbilityUpdate::rva0045108D();
	Object *obj = m_object;
	if (obj == 0)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	SlaveWatcherBehavior *watcher = (SlaveWatcherBehavior *)obj->findModule(key);
	if (watcher == 0)
		return;
	Object *slaver = TheGameLogic->findObjectByID(watcher->rva0030D377());
	if (slaver == 0)
		return;
	for (BehaviorModule **m = slaver->getBehaviorModules(); *m; ++m)
	{
		Rva004CE18AAnswer *answer = (*m)->getInterface()->rva004CE18ASlot26();
		if (answer)
		{
			answer->rva004CE18ASlot6();
			AIUpdateInterface *ai = slaver->getAI();
			if (ai)
				ai->m_commands.aiHunt(CMD_FROM_AI);
		}
	}
}
