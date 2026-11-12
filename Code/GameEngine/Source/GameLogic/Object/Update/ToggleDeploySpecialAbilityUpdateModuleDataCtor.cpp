// cl: /DNDEBUG /MD
//
// ??0ToggleDeploySpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE547,
// 32 bytes. ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54):
// installs vtable 0x00C553D8 explicitly (novtable) and clears the +0xC8 and
// +0xCC words (and-RMW, barrier-pinned below the vtable install per the
// BuffDraw precedent). Class size 0xD0 proven by the
// ToggleDeploySpecialAbilityUpdate data factory (news 0xD0, sole caller at
// 0x24F83D); base size 0xC8 inferred from the +0xC8 position. Row supersedes
// the ctor pin.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../../Include/Common/INI/FieldParse.h"

extern "C" void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00BEF820 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00BEF820[] = {
	{ "SoundDeploy", &__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "SoundUndeploy", &__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ 0, 0, 0, 0 }
};


#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class __declspec(novtable) ToggleDeploySpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ToggleDeploySpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8/+0xCC cleared words (end at the rowed 0xD0 instance size).
	unsigned int m_wordC8;
	unsigned int m_wordCC;
};

// ??0ToggleDeploySpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE547
// The retail table at RVA 0x008553D8: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GToggleDeploySpecialAbilityUpdateModuleData@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern const void *const g_00C553D8[31] = {
	(const void *)&__identifier("??_GToggleDeploySpecialAbilityUpdateModuleData@@UAEPAXI@Z"), // slot 0 0x004AE669
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
ToggleDeploySpecialAbilityUpdateModuleData::ToggleDeploySpecialAbilityUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	*(const void **)this = g_00C553D8;
	_ReadWriteBarrier();
	m_wordC8 &= 0;
	m_wordCC &= 0;
}

// ?buildFieldParse@ToggleDeploySpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024F7C3
void ToggleDeploySpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00BEF820, 0);
}
