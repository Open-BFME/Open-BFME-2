// cl: /O1 /MD /DNDEBUG
//
// ??0PorcupineFormationBodyModuleData@@QAE@XZ, retail 0x004C225D (29 bytes).
// Frameless derived ctor over the rowed ActiveBodyModuleData base
// (0x004BF59F, size 0x64): the base call builds the base, two int slots and
// a byte slot clear through a shared xor-eax, then the derived installs
// vtable 0x00BF4028 explicitly at the end (Defector law; the classes carry
// no virtuals so the compiler emits no store of its own). No EH (the lone
// base call precedes any construction). Identity is the ModuleFactory
// registration under "PorcupineFormationBody" (sole-caller data factory per
// the superseded ctor pin).

// Retail VA 0x00BF4028 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0025706B();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0025706B=??_GStructureBodyModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00BF4028[] = {
	(const void *)&vfn_0025706B,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0050B5C6,
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

class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0x64 base: the rowed base carries its own vtable plus members, and
	// the derived tail sits at +0x64.
	unsigned char m_opaque[0x64];
};

class PorcupineFormationBodyModuleData : public ActiveBodyModuleData
{
public:
	PorcupineFormationBodyModuleData();

private:
	int m_int64;	// +0x64
	int m_int68;	// +0x68
	bool m_flag6C;	// +0x6C
};

PorcupineFormationBodyModuleData::PorcupineFormationBodyModuleData()
	: ActiveBodyModuleData()
{
	m_int64 = 0;
	m_int68 = 0;
	m_flag6C = false;
	*(unsigned int *)this = ((unsigned int)vtbl_00BF4028);
}
