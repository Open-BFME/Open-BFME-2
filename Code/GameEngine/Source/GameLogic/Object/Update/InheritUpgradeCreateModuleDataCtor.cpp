// cl: /GX /DNDEBUG /MD
//
// ??0InheritUpgradeCreateModuleData@@QAE@XZ, retail 0x004B9508, 69 bytes.
// EH ctor: single state-0 store, vtable 0x00C59768 at +0, 0.0f at +8, member
// at +0xC zeroed through the rowed clear80 helper, member at +0x8C built by
// the pinned nullary ctor. Table 0xC59728 holds Radius@8 Upgrade@C
// ObjectFilter@8C; factory 0x250CC3 news 0x90. V4: empty CreateModuleData
// base as the sole unwindable (state 0, no transitions, no -1) plus body in
// retail order; the filter is a plain member driven by a construct-method
// alias pin (a declared ctor would implicitly construct early AND double
// with any body call).

#include "../../../../Include/Common/Rva001EAE6FHelper.h"

class Rva003623E5Member
{
public:
	void construct();

private:
	int m_value;
};

class CreateModuleData
{
public:
	CreateModuleData() {}
	~CreateModuleData();

private:
};

class InheritUpgradeCreateModuleData : public CreateModuleData
{
public:
	InheritUpgradeCreateModuleData();

private:
	void *m_vtable;
	unsigned int m_unused04;
	float m_radius;
	Rva001EAE6FHelper m_upgrade;
	Rva003623E5Member m_filter;
};

extern "C" {
void __identifier("??0RealRange@@QAE@XZ")();
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}

// RVA 0x00859768; 32 code pointers, each the ledger row at the native address.
extern const void *const g_00C59768[32];
const void *const g_00C59768[32] = {
	(const void *)&__identifier("??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z"), // slot 0, RVA 0x004B954D
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"), // slot 2, RVA 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3, RVA 0x0047A69C
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 6, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 7, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12, RVA 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13, RVA 0x0047A699
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"), // slot 14, RVA 0x000B69A1
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15, RVA 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29, RVA 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30, RVA 0x0050B5C6
	(const void *)&__identifier("??0RealRange@@QAE@XZ"), // slot 31, RVA 0x0047A6A9
};

// ??0InheritUpgradeCreateModuleData@@QAE@XZ
InheritUpgradeCreateModuleData::InheritUpgradeCreateModuleData()
{
	m_vtable = (void *)g_00C59768;
	m_radius = 0.0f;
	m_upgrade.clear80();
	m_filter.construct();
}
