// cl: /DNDEBUG /MD /GX
// ??0Rva004DF418@@QAE@PAVThing@@PBVModuleData@@@Z @0x004DF418 (104B):
// ObjectHelper-derived module ctor. Base ctor 0x0028C8DF; m_24 member init
// 0x0029FB3B; setWakeFrame resolved to the 0x0044DF71 pin. The vptr/pointer
// stores land before the m_24 construction because they are member
// initializers declared ahead of m_24; m_20 stays in the body. Evidence:
// callers/callees rowed; banked attempt 0x004df418.cpp.
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
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);
	~ObjectHelper();
};

class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(void *context) { init(context); }
	~Rva0029FB3BMember();
	void *init(void *context);
	void *m_head;
};

static int s_secondary0C;
static int s_10;
extern const void *const g_00C61588[];

class Rva004DF418 : public ObjectHelper
{
public:
	Rva004DF418(Thing *thing, const ModuleData *moduleData);
private:
	const void *m_vtable;
	int m_pad04;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_tailPad[0x20 - 0x14];
	int m_20;
	Rva0029FB3BMember m_24;
};

Rva004DF418::Rva004DF418(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
	, m_vtable(g_00C61588)
	, m_p0C(&s_secondary0C)
	, m_p10(&s_10)
	, m_24((void *)((char *)&moduleData + 3))
{
	m_20 = 0;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C61588@@3QBQBXB=??_7Rva004DF324@@6B@")
