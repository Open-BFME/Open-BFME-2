// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SpawnBehaviorModuleData@@QAE@XZ, retail 0x002575C2, 145 bytes.
//
// SpawnBehavior keeps a group of spawned units and replaces as needed
// (BFME1 SpawnBehavior.cpp donor). The ModuleData side is donor-verbatim:
// SpawnNumber/SpawnReplaceDelay/InitialBurst ints at +8/+C/+10, six flag
// bytes at +14..+19, the spawn-template vector at +0x20 (cleared, not
// assigned), DieMuxData at +0x2C (rowed init), the shared-construct block
// at +0x5C (rowed Rva0025342CMember::construct, 0x110 bytes ending exactly
// at +0x16C), FadeInTime at +0x16C plus three flag bytes. The damage-type
// flags at +0x1C are left unstored, matching the BFME1 donor which never
// initializes m_damageTypesToPropagateToSlaves. Table 0xBF0200 carries all
// fifteen fields at these offsets (field_names votes put SpawnNumber@8 and
// SpawnTemplateName@0x20 on SpawnBehaviorModuleData); factory 0x25769F
// news 0x174 with this ctor as sole caller and pushes the rowed proc.
// Shape follows SupplyTruck (empty base, init-listed explicit vtable,
// vector member driving the single EH state) over Chinook (0x110 shared
// member via the rowed construct).

#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class DieMuxData
{
public:
	DieMuxData *init();

private:
	unsigned char m_pad[0x30];
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class BehaviorModuleData
{
public:
	BehaviorModuleData() {}
	~BehaviorModuleData();
};

class SpawnBehaviorModuleData : public BehaviorModuleData
{
public:
	SpawnBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_spawnNumberData; // +8
	int m_spawnReplaceDelayData; // +0xC
	int m_initialBurst; // +0x10
	bool m_isOneShotData; // +0x14
	bool m_canReclaimOrphans; // +0x15
	bool m_aggregateHealth; // +0x16
	bool m_exitByBudding; // +0x17
	bool m_spawnedRequireSpawner; // +0x18
	bool m_respectCommandLimit; // +0x19
	unsigned char m_pad1A[2];
	int m_damageTypesToPropagateToSlaves; // +0x1C, unstored per donor
	_STL::vector<AsciiString> m_spawnTemplateNameData; // +0x20
	DieMuxData m_dieMuxData; // +0x2C
	Rva0025342CMember m_slaveBlock; // +0x5C
	int m_fadeInTime; // +0x16C
	bool m_killSpawnsBasedOnModelConditionState; // +0x170
	bool m_shareUpgrades; // +0x171
	bool m_spawnInsideBuilding; // +0x172
	unsigned char m_pad173;
};

// ??0SpawnBehaviorModuleData@@QAE@XZ @0x2575C2
SpawnBehaviorModuleData::SpawnBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF4128))
{
	m_dieMuxData.init();
	m_slaveBlock.construct();
	m_spawnNumberData = 0;
	m_spawnReplaceDelayData = 0;
	m_initialBurst = 0;
	m_isOneShotData = false;
	m_canReclaimOrphans = false;
	m_aggregateHealth = false;
	m_exitByBudding = false;
	m_spawnTemplateNameData.clear();
	m_spawnedRequireSpawner = false;
	m_respectCommandLimit = false;
	m_fadeInTime = 0;
	m_killSpawnsBasedOnModelConditionState = false;
	m_shareUpgrades = false;
	m_spawnInsideBuilding = false;
}
