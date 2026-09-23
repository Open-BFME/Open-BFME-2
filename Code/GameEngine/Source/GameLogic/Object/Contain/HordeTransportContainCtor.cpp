// cl: /O1 /DNDEBUG /MD /GX
//
// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00477003, 149 bytes. Behavior-side ctor (rowed instance factory
// 0x24B9CC news 0x128 with this pinned 2-arg ctor as its sole raw caller
// at 0x24B9F6; a derived contain ctor at 0x47D25E shares the base call).
//
// Shape: EH prologue via /GX plus the declared-only base dtor over the
// pinned TransportContain base 0x468559, a Coord2D member at +0x11D built
// in the init-list (rowed 0-arg ctor 0x47A6A9; declared here without a
// dtor so no unwind state is added), the three derived vtable installs
// plus six secondaries, an int minus-1000 at +0x120 and a zero byte at
// +0x124 through pointer casts into the member tail (the rowed Coord2D is
// eight bytes so both overlap it), and no setWakeFrame tail. The base
// runs to +0x11D. Row supersedes the ctor pin.

class Thing;
class ModuleData;

struct Coord2D
{
	Coord2D();

	float x;
	float y;
};

#pragma pack(push, 1)
class TransportContain
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	~TransportContain();

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	void *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_20;
	const void *m_24;
	const void *m_28;
	const void *m_2C;
	const void *m_30;
	const void *m_34;
	unsigned char m_pad38[0xFC - 0x38];
	const void *m_FC;
	unsigned char m_pad100[0x11D - 0x100];
};

class HordeTransportContain : public TransportContain
{
public:
	HordeTransportContain(Thing *thing, const ModuleData *moduleData);

private:
	Coord2D m_11D;
};
#pragma pack(pop)

// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x00477003
HordeTransportContain::HordeTransportContain(Thing *thing, const ModuleData *moduleData)
	: TransportContain(thing, moduleData), m_11D()
{
	m_vtable = (const void *)0x00C45EB8;
	m_secondary0C = (const void *)0x00C441B8;
	m_secondary10 = (const void *)0x00C45EA8;
	m_20 = (const void *)0x00C45D30;
	m_24 = (const void *)0x00C46064;
	m_28 = (const void *)0x00C45D2C;
	m_2C = (const void *)0x00C58790;
	m_30 = (const void *)0x00C45CFC;
	m_34 = (const void *)0x00C45CEC;
	m_FC = (const void *)0x00C47834;
	*(int *)((char *)&m_11D + 3) = -1000;
	*(unsigned char *)((char *)&m_11D + 7) = 0;
}
