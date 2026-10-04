// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0PropagandaTowerBehaviorModuleData@@QAE@XZ, retail 0x0048197C, 66 bytes.
// Frameless ModuleData ctor: implicit base (no base call, derived writes the
// vtable 0x00C49288 directly, base word at +0x04 left alone), then the seven
// INI-table fields at +0x08/+0x0C/+0x10/+0x14/+0x18/+0x1C/+0x20. Table
// 0x00C49368 proves the names and offsets (Radius/DelayBetweenUpdates/
// HealPercentEachSecond/PulseFX/UpgradeRequired/UpgradedHealPercentEachSecond/
// UpgradedPulseFX). The three floats load from extern globals (DIR32-masked;
// literals would emit integer mov-imms instead of the retail movss loads).

// Retail VA 0x00C49288 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_00481BB2();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_00481BB2=??_GPropagandaTowerBehaviorModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C49288[] = {
	(const void *)&vfn_00481BB2,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
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

class PropagandaTowerBehaviorModuleDataBase
{
private:
	unsigned char m_unmodelled_04[4];
};

extern float g_bfmePropagandaRadius;	// 200.0 at retail 0xBCE190 (DIR32-masked)
// g_bfmePropagandaRadius: matched references place it at VA 0xbce190 (retail .rdata value 2e+02f).
float g_bfmePropagandaRadius = 2e+02f;
extern float g_bfmePropagandaHeal;	// 0.01 at retail 0xBCF628 (DIR32-masked)
extern float g_bfmePropagandaUpgradedHeal;	// 0.02 at retail 0xBC6380 (DIR32-masked)
// g_bfmePropagandaUpgradedHeal: matched references place it at VA 0xbc6380 (retail .rdata value 0.02f).
float g_bfmePropagandaUpgradedHeal = 0.02f;

class FXList;
class UpgradeTemplate;

class __declspec(novtable) PropagandaTowerBehaviorModuleData : public PropagandaTowerBehaviorModuleDataBase
{
public:
	PropagandaTowerBehaviorModuleData();
	virtual void moduleDataAnchor();

private:
	float m_radius;	// +0x08 Radius
	int m_delayBetweenUpdates;	// +0x0C DelayBetweenUpdates
	float m_healPercentEachSecond;	// +0x10 HealPercentEachSecond
	const FXList *m_pulseFX;	// +0x14 PulseFX
	const UpgradeTemplate *m_upgradeRequired;	// +0x18 UpgradeRequired
	float m_upgradedHealPercentEachSecond;	// +0x1C UpgradedHealPercentEachSecond
	const FXList *m_upgradedPulseFX;	// +0x20 UpgradedPulseFX
};

PropagandaTowerBehaviorModuleData::PropagandaTowerBehaviorModuleData()
{
	float radius = g_bfmePropagandaRadius;
	*(unsigned int *)this = ((unsigned int)vtbl_00C49288);
	m_upgradeRequired = 0;
	m_radius = radius;
	m_healPercentEachSecond = g_bfmePropagandaHeal;
	float upgradedHeal = g_bfmePropagandaUpgradedHeal;
	m_delayBetweenUpdates = 15;
	m_upgradedHealPercentEachSecond = upgradedHeal;
	m_pulseFX = 0;
	m_upgradedPulseFX = 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_bfmePropagandaHeal@@3MA=__real@3c23d70a")
