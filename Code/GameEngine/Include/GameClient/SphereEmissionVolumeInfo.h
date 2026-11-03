// Target facts (RVAs unless marked VA): FXParticleSystem::SphereEmissionVolumeInfo default constructor 0x003A67E8 installs VA 0x00C1BB60 at +0, clears the inherited byte at +4 and zeroes a float at +8. Copy constructor 0x003A67FD calls EmissionVolumeInfo's copy constructor 0x001F3550, installs the same table and copies the dword at +8; assignment 0x003A681E copies only byte +4 and dword +8. Deleting destructor 0x003A6833 passes stride 0x0C at 0x003A684B, proving sizeof 0x0C; the registered EmissionVolumeInfo base has stride 0x08 at 0x001F358C.
// VA 0x00C1BB60 has four slots: deleting destructor 0x003A6833, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F354A ("EmissionVolumeInfo", VA 0x00BE1558), and inherited DoXfer(Xfer &) 0x0047A69C. VA 0x00C1BB70 is the next table, installed for the sphere subobject at +8 by SphereEmissionVolumeModuleTemplate constructor 0x003A687E. Complete destructor 0x0049B47C restores Snapshot's VA 0x00BBB554: the derived table store is dead during empty base teardown, not an alternative sphere table.
// Retail SphereEmissionVolumeModule construction 0x003AC087 places this base at +0x1C; getPosition 0x0055D48C tests the inherited byte at +0x20 and uses float +0x24 as the generated position's radius. Parser 0x0055D3C7 uses VA 0x00C6BDB4, whose Radius field at template +0x10 identifies this float at +8. Copy callers 0x003A68AF, 0x003AC087 and 0x003AF738 call 0x003A67FD out of line. The ledger names the namespace and special members; the three unchanged Snapshot slots are inherited from the registered parent.
#pragma once

#ifndef __BFME2_SPHEREEMISSIONVOLUMEINFO_H_
#define __BFME2_SPHEREEMISSIONVOLUMEINFO_H_

#include "EmissionVolumeInfo.h"

namespace FXParticleSystem
{

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    SphereEmissionVolumeInfo();
    SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that);
    SphereEmissionVolumeInfo &operator=(const SphereEmissionVolumeInfo &that);
    virtual ~SphereEmissionVolumeInfo();

    float m_radius;
};

}

using FXParticleSystem::SphereEmissionVolumeInfo;

#endif
