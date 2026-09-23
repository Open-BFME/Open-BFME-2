// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ??0WeaponSetSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004923E2,
// 32 bytes. Weapon-set ability data over own INI table 0x00BEF008
// (WeaponsetEffectDuration at +0xC8, WhichWeaponSet at +0xCC; offsets
// read from the retail table). Runs the pinned Rva0044EB54 base ctor
// (0x44EB54), zeroes both trailing words and installs the explicit
// vtable 0xC5F778. Flat classes throughout (no declared dtors anywhere)
// keep the body frameless; /O1 keeps the integer zeros as the compact
// and form. The ModuleData factory at 0x24DAAC (news 0xD0) is a raw
// caller, as is the FellBeastSwoopPower factory at 0x2523EE: the two
// classes share byte-identical ctors (ICF twins, documented as such in
// BFME1), so this row claims the address once under the WeaponSet name
// and the FellBeast pin stands as its alias. Row supersedes the
// WeaponSet ctor pin.

class Rva0044EB54
{
public:
	Rva0044EB54();

private:
	unsigned char m_pad[0xC8];
};

class WeaponSetSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	WeaponSetSpecialAbilityUpdateModuleData();

private:
	int m_weaponsetEffectDuration; // +0xC8
	int m_whichWeaponSet; // +0xCC
};

// ??0WeaponSetSpecialAbilityUpdateModuleData@@QAE@XZ @0x004923E2
WeaponSetSpecialAbilityUpdateModuleData::WeaponSetSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_weaponsetEffectDuration = 0;
	m_whichWeaponSet = 0;
	*(unsigned int *)this = 0x00C5F778;
}
