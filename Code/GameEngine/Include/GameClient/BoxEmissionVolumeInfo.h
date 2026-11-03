// Target facts (RVAs unless marked VA): FXParticleSystem::BoxEmissionVolumeInfo constructors 0x003A664A and 0x003A6669 install VA 0x00C1BB30 at +0. The copy first installs EmissionVolumeInfo's VA 0x00BE1548 and copies its byte at +4, proving the base at +0. Default construction zeroes floats at +8, +0x0C and +0x10; assignment 0x003A6696 copies the base byte and one three-dword block at +8. Vector deleting destructor 0x003A66B2 pushes stride 0x14 at 0x003A66CA, proving sizeof 0x14; the parent stride is 0x08 at 0x001F358C.
// VA 0x00C1BB30 has four slots: vector deleting destructor 0x003A66B2, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F354A ("EmissionVolumeInfo" at VA 0x00BE1558), and inherited DoXfer(Xfer &) 0x0047A69C. The next table VA 0x00C1BB40 is installed at +8 by the module-template copy constructor 0x003A6738. Complete destructor 0x0049B47C restores Snapshot's VA 0x00BBB554 during empty base teardown; dead derived stores are omitted. The shared destructor and inherited Snapshot name do not identify Box with its 8-byte parent.
// Copy callers 0x003A6738 and 0x003AC034 call 0x003A6669 out of line; the latter places the Box base at +0x1C. The ledger names the namespace, default/copy constructors, assignment and virtual destructor; their bodies remain out of line. Coord3D supplies the proven 12-byte three-float group. m_08 identifies its offset rather than an original source spelling; the three remaining virtual slots are inherited from the registered parent.
#pragma once

#ifndef __BFME2_BOXEMISSIONVOLUMEINFO_H_
#define __BFME2_BOXEMISSIONVOLUMEINFO_H_

#include "EmissionVolumeInfo.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

namespace FXParticleSystem
{

class BoxEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    BoxEmissionVolumeInfo();
    BoxEmissionVolumeInfo(const BoxEmissionVolumeInfo &that);
    BoxEmissionVolumeInfo &operator=(const BoxEmissionVolumeInfo &that);
    virtual ~BoxEmissionVolumeInfo();

    Coord3D m_08;
};

}

using FXParticleSystem::BoxEmissionVolumeInfo;

#endif
