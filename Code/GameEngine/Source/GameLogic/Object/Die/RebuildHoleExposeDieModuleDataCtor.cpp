// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RebuildHoleExposeDieModuleData@@QAE@XZ,
// retail 0x0048671F, 38 bytes. Frameless ctor over the pinned SEH base
// (??0Rva00253510@@QAE@XZ at 0x253510 shared with the UpgradeDie family):
// base call then the distinctive vtable literal 0x00C4AD40 then the
// and-zero of the HoleName word at +0x38 then the float zeros of
// HoleMaxHealth at +0x3C and FadeInTimeSeconds at +0x40 (/arch:SSE keeps
// them as xorps plus movss) and the true byte at +0x44. Size 0x48 matches
// the 0x24CB18 factory news. Class identity is the rowed
// RebuildHoleExposeDieModuleData::buildFieldParse proc (HoleName plus
// HoleMaxHealth table 0x00C4AE00) beside the rowed RebuildHoleExposeDie
// pool key (0x486792) closing this cluster. The holeName pointer anchors
// the and-zero below the vtable store (else it hoists above it).

// Retail VA 0x00C4AD40 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_004869B0();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_004869B0=??_GRebuildHoleExposeDieModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C4AD40[] = {
	(const void *)&vfn_004869B0,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
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

class Rva00253510
{
public:
	Rva00253510();
};

class RebuildHoleExposeDieModuleData : public Rva00253510
{
public:
	RebuildHoleExposeDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_holeName; // +0x38 (name key data word)
	float m_holeMaxHealth; // +0x3C
	float m_fadeInTimeSeconds; // +0x40
	bool m_transferAttackers; // +0x44
};

// ??0RebuildHoleExposeDieModuleData@@QAE@XZ @0x48671F
RebuildHoleExposeDieModuleData::RebuildHoleExposeDieModuleData()
{
	int *holeName = &m_holeName;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4AD40));
	*holeName &= 0;
	m_holeMaxHealth = 0.0f;
	m_fadeInTimeSeconds = 0.0f;
	m_transferAttackers = true;
}
