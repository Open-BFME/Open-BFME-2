// cl: /O1 /arch:SSE /GX /Oy /MD /DNDEBUG
// ??0FireWeaponWhenDeadBehaviorModuleData@@QAE@XZ @0x00253737 (111B): vtable
// 0x00C4ED70 (trivial-hierarchy fold shared with DeletionUpdate) then the
// shared-construct block at +8 (rowed Rva0025342CMember::construct, 0x110
// bytes ending exactly at +0x118) then DieMuxData at +0x12C (rowed init)
// then StartsActive at +0x118 plus ActiveDuringConstruction at +0x119 plus
// DelayTime at +0x11C plus DeathWeapon at +0x15C plus WeaponOffset floats at
// +0x120. Table 0x00BF0508 carries all five fields at these offsets;
// factory 0x2537DC news 0x160 with this ctor as sole caller and pushes the
// rowed proc. The base cleanup at RVA 0x00771C42 calls ModuleData::~ModuleData.

#include "../../../../Include/GameLogic/Module/Rva0025342CMember.h"

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

#include "../../../../Include/Common/ModuleData.h"

inline ModuleData::~ModuleData() {}

// The block's rowed construct runs before the next member's constructor.
class ConstructedMuxBlock : public Rva0025342CMember
{
public:
	ConstructedMuxBlock() { construct(); }
};

class FireWeaponWhenDeadBehaviorModuleData : public ModuleData
{
public:
	FireWeaponWhenDeadBehaviorModuleData();

private:
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
