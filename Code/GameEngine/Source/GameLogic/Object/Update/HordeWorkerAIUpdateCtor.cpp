// cl: /O1 /DNDEBUG /MD /GX
//
// ??0HordeWorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049AD15,
// 134 bytes. Behavior-side ctor (rowed instance factory 0x24E560 news
// 0x3F8 with this pinned 2-arg ctor as its sole raw caller at 0x24E58A).
//
// Shape mirrors the rowed HordeAIUpdate base TU over the pinned opaque
// Transport base 0x26E9BD: the base call resolves via the rowed
// HordeAIUpdate ctor 0x49A7F3, the setWakeFrame spelling resolves via the
// Rva0026E9BDBase alias pin at 0x44DF71, and the wake frame comes from the
// int global at 0x00DBA4E4 (g_Va00DBA4E4, shared with the cold getters).
// An eax-homed int zero covers +0x3E8/+0x3EC/+0x3F0 plus the +0x3F4 byte;
// the +0x3E4 slot is re-stored. /GX for the EH prologue plus the single
// mid-body state store; the base dtor stays declared-only (no link clash
// with the base TU). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C50538[];  // folded, 2 classes; via ??_7HordeWorkerAIUpdate@@6BDBaseM1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C50538=??_7HordeWorkerAIUpdate@@6BDBaseM1@@@")
extern "C" const void *const vtbl_00C52F88[];  // folded, 12 classes; via ??_7DeployStyleAIUpdate@@6BDBaseM4@@@
#pragma comment(linker, "/alternatename:_vtbl_00C52F88=??_7DeployStyleAIUpdate@@6BDBaseM4@@@")

extern "C" const void *const vtbl_00C508B8[];  // ??_7HordeWorkerAIUpdate@@6BDBaseM3@@@
#pragma comment(linker, "/alternatename:_vtbl_00C508B8=??_7HordeWorkerAIUpdate@@6BDBaseM3@@@")
extern "C" const void *const vtbl_00C508BC[];  // ??_7HordeWorkerAIUpdate@@6BDBaseB2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C508BC=??_7HordeWorkerAIUpdate@@6BDBaseB2@@@")
extern "C" const void *const vtbl_00C508C8[];  // ??_7HordeWorkerAIUpdate@@6BDBaseRoot@@@
#pragma comment(linker, "/alternatename:_vtbl_00C508C8=??_7HordeWorkerAIUpdate@@6BDBaseRoot@@@")
extern const void *const g_00C50868[];

class Thing;
class ModuleData;
class Object;

extern int g_Va00DBA4E4;

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);
	~Rva0026E9BDBase();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	unsigned char m_pad28[0x3E4 - 0x28];
	const void *m_p3E4;
};

class HordeAIUpdate : public Rva0026E9BDBase
{
public:
	HordeAIUpdate(Thing *thing, const ModuleData *moduleData);
};

class HordeWorkerAIUpdate : public HordeAIUpdate
{
public:
	HordeWorkerAIUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_3E8;
	unsigned int m_3EC;
	unsigned int m_3F0;
	unsigned char m_3F4;
};

// ??0HordeWorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049AD15
HordeWorkerAIUpdate::HordeWorkerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: HordeAIUpdate(thing, moduleData)
{
	int zero = 0;
	m_vtable = (const void *)((unsigned int)vtbl_00C508C8);
	m_p0C = (const void *)((unsigned int)vtbl_00C50538);
	m_p10 = (const void *)((unsigned int)vtbl_00C508BC);
	m_p20 = (const void *)((unsigned int)vtbl_00C508B8);
	m_p24 = (const void *)((unsigned int)vtbl_00C52F88);
	m_p3E4 = (const void *)g_00C50868;
	m_3E8 = zero;
	m_3EC = zero;
	m_3F0 = zero;
	m_3F4 = zero;
	setWakeFrame(m_object, g_Va00DBA4E4);
}
