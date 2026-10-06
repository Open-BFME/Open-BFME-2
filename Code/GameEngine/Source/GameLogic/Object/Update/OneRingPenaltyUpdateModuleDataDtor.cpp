// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /DNDEBUG /MD
//
// ??1OneRingPenaltyUpdateModuleData@@UAE@XZ, retail 0x00499A16, 73 bytes.
// OneRingPenaltyUpdate ModuleData dtor over Snapshot base (0x00BBB554).
// Restores own vtable 0x00C50298, releases the +0x20 holder through the rowed
// Release_Ref at 0x00050ED3 when non-null, destroys the AsciiString at +0x08
// through the folded 0x00036410, then restores the Snapshot base vtable.
// Layout follows the verified ctor at 0x004999F1 in
// OneRingPenaltyUpdateModuleDataCtor.cpp (vptr +0, unused +0x04, string +0x08,
// scalars +0x0C..+0x1C, holder +0x20, size 0x24 from factory 0x0024E42C).
// Called by the audited ??_G wrapper at 0x00499C19 (slot 0 of 0x00C50298).
// Shape follows FlammableUpdateModuleDataDtor (shared Snapshot base with its
// BBB554 restore, entry derived store, empty derived body). BFME1 donor
// OneRingPenaltyUpdateModuleDataDestructorThunk.cpp:82 proves the member
// order and Snapshot base; retail followed.

#include "Common/Snapshot.h"

#include "ascii_string.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct DiscoveredSoundHolder
{
	~DiscoveredSoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class OneRingPenaltyUpdateModuleData : public Snapshot
{
public:
	virtual ~OneRingPenaltyUpdateModuleData();

private:
	int m_unused04; // +0x04
	AsciiString m_specialObjectName; // +0x08
	unsigned int m_ringTimeBeforeSpawning; // +0x0C
	unsigned int m_timeSpentRoamingAround; // +0x10
	unsigned int m_timeRingPowerSuppressed; // +0x14
	float m_startingDistanceFromMe; // +0x18
	unsigned int m_timeFrozenFromPenalty; // +0x1C
	DiscoveredSoundHolder m_discoveredSound; // +0x20
};

OneRingPenaltyUpdateModuleData::~OneRingPenaltyUpdateModuleData()
{
}
