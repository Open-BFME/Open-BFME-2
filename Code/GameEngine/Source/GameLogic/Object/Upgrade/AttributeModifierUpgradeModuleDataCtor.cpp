// cl: /MD /GX /DNDEBUG
//
// ??0AttributeModifierUpgradeModuleData@@QAE@XZ, retail 0x002557E9, 25 bytes.
// Frameless store-only ctor over the rowed Rva00253487Base base
// (0x253487): folded vtable 0x00BF38C0, AttributeModifier zero at +0x118
// (compact and form; own table 0x00858818 holds exactly AttributeModifier at
// +0x118; the AttributeModifierUpgrade pool key at 0x4B6703 ends where the
// rowed proc begins; the ModuleData factory at 0x255802 news 0x11C and is
// the only raw caller). Recipe: RadarUpgradeModuleDataCtor (flat TU-local
// class with explicit vtable slot, no virtuals emitted).

// Retail VA 0x00BF38C0 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_00256267();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_00256267=??_GCommandSetUpgradeModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00BF38C0[] = {
	(const void *)&vfn_00256267,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0050B5C6,
	(const void *)&vfn_0050B5C6,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

class Rva00253487Base
{
public:
	Rva00253487Base();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class AttributeModifierUpgradeModuleData : public Rva00253487Base
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
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF38C0));
	_ReadWriteBarrier();
	m_attributeModifier = 0;
}
