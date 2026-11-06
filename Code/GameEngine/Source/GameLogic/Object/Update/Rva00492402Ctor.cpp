// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00492402@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00492402 (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (0xC4D640 / 0xC4DEE8 / 0xC4DFD4). The +0x20 slot
// uses the complete shared interface table below. No trailing members
// (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24DA7C factory stub.
// The paired dtor (0x00492439, ModuleUpdateDtors.cpp) is rowed and references the same table.
class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;
// RVA 0x0084DFD4: nine code pointers, immediately followed by the primary
// table at 0x0084DFF8. Keep the existing provisional data-owner name;
// these slot bindings do not establish the interface's original identity.
extern "C" {
void __identifier("?initiateIntentToDoSpecialPower@SpecialAbilityUpdate@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?get@Rva005C4AE5ByteField@@QBEEXZ")();
void __identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0044EECA@Rva0044EECA@@QAE_NPAURva0044EECAParam@@@Z")();
void __identifier("?rva0044F09F@Rva0044F09F@@UAE_NH@Z")();
void __identifier("?bfmeGoFDH@BfmeThingFDH@@QAEDPAX@Z")();
}

extern "C" const void *const s_dummy20[9] = {
	(const void *)&__identifier("?initiateIntentToDoSpecialPower@SpecialAbilityUpdate@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z"), // RVA 0x004500A3
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // RVA 0x0050B5C6
	(const void *)&__identifier("?get@Rva005C4AE5ByteField@@QBEEXZ"), // RVA 0x005C4AE5
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // RVA 0x000D43D0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // RVA 0x0047A699
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // RVA 0x0047A69C
	(const void *)&__identifier("?rva0044EECA@Rva0044EECA@@QAE_NPAURva0044EECAParam@@@Z"), // RVA 0x0044EECA
	(const void *)&__identifier("?rva0044F09F@Rva0044F09F@@UAE_NH@Z"), // RVA 0x0044F09F
	(const void *)&__identifier("?bfmeGoFDH@BfmeThingFDH@@QAEDPAX@Z"), // RVA 0x00492543
};

// Opaque 0x88-byte UpdateModule-derived intermediate; ctor resolves to the
// opaque pin at 0x0044EF5E. Protected slots mirror the retail stores.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
	const void *m_p20;
	unsigned char m_pad2[0x88 - 0x24];
};

class Rva00492402 : public Rva0044EF5E
{
public:
	Rva00492402(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00492402();
};

Rva00492402::Rva00492402(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = s_dummy20;
}

// ~Rva00492402 (retail 0x00492439) and its deleting destructor are defined in
// ModuleUpdateDtors.cpp.
