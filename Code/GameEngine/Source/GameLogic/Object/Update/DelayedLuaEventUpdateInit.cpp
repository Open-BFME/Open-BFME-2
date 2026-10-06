// cl: /DNDEBUG /MD /GX
// ?rva004A8F0B@DelayedLuaEventUpdate@@QAEXIABVDelayedLuaEventList@@W4UpdateSleepTime@@M_N2@Z @0x004A8F0B 71B
// __thiscall void (unsigned f20, const DelayedLuaEventList&, sleep, float, bool, bool):
// init m_f20/m_events/m_f70/m_f74/m_f75 plus setWakeFrame clamp.
// Evidence: chain lane (calls landed 0x004A8DDE copy); layout +0x20/+0x24(0x4C)/+0x70/+0x74/+0x75
// from rowed ctor 0x004A8E7B and dtor 0x004A8D4A; callees rowed (0x004A8DDE copy, 0x0044DF71 setWakeFrame);
// 6 stack args (ret 0x18); no vptr store so method not ctor; movss needs /arch:SSE.
class Thing;
class ModuleData;
class Object;

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
	const ModuleData *m_moduleData;
	Object *m_object;
};

class UpdateModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class UpdateModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class UpdateModule : public UpdateModuleBase,
		     public UpdateModuleInterface1,
		     public UpdateModuleInterface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

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
	~DelayedLuaEventList();
	DelayedLuaEventList &rva004A8DDE(const DelayedLuaEventList &other);

private:
	unsigned char m_data[0x4C];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);
	void rva004A8F0B(unsigned int f20, const DelayedLuaEventList &events, UpdateSleepTime sleep, float f70, bool f74, bool f75);

private:
	unsigned int m_f20;
	DelayedLuaEventList m_events;
	float m_f70;
	bool m_f74;
	bool m_f75;
};

void DelayedLuaEventUpdate::rva004A8F0B(unsigned int f20, const DelayedLuaEventList &events, UpdateSleepTime sleep, float f70, bool f74, bool f75)
{
	m_f20 = f20;
	m_events.rva004A8DDE(events);
	m_f74 = f74;
	m_f75 = f75;
	m_f70 = f70;
	UpdateSleepTime frame = (unsigned int)sleep > 0U ? sleep : UPDATE_SLEEP_NONE;
	setWakeFrame(m_object, frame);
}
