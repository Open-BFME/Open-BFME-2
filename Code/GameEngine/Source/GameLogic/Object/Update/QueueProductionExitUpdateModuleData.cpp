// ??0QueueProductionExitUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-29
// cl: /DNDEBUG /MD
//
// Identity: retail ModuleFactory registers "QueueProductionExitUpdate" with a
// data factory that calls this ctor (tools/check_module_registry.py).
// ??0QueueProductionExitUpdateModuleData@@QAE@XZ @ 0x002541FA (68B). Ctor stores vtable 0x00BF1D58,
// six floats at +0x08..+0x1C via movss, ints/bytes at +0x20..+0x32, byte +0x32=1.
// Caller at 0x0025425E. Finish from banked 0.97 stash: xor ecx early vs late
// only diff; try literals for ints so xor lands late like retail.
#include <new.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class QueueProductionExitUpdateModuleData
{
public:
	QueueProductionExitUpdateModuleData();
private:
	const void *m_vtable;
	int m_unk04;
	float m_f08;
	float m_f0C;
	float m_f10;
	float m_f14;
	float m_f18;
	float m_f1C;
	int m_exitDelay;
	unsigned char m_allowAirborneCreation;
	unsigned char m_pad25[3];
	int m_initialBurst;
	float m_f2C;
	unsigned char m_noExitPath;
	unsigned char m_canRallyToSlaughter;
	unsigned char m_useReturnToFormation;
};
// The retail table at RVA 0x007F1D58: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRadarObject@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("??0BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern const void *const g_00BF1D58[31] = {
	(const void *)&__identifier("??_GRadarObject@@UAEPAXI@Z"), // slot 0 0x004A10FD
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
	(const void *)&__identifier("??0BfmeRadarMapPoint@@QAE@XZ"), // slot 25 0x0047A6A9
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30 0x0050B5C6
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline QueueProductionExitUpdateModuleData::QueueProductionExitUpdateModuleData()
{
	float fzero = 0.0f;
	m_vtable = (const void *)g_00BF1D58;
	m_f08 = fzero;
	m_f0C = fzero;
	m_f10 = fzero;
	m_f14 = fzero;
	m_f18 = fzero;
	m_f1C = fzero;
	_ReadWriteBarrier();
	m_exitDelay = 0;
	m_allowAirborneCreation = 0;
	m_initialBurst = 0;
	m_f2C = fzero;
	m_noExitPath = 0;
	m_canRallyToSlaughter = 0;
	m_useReturnToFormation = 1;
}

// ?bfmeAnchorQueueProductionExitUpdateModuleDataCtor absent-from-retail
void *bfmeAnchorQueueProductionExitUpdateModuleDataCtor(void *where)
{
	return ::new (where) QueueProductionExitUpdateModuleData();
}
