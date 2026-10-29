// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@DelayedLuaEventUpdate@@UBE?AW4NameKeyType@@XZ @0x4A8D99
// (69B): cached pool-name key for DelayedLuaEventUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DelayedLuaEventUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

class Thing;
class ModuleData;
class Object;
class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleBase
{
public:
	UpdateModuleBase(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModuleBase();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class UpdateModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class UpdateModuleInterface2
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public UpdateModuleBase,
		     public UpdateModuleInterface1,
		     public UpdateModuleInterface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DelayedLuaEventList
{
public:
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
	DelayedLuaEventList &rva004A8DDE(const DelayedLuaEventList &other);

private:
	char m_pad[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DelayedLuaEventUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004A8F0B(unsigned int f20, const DelayedLuaEventList &events, UpdateSleepTime sleep, float f70, bool f74, bool f75);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_event;			// +0x20
	DelayedLuaEventList m_events;	// +0x24
	float m_range;			// +0x70
	bool m_f74;			// +0x74
	bool m_f75;			// +0x75
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@DelayedLuaEventUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedLuaEventUpdate::getModuleNameKey() const
{
	static NameKeyType TheDelayedLuaEventUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DelayedLuaEventUpdate");
	return TheDelayedLuaEventUpdatePoolKey;
}
