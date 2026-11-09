// cl: /O1 /GX /MD /DNDEBUG
// Identity: ModuleFactory registers this module as "TemporarilyDefectUpdate" (addModule pairs
// the name with its factories); formerly misnamed PrisonDockUpdate.
// ??0TemporarilyDefectUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004CC6AF.
// UpdateModule-direct base (matched row 0x00253390) plus setWakeFrame pin;
// derived re-stores +0x0C/+0x10, zeroes trailing ints/byte via a shared zero
// register, then setWakeFrame. Factory stub order names it. UpdateModule is
// modeled single-vptr opaque (0x20 bytes); do NOT declare an explicit vptr.
class Thing;
class ModuleData;
class Object;

// The derived class re-stores its two secondary vptrs: retail 0x004CC6E0 stores VA 0x00BEFF90 (the shared
// BehaviorModuleInterface table) at +0x0C and VA 0x00C5F594 at +0x10. They were zero ints here, so
// Object::Object's slot-0 call on +0x0C jumped to address 0 (P115).
extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva004CC63A@@6BRva004CC63A_B2@@@")[];

// Opaque UpdateModule (0x30 bytes); ctor resolves to the matched row at
// 0x00253390, setWakeFrame to the pin at 0x0044DF71.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
};

class TemporarilyDefectUpdate : public UpdateModule
{
public:
	TemporarilyDefectUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~TemporarilyDefectUpdate();

private:
	int m_i20;
	int m_i24;
	int m_i28;
	unsigned char m_b2C;
};

TemporarilyDefectUpdate::TemporarilyDefectUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int zero = 0;
	m_p0C = __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7Rva004CC63A@@6BRva004CC63A_B2@@@");
	m_i20 = zero;
	m_i24 = zero;
	m_i28 = zero;
	m_b2C = (unsigned char)zero;
	setWakeFrame(*(Object **)((char *)this + 8), UPDATE_SLEEP_FOREVER);
}

// ??1TemporarilyDefectUpdate@@ present-unmatched
TemporarilyDefectUpdate::~TemporarilyDefectUpdate()
{
}
