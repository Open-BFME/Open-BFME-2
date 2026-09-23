// cl: /O1 /DNDEBUG /MD
//
// ??0ThreatFinderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003ECCA2, 46 bytes.
// ThreatFinderUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x20, then re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked).
// The rowed pool key at 0x3ECCD6 and the rowed instance factory 0x24FBD0
// (sole caller, ModuleFactory registration literal) prove the class. Row
// supersedes the ctor pin.

class ModuleData;
class Thing;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque UpdateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
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

class ThreatFinderUpdate : public UpdateModule
{
public:
	ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
};

// ??0ThreatFinderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x3ECCA2
ThreatFinderUpdate::ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
