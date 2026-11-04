char g_00C55108;
char g_00C55118;

// cl: /DNDEBUG /MD /GX-
//
// ??1GloriousChargeUpdate@@UAE@XZ, retail 0x004AD58C, 60 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched, so the class is
// re-declared here with the ctor declared-only and only the dtor defined.
//
// Shape follows the RousingSpeechUpdate dtor precedent: explicit 4 vtable
// installs plus freelist-node member at +0x88 via pinned reset plus
// pool-free via 0x268902 pin plus implicit Rva0044EF5E base-dtor tail call.
// The class is proven by the poolkey, name getter, ModuleData and instance
// factories plus the ctor installing these same 4 vtables. Zero new pins.

extern "C" const void *const __identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C4D640 (11 classes), by its data-ledger name
// The retail table at RVA 0x008552A4: 9 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?initiateIntentToDoSpecialPower@SpecialAbilityUpdate@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?get@Rva005C4AE5ByteField@@QBEEXZ")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0044EECA@Rva0044EECA@@QAE_NPAURva0044EECAParam@@@Z")();
void __identifier("?rva0044F09F@Rva0044F09F@@UAE_NH@Z")();
void __identifier("?vslot08@SpecialAbilityUpdate@@UAE_NH@Z")();
}
extern "C" const void *const vtbl_00C552A4[9] = {
	(const void *)&__identifier("?initiateIntentToDoSpecialPower@SpecialAbilityUpdate@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z"), // slot 0 0x004500A3
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 1 0x0050B5C6
	(const void *)&__identifier("?get@Rva005C4AE5ByteField@@QBEEXZ"), // slot 2 0x005C4AE5
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 3 0x000D43D0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 5 0x0047A69C
	(const void *)&__identifier("?rva0044EECA@Rva0044EECA@@QAE_NPAURva0044EECAParam@@@Z"), // slot 6 0x0044EECA
	(const void *)&__identifier("?rva0044F09F@Rva0044F09F@@UAE_NH@Z"), // slot 7 0x0044F09F
	(const void *)&__identifier("?vslot08@SpecialAbilityUpdate@@UAE_NH@Z"), // slot 8 0x0044EDA6
};

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class PoolMember
{
public:
	void Rva00268902();
};

class GloriousChargeUpdate : public Rva0044EF5E
{
public:
	GloriousChargeUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~GloriousChargeUpdate();
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
};

// ??1GloriousChargeUpdate@@UAE@XZ @0x004AD58C
GloriousChargeUpdate::~GloriousChargeUpdate()
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	*(const void **)this = (const void *)(unsigned int)&g_00C55118;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7BattlePlanUpdate@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)(unsigned int)&g_00C55108;
	*(const void **)((char *)this + 0x20) = (const void *)((unsigned int)vtbl_00C552A4);
	member->reset();
	((PoolMember *)member)->Rva00268902();
}
