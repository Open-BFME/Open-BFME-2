// cl: /O1 /DNDEBUG /MD /GX
//
// ??0ObjectHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028C8DF, 84 bytes.
// ObjectHelper intermediate behavior base over the pinned UpdateModule base
// (0x253390, thing plus data): redo stores plus setWakeFrame(getObject(),
// UPDATE_SLEEP_FOREVER) via the 0x44DF71 pin, then the three most-derived
// vtable slots (address-of TU-local dummies, DIR32-masked). BFME1 donor is
// ObjectHelperCtor.cpp; BFME2 keeps the shape (EH frame, wake-forever, three
// stores). Six Helper-family behavior ctors call this base; the following
// name getter (0x28C933, "ObjectHelper") plus scalar-deleting dtor prove the
// cluster. Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// Opaque UpdateModule base; 2-arg ctor resolves to its pin. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order; m_object sits at +8 per the rowed getObject users.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
	Object *getObject() const { return m_object; }

	const void *m_vtable;
	int m_pad04;
	Object *m_object;
};

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p0C;
	const void *m_p10;
};

// ??0ObjectHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28C8DF
ObjectHelper::ObjectHelper(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
