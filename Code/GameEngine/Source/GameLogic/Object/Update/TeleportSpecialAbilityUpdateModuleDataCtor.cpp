// cl: /DNDEBUG /MD
//
// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00492E43, 54 bytes.
// ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54, 0xC8 bytes
// per the ArrowStorm row): installs vtable 0x00C4E208 explicitly
// (novtable, no compiler emission), zeroes BusyForDuration at +0xC8,
// DestinationWeaponName at +0xCC and SourceWeaponName at +0xD0, and sets
// MaxDistance at +0xD4 to -1.0f (pools to 0x00BBB9AC via /arch:SSE movss).
// Table 0x00BEF150 proves the four fields at identical offsets; factory
// 0x24DC00 (news 0xD8, sole caller) proves the class size. Row supersedes
// the ctor pin.

// Retail VA 0x00C4E208 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("??_GTeleportSpecialAbilityUpdateModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00C4E208[] = {
	(const void *)&__identifier("??_GTeleportSpecialAbilityUpdateModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
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

class MultiIniFieldParse;
struct FieldParse;

#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class __declspec(novtable) TeleportSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	TeleportSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 BusyForDuration (table offset).
	int m_busyForDuration;
	// +0xCC DestinationWeaponName (table offset).
	int m_destinationWeaponName;
	// +0xD0 SourceWeaponName (table offset).
	int m_sourceWeaponName;
	// +0xD4 MaxDistance (table offset).
	float m_maxDistance;
};

// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ @0x00492E43
TeleportSpecialAbilityUpdateModuleData::TeleportSpecialAbilityUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_busyForDuration = 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C4E208);
	int *destinationWeaponName = &m_destinationWeaponName;
	int *sourceWeaponName = &m_sourceWeaponName;
	*destinationWeaponName = 0;
	*sourceWeaponName = 0;
	m_maxDistance = -1.0f;
}
