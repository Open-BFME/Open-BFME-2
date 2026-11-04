// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ??1TerrainResourceBehaviorModuleData@@UAE@XZ @ 0x00482275 48B
// Implicit virtual dtor restoring base vtable 0x00BBB554 with no base call.
// Member at +0x18 via pinned 0x00360D26. Layout from ctor TU 0x0048202F
// (base 8 radius +8 maxIncome +0xC interval +0x10 highPri +0x14 visible +0x15
// pad +0x16 member +0x18). Vtable 0x00849440 slot 0 is ??_G 0x00482259.
// The class views match TerrainResourceBehavior.cpp's, its approved TU.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
class TerrainResourceModuleDataBase
{
public:
	TerrainResourceModuleDataBase() {}
	virtual ~TerrainResourceModuleDataBase() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

private:
	unsigned char m_pad[8 - 4];
};
class UpgradeTemplate;
class BfmeTab1026;
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();

	unsigned int m_data; // +0, 4-aligned: retail pads +0x16/+0x17 before +0x18
};
class TerrainResourceBehaviorModuleData : public TerrainResourceModuleDataBase
{
public:
	TerrainResourceBehaviorModuleData();
	// The virtual destructor stays implicit: retail 0x00482275 stores no
	// derived vptr, which only the compiler-generated form omits.
	BfmeTab1026 *upgradeMustBePresent() const { return (BfmeTab1026 *)&m_upgradeMustBePresent; }

	float m_radius; // +8
	int m_maxIncome; // +0xC
	int m_incomeInterval; // +0x10
	bool m_highPriority; // +0x14
	bool m_visible; // +0x15
	Rva003623E5Filter m_upgradeMustBePresent; // +0x18
	const UpgradeTemplate *m_upgrade; // +0x1C
	float m_upgradeBonusPercent; // +0x20
};

// Emit the implicit destructor without a synthetic constructor.
void destroyTerrainResourceBehaviorModuleData(TerrainResourceBehaviorModuleData *terrainResourceBehaviorModuleData)
{
	terrainResourceBehaviorModuleData->TerrainResourceBehaviorModuleData::~TerrainResourceBehaviorModuleData();
}
