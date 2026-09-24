// cl: /O1 /MD /GX /DNDEBUG
//
// ??0ArmorUpgradeModuleData@@QAE@XZ, retail 0x00254556, 26 bytes.
// Frameless store-only ctor over the rowed OpenContainModuleData base
// (0x253487): folded vtable 0x00BF2558 (shared with RadarUpgrade, Defector
// precedent for ICF-folded vtables), KillArmorUpgrade false at +0x118,
// IgnoreArmorUpgrade false at +0x119, ArmorSetFlag 3 at +0x11C (own table
// 0x00DBA870 holds exactly these three fields; all three vote one BFME1
// class in field_names; the ModuleData factory at 0x2545DB news 0x120 and
// is the sole raw caller). Recipe: ReflectDamageModuleDataCtor (flat
// TU-local class, explicit vtable slot, no virtuals emitted).

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class ArmorUpgradeModuleData : public OpenContainModuleData
{
public:
	ArmorUpgradeModuleData();

private:
	bool m_killArmorUpgrade; // +0x118
	bool m_ignoreArmorUpgrade; // +0x119
	// +0x11A..0x11B pad
	int m_armorSetFlag; // +0x11C
};

// ??0ArmorUpgradeModuleData@@QAE@XZ @0x254556
ArmorUpgradeModuleData::ArmorUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF2558);
	m_killArmorUpgrade = false;
	m_ignoreArmorUpgrade = false;
	m_armorSetFlag = 3;
}
