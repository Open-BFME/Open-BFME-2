// cl: /O1 /DNDEBUG /MD
//
// ??0RadarMarkerClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C9BCD, 32 bytes.
// RadarMarkerClientUpdate ctor over the rowed Rva00362EC7 base (0x362EC7):
// re-stores the primary vtable slot and zeroes +0x0C (address-of TU-local
// dummy, DIR32-masked). The rowed pool key at 0x4C9BF3 and the rowed
// instance factory 0x252AD9 (sole caller, ModuleFactory registration
// literal) prove the class. Row supersedes the ctor pin.

class ModuleData;
class Thing;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;

// Opaque Rva00362EC7 base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	int m_0C;
};

class RadarMarkerClientUpdate : public Rva00362EC7
{
public:
	RadarMarkerClientUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0RadarMarkerClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C9BCD
RadarMarkerClientUpdate::RadarMarkerClientUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	m_vtable = &s_vtable;
	_ReadWriteBarrier();
	m_0C = 0;
}
