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
extern "C" const void *const vtbl_00BF3940[] = {
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
	(const void *)&vfn_0047A699,
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
