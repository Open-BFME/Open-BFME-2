/* Target facts (RVAs unless marked VA): FXParticleSystem::CylindricalEmissionVelocityInfo default constructor 0x003A7489 and copy constructor 0x003A7501 install VA 0x00C1BC90 at +0. The copy calls EmissionVelocityInfo's copy constructor 0x001F35CE at 0x003A750C before installing the derived table. The base constructors 0x001F35C5/0x001F35CE install VA 0x00BE1584; its deleting destructor 0x003A7ABD passes stride 4 at 0x003A7AD5. The derived deleting destructor 0x003A7532 passes stride 0x1C at 0x003A754A, proving sizeof 0x1C with the single four-byte base at +0.
The four slots at VA 0x00C1BC90 are vector deleting destructor 0x003A7532, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F35BF ("EmissionVelocityInfo", VA 0x00BE156C), and inherited DoXfer(Xfer &) 0x0047A69C. Only the destructor differs from the base table. Complete destructor 0x0049B47C restores Snapshot's VA 0x00BBB554, also installed by Snapshot constructors 0x000053A6/0x00001745. This is base teardown, not a second derived table or identity with the four-byte parent.
Default construction zeroes two 12-byte GameClientRandomVariable members at +4/+0x10 and calls setRange 0x002341E7 on them at 0x003A74D6/0x003A74EC with zero bounds and distribution 1. The setter stores floats at +4/+8 and distribution at +0; GameClientRandomVariable constructor 0x000B4979 and assignment 0x0000353A confirm its footprint. Copy construction 0x003A7501 and assignment 0x003A765F copy two separate three-dword blocks at +4/+0x10. The ledger proves the namespace, class key, default/copy constructors, assignment and virtual destructor; these bodies remain out of line. The module-template constructors call the default at 0x003A75AC and the copy at 0x003A75F4. Member names are neutral ordinals. */
#pragma once

#ifndef __BFME2_CYLINDRICALEMISSIONVELOCITYINFO_H_
#define __BFME2_CYLINDRICALEMISSIONVELOCITYINFO_H_

#include "EmissionVelocityInfo.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityInfo();
    CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that);
    CylindricalEmissionVelocityInfo &operator=(const CylindricalEmissionVelocityInfo &that);
    virtual ~CylindricalEmissionVelocityInfo();

    ::GameClientRandomVariable m_04;
    ::GameClientRandomVariable m_10;
};

}

using FXParticleSystem::CylindricalEmissionVelocityInfo;

#endif
