// cl: /DNDEBUG /MD /EHsc

// ??0OneRingPenaltyUpdateModuleData@@QAE@XZ at retail 0x004999F1 (37 bytes).
// The module-data half of OneRingPenaltyUpdate: vtable immediate 0x00C50298
// modelled as an explicit first member (DemoTrapUpdateModuleDataCtor
// precedent, so no vtable is emitted and no dtor row is owed), an unstored
// word at +0x04 retail never touches, then the seven table-backed slots the
// BFME1 OneRingPenaltyUpdateModuleData donor constructs in this exact order:
// SpecialObjectName at +0x08, DiscoveredSound at +0x20, RingTimeBeforeSpawning
// at +0x0C, TimeSpentRoamingAround at +0x10, TimeRingPowerSuppressed at +0x14,
// StartingDistanceFromMe (a real) at +0x18 and TimeFrozenFromPenalty at +0x1C.
// Retail's own INI table at 0x00C503B0 (landed buildFieldParse row) proves the
// names and offsets; the BFME1 donor proves the store order. Sole caller is
// the rowed 0x24E42C factory which news 0x24 and pushes the rowed proc.
extern "C" const void *const vtbl_00C50298[];  // ??_7OneRingPenaltyUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C50298=??_7OneRingPenaltyUpdateModuleData@@6B@")

class OneRingPenaltyUpdateModuleData
{
public:
	OneRingPenaltyUpdateModuleData();

private:
	const void *m_vtable;					// +0x00
	unsigned int m_unused04;				// +0x04 retail never stores
	const char *m_specialObjectName;		// +0x08
	unsigned int m_ringTimeBeforeSpawning;	// +0x0C
	unsigned int m_timeSpentRoamingAround;	// +0x10
	unsigned int m_timeRingPowerSuppressed;	// +0x14
	float m_startingDistanceFromMe;			// +0x18
	unsigned int m_timeFrozenFromPenalty;	// +0x1C
	const char *m_discoveredSound;			// +0x20
};

// ??0OneRingPenaltyUpdateModuleData@@QAE@XZ
OneRingPenaltyUpdateModuleData::OneRingPenaltyUpdateModuleData()
	: m_vtable( reinterpret_cast<const void *>(((unsigned int)vtbl_00C50298)) )
{
	m_specialObjectName = 0;
	m_discoveredSound = 0;
	m_timeSpentRoamingAround = 0;
	m_timeRingPowerSuppressed = 0;
	m_startingDistanceFromMe = 0.0f;
	m_ringTimeBeforeSpawning = 0;
	m_timeFrozenFromPenalty = 0;
}
