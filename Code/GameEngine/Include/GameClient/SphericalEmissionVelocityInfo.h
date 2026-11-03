/* Target facts (RVAs unless marked VA): FXParticleSystem::SphericalEmissionVelocityInfo default constructor 0x003A721F and copy constructor 0x003A7270 install VA 0x00C1BC30 at +0. Copy construction calls EmissionVelocityInfo's copy constructor 0x001F35CE at 0x003A727A before installing the derived table. The parent constructors 0x001F35C5/0x001F35CE install VA 0x00BE1584; its deleting destructor 0x003A7ABD passes stride 4 at 0x003A7AD5. Spherical's vector deleting destructor 0x003A72AC passes stride 0x10 at 0x003A72C4, proving sizeof 0x10 and the single four-byte base at +0.
The four slots at VA 0x00C1BC30 are vector deleting destructor 0x003A72AC, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F35BF ("EmissionVelocityInfo", VA 0x00BE156C), and inherited DoXfer(Xfer &) 0x0047A69C. Only the destructor differs from the parent table. Complete destructor 0x0049B47C restores Snapshot's VA 0x00BBB554, also installed by Snapshot constructors 0x000053A6/0x00001745. This is shared base teardown, not another Spherical table or an identity with the four-byte parent.
Default construction zeroes the 12-byte GameClientRandomVariable at +4 and calls setRange 0x002341E7 at 0x003A725C with zero bounds and distribution 1. The setter writes floats at member +4/+8 and the distribution at member +0; GameClientRandomVariable constructor 0x000B4979 and assignment 0x0000353A confirm the footprint. Spherical copy construction 0x003A7270 and assignment 0x003A7296 copy the three-dword block at +4. The ledger proves the namespace, class key, default/copy constructors, assignment and virtual destructor; these bodies remain declared out of line. The member name is a neutral placeholder. */
#pragma once

#ifndef __BFME2_SPHERICALEMISSIONVELOCITYINFO_H_
#define __BFME2_SPHERICALEMISSIONVELOCITYINFO_H_

#include "EmissionVelocityInfo.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    SphericalEmissionVelocityInfo();
    SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &that);
    SphericalEmissionVelocityInfo &operator=(const SphericalEmissionVelocityInfo &that);
    virtual ~SphericalEmissionVelocityInfo();

    ::GameClientRandomVariable m_04;
};

}

using FXParticleSystem::SphericalEmissionVelocityInfo;

#endif
