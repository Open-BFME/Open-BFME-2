// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0SlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045D4B4, 266 bytes.
// SlowDeathBehavior EH ctor over the rowed UpdateModule base (0x253390, thing
// plus data): two-phase +0x20/+0x24 slots (interim ints 0x81C780/0x84EF80
// first, vtable constants second, FakePathfind/RebuildHole precedent), shared
// -1/zero run (-1 via or, 5 ints via xor+mov, 2 bools via al), vtable group
// (0x842040/0x842DA8/0x842034/0x842030/0x842020), float 1.0 plus 99999, then
// probability check (ModuleData+0x3C from rowed ModuleDataCtor 0x45E386 with
// table 0xC42290) throwing INIException(3) via rowed 0x2F681, then 4 vector
// emptiness checks (ModuleData+0x7C/+0xAC/+0xDC/+0x10C last-phase vectors,
// SimpleVec::empty inline giving lea+mov+cmp) setting +0x40, then setWakeFrame
// via rowed 0x44DF71 with 0x3FFFFFFF. Donor is BFME1 SlowDeathBehavior.cpp:172
// plus reference thunk facade (0x7C layout); BFME2 adds members/branches so
// retail is followed. Callers proving class: friend_new 0x24B264 plus Ship
// 0x45E9AA plus GiantBird 0x461E58 plus ClearanceTesting 0x483D39.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	const void *m_vtable; // +0x00
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	const void *m_p0C; // +0x0C
	const void *m_p10; // +0x10
	unsigned char m_pad14[0x20 - 0x14]; // +0x14..0x20 base members via rowed ctor
	void setWakeFrame(Object *obj, UpdateSleepTime wake);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

	char *mFailureMessage;
	int m_argCount;
};

struct SimpleVec
{
	void *m_begin;
	void *m_end;
	bool empty() const { return m_begin == m_end; }
};

struct SlowDeathBehaviorModuleDataFacade
{
	unsigned char m_pad00[0x3C];
	int m_probabilityModifier; // +0x3C
	unsigned char m_pad40[0x7C - 0x40];
	SimpleVec m_fx3; // +0x7C (FX[3]: 0x58+3*0x0C)
	unsigned char m_pad84[0xAC - 0x84];
	SimpleVec m_ocl3; // +0xAC (OCL[3])
	unsigned char m_padB4[0xDC - 0xB4];
	SimpleVec m_weapon3; // +0xDC (Weapon[3])
	unsigned char m_padE4[0x10C - 0xE4];
	SimpleVec m_sound3; // +0x10C (Sound[3])
};

class SlowDeathBehavior : public UpdateModule
{
public:
	SlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20; // +0x20
	const void *m_secondary24; // +0x24
	int m_28; // +0x28
	int m_2C; // +0x2C
	int m_30; // +0x30
	int m_34; // +0x34
	float m_38; // +0x38 1.0f
	int m_3C; // +0x3C 0
	bool m_40; // +0x40 hasLoadedEffect
	unsigned char m_pad41[3];
	int m_44; // +0x44 99999
	bool m_48; // +0x48
	unsigned char m_pad49[3];
	int m_4C; // +0x4C -1
};

// ??0SlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045D4B4
SlowDeathBehavior::SlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_secondary20;
	int *slot24 = (int *)&m_secondary24;
	*slot20 = 0x00C1C780;
	*slot24 = 0x00C4EF80;
	m_4C = -1;
	m_3C = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_40 = false;
	m_48 = false;
	m_vtable = (const void *)0x00C42040;
	m_p0C = (const void *)0x00C42DA8;
	m_p10 = (const void *)0x00C42034;
	m_secondary20 = (const void *)0x00C42030;
	m_secondary24 = (const void *)0x00C42020;
	m_38 = 1.0f;
	m_44 = 99999;

	const SlowDeathBehaviorModuleDataFacade *facade =
		(const SlowDeathBehaviorModuleDataFacade *)m_moduleData;
	if (facade->m_probabilityModifier < 1)
		throw INIException(3, "ProbabilityModifer must be >= 1.\n");

	if (!facade->m_fx3.empty())
		m_40 = true;
	if (!facade->m_ocl3.empty())
		m_40 = true;
	if (!facade->m_weapon3.empty())
		m_40 = true;
	if (!facade->m_sound3.empty())
		m_40 = true;

	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
