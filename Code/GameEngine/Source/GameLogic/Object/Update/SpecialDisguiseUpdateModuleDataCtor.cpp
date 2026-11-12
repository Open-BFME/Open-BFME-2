// cl: /DNDEBUG /MD
//
// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ, retail 0x004B0255, 61 bytes.
// Disguise module data ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54,
// 0xC8 bytes): installs vtable 0x00C563F8 explicitly (novtable, no compiler
// emission), clears DisguiseAsTemplate/EnemyPerspective/DisguiseFX at
// +0xD0/+0xD4/+0xD8, clears TriggerInstantlyOnCreate at +0xC8 and
// ForceMountedWhenDisguising at +0xDC, and zeroes OpacityTarget at +0xCC
// via xorps float zero (/arch:SSE emits retail movss). Table 0x00BEF8B8
// proves the six fields at identical offsets; factory 0x24F9D8 (news 0xE0,
// sole caller) proves the class size. Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class __declspec(novtable) SpecialDisguiseUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	SpecialDisguiseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 TriggerInstantlyOnCreate (table offset).
	bool m_triggerInstantlyOnCreate;
	// +0xC9 pad.
	unsigned char m_padC9[3];
	// +0xCC OpacityTarget (table offset).
	float m_opacityTarget;
	// +0xD0 DisguiseAsTemplate (table offset).
	int m_disguiseAsTemplate;
	// +0xD4 DisguisedAsTemplate_EnemyPerspective (table offset).
	int m_disguisedAsEnemy;
	// +0xD8 DisguiseFX (table offset).
	int m_disguiseFX;
	// +0xDC ForceMountedWhenDisguising (table offset).
	bool m_forceMounted;
	// +0xDD pad to the 0xE0 factory size.
	unsigned char m_padDD[3];
};

// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ @0x004B0255
// The retail table at RVA 0x008563F8: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GSpecialDisguiseUpdateModuleData@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern const void *const g_00C563F8[31] = {
	(const void *)&__identifier("??_GSpecialDisguiseUpdateModuleData@@UAEPAXI@Z"), // slot 0 0x004B044C
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"), // slot 2 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 6 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 7 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"), // slot 14 0x000B69A1
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30 0x0050B5C6
};
SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	int *disguiseAsTemplate = &m_disguiseAsTemplate;
	*(const void **)this = g_00C563F8;
	*disguiseAsTemplate = 0;
	m_disguisedAsEnemy = 0;
	m_triggerInstantlyOnCreate = false;
	m_disguiseFX = 0;
	m_forceMounted = false;
	m_opacityTarget = 0.0f;
}
