// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1DelayedLuaEventUpdate@@UAE@XZ, retail 0x004A8D4A, 73 bytes.
// Behavior dtor: restores the own vtable group at +0/+0x0C/+0x10
// (0x00853A5C plus 0x007EFF90 plus 0x00853A50), tears down the
// DelayedLuaEventList member at +0x24 through the pinned 0xB6DD2 body
// (Rva00B6DD2 pin), then calls the rowed UpdateModule base dtor at
// 0x0024A797. Empty derived body; the list is the only tracked member
// giving EH state 0 exactly as retail. Shape follows the landed
// DynamicShroudClearingRangeUpdateDtor (compiler MI vptr group ahead of
// EH state plus implicit member plus base). Layout from the rowed ctor
// 0x004A8E7B (UpdateModule base 0x20 plus m_f20 +0x20 plus events +0x24
// size 0x4C plus m_f70 +0x70 plus flags +0x74/+0x75) joined to the BFME1
// DelayedLuaEventUpdateDestructors donor. Caller is the slot-0 ??_G at
// 0x004A8EEF (vtable 0x00853A5C).

class Thing;
class ModuleData;
class Object;

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
	virtual ~UpdateModule();

protected:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class Rva00B6DD2
{
public:
	virtual ~Rva00B6DD2();

private:
	char m_pad[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DelayedLuaEventUpdate();

private:
	unsigned int m_f20;
	Rva00B6DD2 m_events;
	float m_f70;
	bool m_f74;
	bool m_f75;
};

DelayedLuaEventUpdate::~DelayedLuaEventUpdate()
{
}
