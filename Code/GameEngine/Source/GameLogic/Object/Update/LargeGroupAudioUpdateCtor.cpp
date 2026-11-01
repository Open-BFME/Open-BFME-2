// cl: /DNDEBUG /MD
// stlport
//
// ??0LargeGroupAudioUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AB811,
// 120 bytes. Behavior-side ctor over the rowed UpdateModule base 0x253390
// (thing plus data): two-phase +0x20/+0x24 slots via sourced-before
// address-take (C6FFFC/BFB698 first, C548E8/C548B8 second, RainOfFire and
// WallUpgrade precedent), the derived vtable group (primary C549BC plus
// secondaries C54900/C548F0), float zeroes at +0x28/+0x2C via an xmm0-homed
// fzero local (/arch:SSE emits retail xorps+movss), the 0x4C condition member
// at +0x30 via the pinned CondStore init 0x42526, the 128-bit mask at +0x7C
// via the rowed bitset reset 0x24CA24, or-ff at +0x90 plus bytes at +0x8C/+0x8D.
// The rowed instance factory 0x24F327 (news 0x94, ModuleFactory registration
// literal) is the sole raw caller; poolkey rowed at 0x4AB897. Row supersedes
// the ctor pin. Zero new pins (base plus both callees already rowed/pinned).

extern "C" const void *const __identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@")[];  // folded vftable 0x00C6FFFC (10 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate_B24@@6B@")[];  // vftable 0x00BFB698
extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate@@6BLargeGroupAudioUpdate_B24@@@")[];  // vftable 0x00C548B8
extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate@@6BLargeGroupAudioUpdate_B20@@@")[];  // vftable 0x00C548E8
// The retail table at RVA 0x008548F0: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?update@LargeGroupAudioUpdate@@UAE?AW4UpdateSleepTime@@XZ")();
void __identifier("?getDisabledTypesToProcess@Rva004AB9D5@@QAE?AVBfmeFixedStorage002CF0F0@@XZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
}
extern "C" const void *const vtbl_00C548F0[3] = {
	(const void *)&__identifier("?update@LargeGroupAudioUpdate@@UAE?AW4UpdateSleepTime@@XZ"), // slot 0 0x004ABB4B
	(const void *)&__identifier("?getDisabledTypesToProcess@Rva004AB9D5@@QAE?AVBfmeFixedStorage002CF0F0@@XZ"), // slot 1 0x004AB9D5
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z"), // slot 2 0x0044DF8D
};
extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C54900
extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate@@6BObjectModule@@@")[];  // vftable 0x00C549BC

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

struct CondStore
{
	unsigned char m_data[0x4C];
};

// The +0x30 store is initialised by the rowed 0x00042526 zeroing
// constructor (LargeGroupAudioAudioMap.cpp's Rva0042526Member).
class Rva0042526Member
{
public:
	Rva0042526Member();
};

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
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class LargeGroupAudioUpdate : public UpdateModule
{
public:
	LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	const void *m_secondary24;
	float m_state28;
	float m_state2C;
	CondStore m_condition30;
	unsigned long m_flags7C[4];
	bool m_flag8C;
	bool m_flag8D;
	unsigned char m_pad8E[2];
	int m_state90;
};

// ??0LargeGroupAudioUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004AB811
LargeGroupAudioUpdate::LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slotInit20 = (int *)&m_secondary20;
	*slotInit20 = (int)((unsigned int)__identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@"));
	int *slotInit24 = (int *)&m_secondary24;
	*slotInit24 = (int)((unsigned int)__identifier("??_7LargeGroupAudioUpdate_B24@@6B@"));
	int *vtab = (int *)&m_vtable;
	*vtab = (int)((unsigned int)__identifier("??_7LargeGroupAudioUpdate@@6BObjectModule@@@"));
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)((unsigned int)__identifier("??_7LargeGroupAudioUpdate@@6BBehaviorModuleInterface@@@"));
	int *sec10 = (int *)&m_secondary10;
	*sec10 = (int)((unsigned int)vtbl_00C548F0);
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)((unsigned int)__identifier("??_7LargeGroupAudioUpdate@@6BLargeGroupAudioUpdate_B20@@@"));
	int *slot24 = (int *)&m_secondary24;
	*slot24 = (int)((unsigned int)__identifier("??_7LargeGroupAudioUpdate@@6BLargeGroupAudioUpdate_B24@@@"));
	m_state28 = fzero;
	m_state2C = fzero;
	CondStore *condStore = &m_condition30;
	((Rva0042526Member *)condStore)->Rva0042526Member::Rva0042526Member();
	((_STL::bitset<128> *)m_flags7C)->reset();
	m_state90 |= -1;
	m_flag8C = false;
	m_flag8D = false;
}
