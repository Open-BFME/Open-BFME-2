// cl: /O1 /MD /GX /DNDEBUG
//
// ??0AttributeModifierUpgradeModuleData@@QAE@XZ, retail 0x002557E9, 25 bytes.
// Frameless store-only ctor over the rowed OpenContainModuleData base
// (0x253487): folded vtable 0x00BF38C0, AttributeModifier zero at +0x118
// (compact and form; own table 0x00858818 holds exactly AttributeModifier at
// +0x118; the AttributeModifierUpgrade pool key at 0x4B6703 ends where the
// rowed proc begins; the ModuleData factory at 0x255802 news 0x11C and is
// the only raw caller). Recipe: RadarUpgradeModuleDataCtor (flat TU-local
// class with explicit vtable slot, no virtuals emitted).

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class AttributeModifierUpgradeModuleData : public OpenContainModuleData
{
public:
	AttributeModifierUpgradeModuleData();

private:
	int m_attributeModifier; // +0x118
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0AttributeModifierUpgradeModuleData@@QAE@XZ @0x2557E9
AttributeModifierUpgradeModuleData::AttributeModifierUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF38C0);
	_ReadWriteBarrier();
	m_attributeModifier = 0;
}
