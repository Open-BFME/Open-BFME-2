// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??1PropagandaTowerBehaviorModuleData@@UAE@XZ retail 0x00481BCE 48 bytes.
// Virtual dtor over vtable 0x00C49288 (slot 0 deleting dtor at 0x00481BB2).
// Layout from rowed ctor 0x0048197C (Radius@08 Delay@0C Heal@10 PulseFX@14
// UpgradeRequired AsciiString@18 UpgradedHeal@1C UpgradedPulseFX@20 news 0x24
// INI table 0xC49368). Destruction is the AsciiString at +0x18 via the folded
// 0x00036410 teardown then the Snapshot base vtable 0x00BBB554 restored inline
// with no base call. Shape follows RunOffMapBehaviorModuleDataDtor 48B precedent
// (single AsciiString plus BBB554; offset 0x18 vs 0x14).

#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) PropagandaTowerBehaviorModuleData : public Snapshot
{
public:
	virtual ~PropagandaTowerBehaviorModuleData();
private:
	int m_unused04; // +0x04
	float m_radius; // +0x08
	int m_delayBetweenUpdates; // +0x0C
	float m_healPercentEachSecond; // +0x10
	const void *m_pulseFX; // +0x14
	AsciiString m_upgradeRequired; // +0x18
	float m_upgradedHealPercentEachSecond; // +0x1C
	const void *m_upgradedPulseFX; // +0x20
};

PropagandaTowerBehaviorModuleData::~PropagandaTowerBehaviorModuleData()
{
}
