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
extern "C" void __cdecl __identifier("??_GRva004C1B7B@@UAEPAXI@Z")(void);
extern "C" void __cdecl __identifier("??1Coord2D@@QAE@XZ")(void);
extern "C" void __cdecl __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")(void);
extern "C" void __cdecl __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")(void);
extern "C" void __cdecl __identifier("?IsCRC@Xfer@@UBE_NXZ")(void);
extern "C" void __cdecl __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")(void);
extern "C" void __cdecl __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")(void);
extern "C" void __cdecl __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")(void);

extern const void *const g_00C5BC48[] = {
	(const void *)&__identifier("??_GRva004C1B7B@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z"),
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

#include "../../../../Include/GameLogic/Module/RespawnBodyModuleData.h"

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
