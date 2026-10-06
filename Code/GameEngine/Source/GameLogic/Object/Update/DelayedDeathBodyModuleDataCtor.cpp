// cl: /DNDEBUG /MD
//
// ??0DelayedDeathBodyModuleData@@QAE@XZ, retail 0x004C180A (37 bytes).
// Frameless Body-side ModuleData for delayed death: runs the pinned
// RespawnUpdate base ctor (0x4C14DF), installs the explicit vtable 0xC5BC48,
// zeroes the DelayedDeath scalars and sets the Immortal and DoHealthCheck
// bytes matching the rowed chained proc's table 0x0085BAE8
// (DelayedDeathTime at +0x6C, ImmortalUntilDeathTime at +0x70,
// InvulnerableFX at +0x74, DoHealthCheck at +0x78,
// DelayedDeathPrerequisiteUpgrade at +0x7C). Flat classes throughout (no
// declared dtors anywhere) keep the body frameless. The DelayedDeathBody
// pool key at 0x4C1642 sits in the same cluster; the ModuleData factory at
// 0x251622 (news 0x80) is the only raw caller. Supersedes nothing (no pin);
// the FreeLifeBody sibling shares the base and vtable.

// vftable_map identifies the 31 slots at 0x00C5BC48 from both installers;
// every target is a matched body. No data_xrefs row bounds this table.
extern "C" void __cdecl c5bc48Slot0(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot0=??_GRva004C1B7B@@UAEPAXI@Z")
extern "C" void __cdecl c5bc48Slot1(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot1=??1Coord2D@@QAE@XZ")
extern "C" void __cdecl c5bc48Slot2(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot2=?name@Rva00065212Named@@QBEPBDXZ")
extern "C" void __cdecl c5bc48Slot3(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot3=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
extern "C" void __cdecl c5bc48Slot4(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot4=?IsCRC@Xfer@@UBE_NXZ")
extern "C" void __cdecl c5bc48Slot7(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot7=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" void __cdecl c5bc48Slot14(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot14=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
extern "C" void __cdecl c5bc48Slot16(void);
#pragma comment(linker, "/alternatename:_c5bc48Slot16=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

extern const void *const g_00C5BC48[] = {
	(const void *)&c5bc48Slot0,
	(const void *)&c5bc48Slot1,
	(const void *)&c5bc48Slot2,
	(const void *)&c5bc48Slot3,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot7,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot14,
	(const void *)&c5bc48Slot4,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot16,
	(const void *)&c5bc48Slot7
};

class RespawnBodyModuleData
{
public:
	RespawnBodyModuleData();

private:
	unsigned char m_pad[0x6C];
};

class DelayedDeathBodyModuleData : public RespawnBodyModuleData
{
public:
	DelayedDeathBodyModuleData();

private:
	int m_delayedDeathTime; // +0x6C
	unsigned char m_immortal; // +0x70
	unsigned char m_pad71[3];
	int m_invulnerableFX; // +0x74
	unsigned char m_doHealthCheck; // +0x78
	unsigned char m_pad79[3];
	int m_prerequisite; // +0x7C
};

// ??0DelayedDeathBodyModuleData@@QAE@XZ @0x4C180A
DelayedDeathBodyModuleData::DelayedDeathBodyModuleData()
	: RespawnBodyModuleData()
{
	m_delayedDeathTime = 0;
	m_invulnerableFX = 0;
	m_prerequisite = 0;
	*(unsigned int *)this = (unsigned int)g_00C5BC48;
	m_immortal = 1;
	m_doHealthCheck = 1;
}
