// cl: /DNDEBUG /MD
//
// ??0RainOfFireUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004AC0A8, 135 bytes. Behavior-side ctor (rowed instance factory
// 0x24F3B3 news 0x38 with this pinned 2-arg ctor as its sole raw caller
// at 0x24F3DA).
//
// Shape follows the DestroyEnvironmentUpdate precedent over the rowed
// UpdateModule base (0x253390, thing plus data): a table slot at +0x20
// (init literal, reassigned in body), the module-data load plus null test
// hoisted above the vtable group with flags live across the stores, the
// vtable group reinstalling the primary slot and the +0x0C/+0x10
// secondaries, next-frame at +0x24 defaulting to 0x3FFFFFFF and refreshed
// from the GameLogic frame when module data is present, float state at
// +0x28/+0x2C/+0x30/+0x34, plus an equality check on the module-data DPS
// ramp (+0x24 float per the rowed ModuleData table) raising +0x34 to 1.0f
// when the ramp is exactly 0.0f. No virtuals are declared anywhere so no
// vtable is emitted here; every store goes through a sourced-before
// address-take pointer (SiegeDeploySpecialPower idiom), which pins the
// groups in program order where plain assignments get clustered. Row
// supersedes the ctor pin and the banked 0.9 partial.

extern "C" const void *const __identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@")[];  // folded vftable 0x00C6FFFC (10 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7RainOfFireUpdate@@6BSecondary20@@@")[];  // vftable 0x00C54BA0
// The retail table at RVA 0x00854BA8: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?update@RainOfFireUpdate@@UAE?AW4UpdateSleepTime@@XZ")();
void __identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
}
extern "C" const void *const vtbl_00C54BA8[3] = {
	(const void *)&__identifier("?update@RainOfFireUpdate@@UAE?AW4UpdateSleepTime@@XZ"), // slot 0 0x004AC2A8
	(const void *)&__identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ"), // slot 1 0x00253376
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z"), // slot 2 0x0044DF8D
};
extern "C" const void *const __identifier("??_7RainOfFireUpdate@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C54BB8
extern "C" const void *const __identifier("??_7RainOfFireUpdate@@6BObjectModule@@@")[];  // vftable 0x00C54C74

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	void *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class RainOfFireUpdateModuleData
{
public:
	float m_pad00[9];
	float m_dpsRampupTime;
};

class RainOfFireUpdate : public UpdateModule
{
public:
	RainOfFireUpdate(Thing *thing, const ModuleData *moduleData);

private:
	void *m_slot;
	int m_frame;
	float m_state28;
	float m_state2C;
	float m_state30;
	float m_state34;
};

// ??0RainOfFireUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RainOfFireUpdate::RainOfFireUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slotInit = (int *)&m_slot;
	*slotInit = (int)((unsigned int)__identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@"));
	const RainOfFireUpdateModuleData *mod =
		reinterpret_cast<const RainOfFireUpdateModuleData *>(m_moduleData);
	int *vtab = (int *)&m_vtable;
	*vtab = (int)((unsigned int)__identifier("??_7RainOfFireUpdate@@6BObjectModule@@@"));
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)((unsigned int)__identifier("??_7RainOfFireUpdate@@6BBehaviorModuleInterface@@@"));
	int *sec10 = (int *)&m_secondary10;
	*sec10 = (int)((unsigned int)vtbl_00C54BA8);
	int *slot = (int *)&m_slot;
	*slot = (int)((unsigned int)__identifier("??_7RainOfFireUpdate@@6BSecondary20@@@"));
	m_frame = 0x3FFFFFFF;
	float *cell28 = &m_state28;
	*cell28 = 0.0f;
	float *cell2C = &m_state2C;
	*cell2C = 1.0f;
	float *cell30 = &m_state30;
	*cell30 = 0.0f;
	float *cell34 = &m_state34;
	*cell34 = 0.0f;
	if (mod != 0) {
		m_frame = TheGameLogic->getFrame();
		m_state34 = (mod->m_dpsRampupTime == 0.0f) ? 1.0f : 0.0f;
	}
}
