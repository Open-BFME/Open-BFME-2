// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A65AE, 120 bytes. Behavior-side EH ctor over the rowed
// UpdateModule base (0x253390): two-phase +0x20 slot (C430B4 first via
// sourced-before address-take, C52D00 second) plus float zeros at
// +0x24/+0x28/+0x2C via an xmm0-homed fzero local (/arch:SSE emits retail
// xorps+movss) plus a zero byte at +0x30, then setWakeFrame over the +8
// object with a FOREVER frame (0x3FFFFFFF; rowed setWakeFrame pin 0x44DF71).
// Queues the imm-push above the float stores from natural source (push-hoist).
// The rowed instance factory 0x24EE3F (news 0x34) is the sole caller. Row
// supersedes the ctor pin. (Twin's SupplyCenterProductionExitUpdateCtor.cpp
// holds StoreObjectsSpecialPowerModuleData instead; this shard keeps clear.)

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *obj, unsigned int sleepTime);

protected:
	const void *m_vtable;
	Thing *m_owner;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class SupplyCenterProductionExitUpdate : public UpdateModule
{
public:
	SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	float m_24;
	float m_28;
	float m_2C;
	bool m_30;
	char m_pad31[3]; // to the rowed 0x34 instance size
};

// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A65AE
SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	m_secondary20 = (const void *)0x00C430B4;
	m_vtable = (const void *)0x00C52D30;
	m_p0C = (const void *)0x00C4B1F0;
	m_p10 = (const void *)0x00C4B1E0;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C52D00;
	m_30 = false;
	m_24 = fzero;
	m_28 = fzero;
	m_2C = fzero;
	setWakeFrame(m_object, 0x3FFFFFFF);
}
