// cl: /O1 /arch:SSE /MD /DNDEBUG
// ??0FireWeaponWhenDamagedBehaviorModuleData@@QAE@XZ @0x00253682 (95B):
// vtable 0x00C4ED70 (trivial-hierarchy fold) then the shared-construct
// block at +8 (rowed Rva0025342CMember::construct, 0x110 bytes ending
// exactly at +0x118) then StartsActive at +0x118 plus DamageTypes at +0x11C
// (or -1) plus DamageAmount at +0x120 (float-zero) plus ReactionWeapon
// Pristine/Damaged/ReallyDamaged/Rubble at +0x124/0x128/0x12C/0x130 plus
// ContinuousWeapon Pristine/Damaged/ReallyDamaged/Rubble at
// +0x134/0x138/0x13C/0x140. Table 0x00BF0400 carries all eleven fields at
// these offsets; factory 0x253703 news 0x144 with this ctor as sole caller
// and pushes the rowed proc. Shape follows ReflectDamage trivial-ctor
// (flat explicit vtable, body in retail order, /O1 /arch:SSE).
class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	FireWeaponWhenDamagedBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04
	Rva0025342CMember m_sharedConstruct; // +0x08
	bool m_startsActive; // +0x118
	unsigned char m_pad119[3];
	int m_damageTypes; // +0x11C
	float m_damageAmount; // +0x120
	void *m_reactionWeaponPristine; // +0x124
	void *m_reactionWeaponDamaged; // +0x128
	void *m_reactionWeaponReallyDamaged; // +0x12C
	void *m_reactionWeaponRubble; // +0x130
	void *m_continuousWeaponPristine; // +0x134
	void *m_continuousWeaponDamaged; // +0x138
	void *m_continuousWeaponReallyDamaged; // +0x13C
	void *m_continuousWeaponRubble; // +0x140
};

// ??0FireWeaponWhenDamagedBehaviorModuleData@@QAE@XZ @0x00253682
FireWeaponWhenDamagedBehaviorModuleData::FireWeaponWhenDamagedBehaviorModuleData()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00C4ED70);
	m_sharedConstruct.construct();
	m_damageTypes |= -1;
	m_startsActive = false;
	m_reactionWeaponPristine = 0;
	m_reactionWeaponDamaged = 0;
	m_reactionWeaponReallyDamaged = 0;
	m_reactionWeaponRubble = 0;
	m_continuousWeaponPristine = 0;
	m_continuousWeaponDamaged = 0;
	m_continuousWeaponReallyDamaged = 0;
	m_continuousWeaponRubble = 0;
	m_damageAmount = 0.0f;
}
