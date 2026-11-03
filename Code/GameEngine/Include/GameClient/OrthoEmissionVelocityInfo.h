/* Target facts (RVAs unless marked VA): FXParticleSystem::OrthoEmissionVelocityInfo default constructor 0x003A6FD0 and copy constructor 0x003A706F install VA 0x00C1BC00 at +0. Copy construction calls EmissionVelocityInfo's copy constructor 0x001F35CE at 0x003A707A before installing the derived table. That base's constructors 0x001F35C5/0x001F35CE install VA 0x00BE1584; its deleting destructor 0x003A7ABD passes stride 4 at 0x003A7AD5. Ortho's deleting destructor 0x003A70D1 passes stride 0x28 at 0x003A70E9, proving sizeof 0x28 and the single four-byte base at +0.
The four slots at VA 0x00C1BC00 are vector deleting destructor 0x003A70D1, inherited LoadPostProcess 0x000B3FD0, inherited non-const GetSnapshotName 0x001F35BF ("EmissionVelocityInfo", VA 0x00BE156C), and inherited DoXfer(Xfer &) 0x0047A69C. Only the destructor differs from the base table. Complete destructor 0x0049B47C restores Snapshot's VA 0x00BBB554; Snapshot constructors 0x000053A6/0x00001745 install that table. This shared teardown does not identify a second Ortho layout or merge Ortho with its four-byte parent.
Default construction zeroes three 12-byte GameClientRandomVariable members at +4/+0x10/+0x1C and calls setRange 0x002341E7 on them at 0x003A702D/0x003A7043/0x003A7059 with zero bounds and distribution 1. That setter stores floats at +4/+8 and the distribution at +0; GameClientRandomVariable constructor 0x000B4979 and assignment 0x0000353A confirm the footprint. Ortho copy construction 0x003A706F and assignment 0x003A70A9 copy three separate three-dword blocks at those offsets. The ledger proves the namespace, class key, default/copy constructors, assignment and virtual destructor; these bodies remain declared out of line. Member names are neutral placeholders. */
#pragma once

#ifndef __BFME2_ORTHOEMISSIONVELOCITYINFO_H_
#define __BFME2_ORTHOEMISSIONVELOCITYINFO_H_

#include "EmissionVelocityInfo.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    OrthoEmissionVelocityInfo();
    OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &that);
    OrthoEmissionVelocityInfo &operator=(const OrthoEmissionVelocityInfo &that);
    virtual ~OrthoEmissionVelocityInfo();

    ::GameClientRandomVariable m_04;
    ::GameClientRandomVariable m_10;
    ::GameClientRandomVariable m_1C;
};

}

using FXParticleSystem::OrthoEmissionVelocityInfo;

#endif
