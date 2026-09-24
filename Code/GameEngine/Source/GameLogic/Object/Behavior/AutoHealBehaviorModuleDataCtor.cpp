// cl: /O1 /DNDEBUG /MD
//
// ??0AutoHealBehaviorModuleData@@QAE@XZ, retail 0x00254DE7, 150 bytes.
// V1: flat class over OpenContain-style base tail plus Rva0025342CMember at
// +8 (rowed construct) plus healing fields from retail table 0xBF3CE0 plus
// Rva0024C7B3Member mask at +0x130 (rowed zeroing ctor) plus trailing
// fields; vtable is the folded 0x00C4ED70 stored explicitly; the mask is
// set to all-bits by the single-use file helper pinned at 0x2535A5.

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_data[0x110];
};

// Init-list setup-hoist scaffolding: deriving gives the +8 region an inline
// ctor whose construct call stays in init position while the lea setup
// hoists above the vtable store, reproducing retail's lea/vtable/call head.
struct M08Wrap : public Rva0025342CMember
{
	M08Wrap() { construct(); }
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	unsigned char m_data[0x1C];
};

class Rva002535A5Mask
{
public:
	static void setAll(void *mask);
};

class AutoHealBehaviorModuleData
{
public:
	AutoHealBehaviorModuleData();

private:
	unsigned int m_vtable; // +0x00
	unsigned int m_pad04; // +0x04
	M08Wrap m_08; // +0x08
	bool m_startsActive; // +0x118
	bool m_buttonTriggered; // +0x119
	bool m_singleBurst; // +0x11A
	unsigned char m_pad11B; // +0x11B
	int m_healingAmount; // +0x11C
	int m_healingDelay; // +0x120
	int m_startHealingDelay; // +0x124
	int m_radius; // +0x128
	bool m_affectsWholePlayer; // +0x12C
	bool m_affectsContained; // +0x12D
	bool m_healOnlyIfNotUnderAttack; // +0x12E
	bool m_healOnlyIfNotInCombat; // +0x12F
	Rva0024C7B3Member m_kindOf; // +0x130
	bool m_healOnlyOthers; // +0x14C
	unsigned char m_pad14D[3]; // +0x14D
	int m_unitHealPulseFX; // +0x150
	bool m_nonStackable; // +0x154
	bool m_respawnNearbyHordeMembers; // +0x155
	unsigned char m_pad156[2]; // +0x156
	int m_respawnFXList; // +0x158
	int m_respawnMinimumDelay; // +0x15C
};

// ??0AutoHealBehaviorModuleData@@QAE@XZ @0x254DE7
AutoHealBehaviorModuleData::AutoHealBehaviorModuleData()
	: m_vtable(0x00C4ED70), m_08(), m_kindOf()
{
	m_healingDelay |= -1;
	m_startsActive = false;
	m_buttonTriggered = false;
	m_singleBurst = false;
	m_healingAmount = 0;
	m_startHealingDelay = 0;
	m_radius = 0;
	m_affectsWholePlayer = false;
	m_affectsContained = false;
	m_healOnlyIfNotUnderAttack = false;
	m_healOnlyIfNotInCombat = false;
	m_healOnlyOthers = false;
	m_unitHealPulseFX = 0;
	Rva002535A5Mask::setAll(&m_kindOf);
	m_nonStackable = false;
	m_respawnNearbyHordeMembers = false;
	m_respawnFXList = 0;
	m_respawnMinimumDelay = 0;
}
