// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0QueueProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A010E, 106 bytes. Behavior-side ctor over the rowed
// UpdateModule base (0x253390): two-phase +0x20 slot (C430B4 first via
// sourced-before address-take, C5198C second) plus an ecx-homed int zero
// plus float zeros via an xmm0-homed fzero local (/arch:SSE emits retail
// xorps+movss), then a trailing zero group (single barrier) with an
// owner-null-conditional overwrite of +0x3C from owner+0x28
// (PartTheHeavens precedent). The rowed instance factory 0x24E969
// (news 0x44) is the sole caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

struct ThingOwner
{
	char m_pad[0x28];
	int m_28;
};

class QueueProductionExitUpdate : public UpdateModule
{
public:
	QueueProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	unsigned int m_24;
	float m_28;
	float m_2C;
	float m_30;
	bool m_34;
	char m_pad35[3];
	float m_38;
	int m_3C;
	int m_40;
};

// ??0QueueProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A010E
QueueProductionExitUpdate::QueueProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C430B4;
	int zero = 0;
	m_vtable = (const void *)0x00C519C8;
	m_p0C = (const void *)0x00C4B1F0;
	m_p10 = (const void *)0x00C519BC;
	m_secondary20 = (const void *)0x00C5198C;
	m_24 = zero;
	m_38 = fzero;
	m_28 = fzero;
	m_2C = fzero;
	m_30 = fzero;
	_ReadWriteBarrier();
	m_40 = zero;
	m_34 = false;
	m_3C = zero;
	if (m_owner != 0)
		m_3C = ((ThingOwner *)m_owner)->m_28;
}
