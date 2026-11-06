// cl: /O1 /GX /arch:SSE /MD /DNDEBUG /Ireference/shims/moduledata
// ??1BoredUpdateModuleData@@UAE@XZ @ 0x004969B7 48B
// Implicit virtual dtor restoring Snapshot base vtable 0x00BBB554 with no
// base call. Member filter at +0x10 via pinned ??1Rva003623E5Filter at
// 0x00360D26 (folds with the opaque pool-aware dtors there).
// Layout from ctor TU 0x004966FE (unused +4 scanDelay +8 scanDist +C
// filter +10 canScan +14 specialPower +18 size 0x1C).
// Vtable 0x0084F590 slot 0 is ??_G 0x0049699B.
// ShareExperienceBehaviorModuleDataDtor precedent.
#include "Common/Snapshot.h"
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
class BoredUpdateModuleData : public Snapshot
{
public:
	BoredUpdateModuleData(); // rowed in BoredUpdateModuleDataCtor.cpp
	BoredUpdateModuleData(struct EmitVtableTag *); // vtable anchor, no retail body
// Implicit virtual dtor (never declared, never defined)
private:
	unsigned char m_unk04[4];
	int m_scanDelayTime;
	float m_scanDistance;
	Rva003623E5Filter m_filter;
	unsigned char m_canScanWhileAttackingOrMoving;
	unsigned char m_pad15[3];
	int m_specialPowerTemplate;
};
// ?<BoredUpdateModuleData::BoredUpdateModuleData> absent-from-retail
BoredUpdateModuleData::BoredUpdateModuleData(EmitVtableTag *)
{
}
void deleteBoredUpdateModuleData(BoredUpdateModuleData *boredUpdateModuleData)
{
	delete boredUpdateModuleData;
}
