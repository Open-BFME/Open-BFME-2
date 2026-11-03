#pragma once

// Retail ctor 0x004999F1 and field table 0x00C503B0 establish the offsets.
// The destructor at 0x00499A16 releases the holder before the string and Snapshot.
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/BfmeAudioEventPrefix136.h"

struct DiscoveredSoundHolder : public OpaqueRefElement4
{
};

class OneRingPenaltyUpdateModuleData : public Snapshot
{
public:
    OneRingPenaltyUpdateModuleData();
    virtual ~OneRingPenaltyUpdateModuleData();

    unsigned int m_unused04; // +0x04, not initialized by the constructor
    AsciiString m_specialObjectName; // +0x08
    unsigned int m_ringTimeBeforeSpawning; // +0x0C
    unsigned int m_timeSpentRoamingAround; // +0x10
    unsigned int m_timeRingPowerSuppressed; // +0x14
    float m_startingDistanceFromMe; // +0x18
    unsigned int m_timeFrozenFromPenalty; // +0x1C
    DiscoveredSoundHolder m_discoveredSound; // +0x20
};
