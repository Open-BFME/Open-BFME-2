// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG
// ??0FireWeaponWhenDeadBehaviorModuleData@@QAE@XZ @0x00253737 (110B): vtable
// 0x00C4ED70 (trivial-hierarchy fold shared with DeletionUpdate) then the
// shared-construct block at +8 (rowed Rva0025342CMember::construct, 0x110
// bytes ending exactly at +0x118) then DieMuxData at +0x12C (rowed init)
// then StartsActive at +0x118 plus ActiveDuringConstruction at +0x119 plus
// DelayTime at +0x11C plus DeathWeapon at +0x15C plus WeaponOffset floats at
// +0x120. Table 0x00BF0508 carries all five fields at these offsets;
// factory 0x2537DC news 0x160 with this ctor as sole caller and pushes the
// rowed proc. Shape follows SpawnBehavior (empty base, init-listed explicit
// vtable, rowed construct plus rowed init).
extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];  // folded nine-class vftable 0x00C4ED70, by its data-ledger name

#include "../../../../Include/GameLogic/Module/Rva0025342CMember.h"

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

class BehaviorModuleData
{
public:
	__declspec(dllimport) __forceinline BehaviorModuleData() {}
	~BehaviorModuleData();
};

// The block's rowed construct runs before the next member's constructor.
class ConstructedMuxBlock : public Rva0025342CMember
{
public:
	ConstructedMuxBlock() { construct(); }
};

class FireWeaponWhenDeadBehaviorModuleData : public BehaviorModuleData
{
public:
	FireWeaponWhenDeadBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	ConstructedMuxBlock m_muxData; // +8
	bool m_startsActive; // +0x118
	bool m_activeDuringConstruction; // +0x119
	unsigned char m_pad11A[2];
	int m_delayTime; // +0x11C
	float m_weaponOffset[3]; // +0x120
	DieMuxData m_dieMuxData; // +0x12C
	int m_deathWeapon; // +0x15C
};

// ??0FireWeaponWhenDeadBehaviorModuleData@@QAE@XZ @0x00253737
inline FireWeaponWhenDeadBehaviorModuleData::FireWeaponWhenDeadBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(((unsigned int)__identifier("??_7ObjectHelperModuleData@@6B@"))))
{
	m_startsActive = false;
	m_activeDuringConstruction = false;
	m_delayTime = 0;
	m_deathWeapon = 0;
	float *weaponOffset = m_weaponOffset;
	weaponOffset[0] = 0.0f;
	weaponOffset[1] = 0.0f;
	weaponOffset[2] = 0.0f;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFireWeaponWhenDeadBehaviorModuleDataInlineAnchor@@YAXPAVFireWeaponWhenDeadBehaviorModuleData@@@Z absent-from-retail
void _bfmeFireWeaponWhenDeadBehaviorModuleDataInlineAnchor(FireWeaponWhenDeadBehaviorModuleData *fireWeaponWhenDeadBehaviorModuleData)
{
    fireWeaponWhenDeadBehaviorModuleData->FireWeaponWhenDeadBehaviorModuleData::FireWeaponWhenDeadBehaviorModuleData();
}
#pragma inline_depth()
