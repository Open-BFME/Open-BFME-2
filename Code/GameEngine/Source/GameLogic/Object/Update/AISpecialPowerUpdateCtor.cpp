// cl: /DNDEBUG /MD
//
// ??0AISpecialPowerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B2F2A, 53 bytes.
// AISpecialPowerUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x20/+0x21/+0x24, then re-stores the primary vtable
// slot and the +0x0C/+0x10 secondary slots (the class's own tables, by
// their retail store immediates). The rowed name getter at 0x4B2ED4 and ModuleData triple
// (proc 0x4B2F19 plus ctor 0x4B2FCD plus factory 0x24FD76) prove the class;
// the rowed instance factory 0x24FD3E is the sole raw caller. Row supersedes
// the ctor pin.

class ModuleData;
class Thing;

extern "C" const void *const __identifier("??_7AISpecialPowerUpdate@@6BObjectModule@@@")[];  // vftable 0x00C56E1C
extern "C" const void *const __identifier("??_7AISpecialPowerUpdate@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C56D60
extern "C" const void *const __identifier("??_7AISpecialPowerUpdate@@6B@")[];  // vftable 0x00C56D50

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

class AISpecialPowerUpdate : public UpdateModule
{
public:
	AISpecialPowerUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad22[2];
	int m_24;
};

// ??0AISpecialPowerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B2F2A
AISpecialPowerUpdate::AISpecialPowerUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = 0;
	m_21 = 0;
	m_24 = 0;
	m_vtable = __identifier("??_7AISpecialPowerUpdate@@6BObjectModule@@@");
	m_p0C = __identifier("??_7AISpecialPowerUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7AISpecialPowerUpdate@@6B@");
}
