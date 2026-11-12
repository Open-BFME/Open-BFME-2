// cl: /O1 /MD /GX /DNDEBUG /arch:SSE
//
// ??0WorkerAIUpdateModuleData@@QAE@XZ, retail 0x00254434 (101 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): installs the
// explicit vtable 0x00BF23C8 first (DeployStyle precedent: pointer-cast
// write, no virtuals declared on the derived class so no vtable is emitted
// here; the address is unique image-wide with this ctor its sole installer),
// then zeroes voice/maxBoxes, the three float zeros, the two action-delay
// ints, the harvest-trees bool, stores scan distance 100.0, sets the two
// harvest times to 1 and stores activation range 50.0. Field identity is
// the rowed base-call buildFieldParse proc at 0x0024F299 (Transport base
// proc plus table 0x00BEF620 holding MaxBoxes at +0x64 through
// SuppliesDepletedVoice at +0x90). Sole raw caller is the rowed ModuleData
// factory 0x002544F1 which news 0x94; this row supersedes the ctor pin.

// The retail table at RVA 0x007F23C8: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva002544B5@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
}
extern "C" const void *const vtbl_00BF23C8[31] = {
	(const void *)&__identifier("??_GRva002544B5@@UAEPAXI@Z"), // slot 0 0x00254499
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"), // slot 2 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 4 0x0050B5C6
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
#include "../../../../../Include/GameLogic/Module/TransportAIUpdateModuleData.h"

class WorkerAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	WorkerAIUpdateModuleData();

private:
	int m_maxBoxes;					// +0x64
	float m_repairHealthPercentPerSecond;	// +0x68
	float m_boredTime;				// +0x6C
	float m_boredRange;				// +0x70
	int m_supplyCenterActionDelay;	// +0x74
	int m_supplyWarehouseActionDelay;	// +0x78
	float m_supplyWarehouseScanDistance;	// +0x7C
	bool m_harvestTrees;			// +0x80
	float m_harvestActivationRange;	// +0x84
	int m_harvestPreparationTime;	// +0x88
	int m_harvestActionTime;		// +0x8C
	int m_suppliesDepletedVoice;	// +0x90
};

// ??0WorkerAIUpdateModuleData@@QAE@XZ @0x00254434
inline WorkerAIUpdateModuleData::WorkerAIUpdateModuleData()
{
	int *voice = &m_suppliesDepletedVoice;
	int *maxBoxes = &m_maxBoxes;
	*(unsigned int *)this = ((unsigned int)vtbl_00BF23C8);
	*voice = 0;
	*maxBoxes = 0;
	m_repairHealthPercentPerSecond = 0.0f;
	m_boredTime = 0.0f;
	m_boredRange = 0.0f;
	m_supplyCenterActionDelay = 0;
	m_supplyWarehouseActionDelay = 0;
	m_harvestTrees = false;
	m_supplyWarehouseScanDistance = 100.0f;
	m_harvestPreparationTime = 1;
	m_harvestActionTime = 1;
	m_harvestActivationRange = 50.0f;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeWorkerAIUpdateModuleDataInlineAnchor@@YAXPAVWorkerAIUpdateModuleData@@@Z absent-from-retail
void _bfmeWorkerAIUpdateModuleDataInlineAnchor(WorkerAIUpdateModuleData *workerAIUpdateModuleData)
{
    workerAIUpdateModuleData->WorkerAIUpdateModuleData::WorkerAIUpdateModuleData();
}
#pragma inline_depth()
