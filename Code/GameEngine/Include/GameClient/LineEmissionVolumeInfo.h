// Target facts (RVAs unless marked VA): FXParticleSystem::LineEmissionVolumeInfo default constructor 0x003A6958 and copy constructor 0x003A653B install VA 0x00C1BB00 at +0. The copy first installs EmissionVolumeInfo's VA 0x00BE1548 and copies its byte at +4, proving the base at +0. Vector deleting destructor 0x003A69B4 passes stride 0x20 at 0x003A69CC, proving sizeof 0x20; destructor 0x0049B47C restores Snapshot's VA 0x00BBB554 during base teardown.
// VA 0x00C1BB00 has four slots, ending at the next table VA 0x00C1BB10: vector deleting destructor 0x003A69B4, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F354A ("EmissionVolumeInfo" at VA 0x00BE1558), and inherited DoXfer(Xfer &) 0x0047A69C. There are no additional virtual slots. Assignment 0x003A657A copies the base byte and two separate three-dword groups at +8 and +0x14; default construction zeros their six float components, and copy construction copies each dword through +0x1C.
// Retail callers 0x003A6609 and 0x003A6A69 call copy constructor 0x003A653B out of line. The ledger names the default/copy constructors, assignment and virtual destructor in FXParticleSystem; their bodies remain out of line. Coord3D supplies each three-float group's proven 12-byte shape; m_08 and m_14 identify offsets rather than original source names. The default constructor is folded with the unregistered CylinderEmissionVolumeInfo constructor; the inherited Snapshot name identifies their base, not a second registered object.
#pragma once

#ifndef __BFME2_LINEEMISSIONVOLUMEINFO_H_
#define __BFME2_LINEEMISSIONVOLUMEINFO_H_

#include "EmissionVolumeInfo.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

namespace FXParticleSystem
{

class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    LineEmissionVolumeInfo();
    LineEmissionVolumeInfo(const LineEmissionVolumeInfo &that);
    LineEmissionVolumeInfo &operator=(const LineEmissionVolumeInfo &that);
    virtual ~LineEmissionVolumeInfo();

    Coord3D m_08;
    Coord3D m_14;
};

}

using FXParticleSystem::LineEmissionVolumeInfo;

#endif
