// cl: /O1 /MD /GX- /DNDEBUG /arch:SSE
//
// ??0MaxHealthUpgradeModuleData@@QAE@XZ, retail 0x004B62C4, 36 bytes.
// Frameless store-only ctor over the rowed OpenContainModuleData base
// (0x253487): folded vtable 0x00BF2558, ChangeType zero at +0x11C (compact
// and form, hoisted above the vtable store) and AddMaxHealth float-zero at
// +0x118 (xorps plus movss; own table 0x008585DC holds exactly AddMaxHealth
// at +0x118 plus ChangeType at +0x11C; the rowed MaxHealthUpgrade pool key
// at 0x4B627F ends where the ctor begins; the EH factory at 0x2504BA news
// 0x120 and is the only raw caller). Recipe:
// RadarUpgradeModuleDataCtor (flat TU-local class with explicit vtable
// slot); /arch:SSE for the float-zero store (DemoTrap precedent).

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class MaxHealthUpgradeModuleData : public OpenContainModuleData
{
public:
	MaxHealthUpgradeModuleData();

private:
	float m_addMaxHealth; // +0x118
	int m_changeType; // +0x11C
};

// ??0MaxHealthUpgradeModuleData@@QAE@XZ @0x4B62C4
MaxHealthUpgradeModuleData::MaxHealthUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF2558);
	m_changeType = 0;
	m_addMaxHealth = 0.0f;
}
