// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
// The class derives from the canonical ModuleData (Snapshot at +0, module
// tag at +4), so the compiler installs ??_7SpawnBehaviorModuleData (retail
// 0x00BF4128, 31 ModuleData slots) and the unwind destroys the base through
// ModuleData's rowed destructor 0x0049B47C. Shape follows SupplyTruck (vector
// member driving the single EH state) over Chinook (0x110 shared member via
// the rowed construct).

#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

#include "../../../../Include/GameLogic/Module/Rva0025342CMember.h"

#include "../../../../Include/Common/ModuleData.h"

class SpawnBehaviorModuleData : public ModuleData
{
public:
	SpawnBehaviorModuleData();
	virtual ~SpawnBehaviorModuleData();

private:
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
inline SpawnBehaviorModuleData::SpawnBehaviorModuleData()
{
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

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeSpawnBehaviorModuleDataInlineAnchor@@YAXPAVSpawnBehaviorModuleData@@@Z absent-from-retail
void _bfmeSpawnBehaviorModuleDataInlineAnchor(SpawnBehaviorModuleData *spawnBehaviorModuleData)
{
    spawnBehaviorModuleData->SpawnBehaviorModuleData::SpawnBehaviorModuleData();
}
#pragma inline_depth()
