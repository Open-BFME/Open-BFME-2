// ?rva004CE0D9@UnleashSpecialPower@@UAE_NH@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX
//
// ?rva004CE0D9@UnleashSpecialPower@@UAE_NH@Z, retail 0x004CE0D9, 177 bytes:
// slot 8 of the vtable 0x00C5FD98 that UnleashSpecialPower's ctor 0x004CE006
// installs at +0x20 (the argument unread). Through the owner's
// "SlaveWatcherBehavior" module (key cached in a function static, rowed
// nameToKey 0x00148E1A and Object::findModule 0x0028B6D6) it finds the
// watched slaver (the module's +0x20 ObjectID, getter 0x0030D377 pinned) and
// answers true when the slaver is alive (bit 0 of +0x438 clear) and none of
// its behavior modules (the null-terminated +0x244 list) hands out, from
// slot 26 of its +0x0C interface, an interface whose slot 7 answers true.
// Compiled with the +0x20 subobject this. Names by address.
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectID
{
	INVALID_ID = 0
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

class Rva004CE0D9Answer
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual Bool rva004CE0D9Slot7();
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
	virtual Rva004CE0D9Answer *rva004CE0D9Slot26();
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
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x438 - 0x248];
	unsigned char m_438; // +0x438
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

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class Rva004CE0D9Interface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual Bool rva004CE0D9(int unused) = 0;
};

class UnleashSpecialPower : public SpecialPowerModule, public Rva004CE0D9Interface
{
public:
	virtual Bool rva004CE0D9(int unused);
};

static inline Bool rva004CE0D9Free(Object *slaver)
{
	for (BehaviorModule **m = slaver->getBehaviorModules(); *m; ++m)
	{
		Rva004CE0D9Answer *answer = (*m)->getInterface()->rva004CE0D9Slot26();
		if (answer && answer->rva004CE0D9Slot7())
			return false;
	}
	return true;
}

Bool UnleashSpecialPower::rva004CE0D9(int unused)
{
	Object *obj = m_object;
	if (obj == 0)
		return false;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	SlaveWatcherBehavior *watcher = (SlaveWatcherBehavior *)obj->findModule(key);
	if (watcher == 0)
		return false;
	Object *slaver = TheGameLogic->findObjectByID(watcher->rva0030D377());
	if (slaver == 0 || (slaver->m_438 & 1))
		return false;
	return rva004CE0D9Free(slaver);
}
