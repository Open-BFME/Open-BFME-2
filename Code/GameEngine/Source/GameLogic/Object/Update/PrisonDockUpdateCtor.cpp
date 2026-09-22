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

static int s_prison0C;
static int s_prison10;

// Opaque UpdateModule (0x30 bytes); ctor resolves to the matched row at
// 0x00253390, setWakeFrame to the pin at 0x0044DF71.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, unsigned int frame);
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
	m_p0C = &s_prison0C;
	m_p10 = &s_prison10;
	m_i20 = zero;
	m_i24 = zero;
	m_i28 = zero;
	m_b2C = (unsigned char)zero;
	setWakeFrame(*(Object **)((char *)this + 8), 0x3FFFFFFF);
}

// ??1TemporarilyDefectUpdate@@ present-unmatched
TemporarilyDefectUpdate::~TemporarilyDefectUpdate()
{
}

// ??1UpdateModule@@ present-unmatched
UpdateModule::~UpdateModule()
{
}
