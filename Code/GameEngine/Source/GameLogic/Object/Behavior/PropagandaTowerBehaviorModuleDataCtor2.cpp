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

class PropagandaTowerBehaviorModuleDataBase
{
private:
	unsigned char m_unmodelled_04[4];
};

extern float g_bfmePropagandaRadius;	// 200.0 at retail 0xBCE190 (DIR32-masked)
extern float g_bfmePropagandaHeal;	// 0.01 at retail 0xBCF628 (DIR32-masked)
extern float g_bfmePropagandaUpgradedHeal;	// 0.02 at retail 0xBC6380 (DIR32-masked)

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
	*(unsigned int *)this = 0x00C49288;
	m_upgradeRequired = 0;
	m_radius = radius;
	m_healPercentEachSecond = g_bfmePropagandaHeal;
	float upgradedHeal = g_bfmePropagandaUpgradedHeal;
	m_delayBetweenUpdates = 15;
	m_upgradedHealPercentEachSecond = upgradedHeal;
	m_pulseFX = 0;
	m_upgradedPulseFX = 0;
}
