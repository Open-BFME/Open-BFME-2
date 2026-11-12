// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CastleUpgradeModuleData@@QAE@XZ, retail 0x00255836 (36 bytes).
// Frameless ctor over the rowed OpenContain base (0x253487): base call then
// the vtable literal 0x00BF3940 then the and-zero of the Upgrade word at
// +0x118 then the float zero of WallUpgradeRadius at +0x11C (/arch:SSE
// keeps it as xorps plus movss). Size 0x120 matches the rowed 0x25585A
// factory news. Class identity is the rowed CastleUpgrade proc (Upgrade
// base proc plus table 0x008588C4 holding Upgrade at +0x118 plus
// WallUpgradeRadius at +0x11C) beside the rowed CastleUpgrade pool key
// (0x4B682C) closing this cluster. The upgrade pointer anchors the
// and-zero below the vtable store while xorps still hoists above it
// (RebuildHole address-take precedent). True size 36 corrects the 35B pin
// which cut the ret.

// Retail VA 0x00BF3940 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("??_GCommandSetUpgradeModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00BF3940[] = {
	(const void *)&__identifier("??_GCommandSetUpgradeModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
};

class Rva00253487Base
{
public:
	Rva00253487Base();
};

class CastleUpgradeModuleData : public Rva00253487Base
{
public:
	CastleUpgradeModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared so no vtable is emitted)
	unsigned char m_pad[0x118 - 4]; // +4..0x117
	int m_upgrade; // +0x118
	float m_wallUpgradeRadius; // +0x11C
};

// ??0CastleUpgradeModuleData@@QAE@XZ @0x255836
CastleUpgradeModuleData::CastleUpgradeModuleData()
{
	int *upgrade = &m_upgrade;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF3940));
	*upgrade &= 0;
	m_wallUpgradeRadius = 0.0f;
}
