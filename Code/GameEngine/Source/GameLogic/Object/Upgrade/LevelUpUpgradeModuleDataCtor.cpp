// cl: /O1 /DNDEBUG /MD
//
// ??0LevelUpUpgradeModuleData@@QAE@XZ, retail 0x0025467E, 32 bytes.
// Frameless ctor over the rowed OpenContainModuleData base (0x253487):
// vtable literal 0x00BF24A0 installed last (overwriting the base folded
// vtable), LevelsToGain zero at +0x118 plus LevelCap zero at +0x11C
// matching the own table at 0x00C574AC. Identity is the LevelUpUpgrade pool
// key at 0x4B3D61 in the same cluster plus the chained buildFieldParse at
// 0x4B3DA6 plus the ModuleData factory at 0x25469E which news 0x120.
// Shape follows ChinookAIUpdateModuleDataCtor (explicit vtable last over a
// rowed base with trailing zeros).

// Retail VA 0x00BF24A0 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0047A6A9();
extern "C" void vfn_004A10FD();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A6A9=??0Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_004A10FD=??_GObjectModule@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00BF24A0[] = {
	(const void *)&vfn_004A10FD,
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
	(const void *)&vfn_0050B5C6,
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
	(const void *)&vfn_0047A6A9,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

class OpenContainModuleData
{
public:
	OpenContainModuleData();

private:
	unsigned char m_pad[0x118];
};

class LevelUpUpgradeModuleData : public OpenContainModuleData
{
public:
	LevelUpUpgradeModuleData();

private:
	int m_levelsToGain; // +0x118
	int m_levelCap; // +0x11C
};

// ??0LevelUpUpgradeModuleData@@QAE@XZ @0x25467E
LevelUpUpgradeModuleData::LevelUpUpgradeModuleData()
{
	m_levelsToGain = 0;
	m_levelCap = 0;
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BF24A0));
}
