/* Target facts (RVAs unless marked VA): FXParticleSystem::LightningEmissionInfo constructors 0x003A6AF5 and 0x0055D9A5 install VA 0x00C1BBA0 at +0. Copy construction first installs EmissionVolumeInfo's VA 0x00BE1548 and copies its byte at +4; that base's deleting destructor 0x001F3574 uses stride 8. Lightning's deleting destructor 0x003A6C0B passes stride 0x8C at 0x003A6C23, proving sizeof 0x8C. The shared destructor 0x0049B47C restores Snapshot's VA 0x00BBB554; this is base teardown, not Lightning's table.
Lightning's four slots are deleting destructor 0x003A6C0B, empty post-load 0x000B3FD0, inherited non-const GetSnapshotName 0x001F354A ("EmissionVolumeInfo", VA 0x00BE1558), and inherited DoXfer(Xfer &) 0x0047A69C. Slots 1-3 equal the registered EmissionVolumeInfo table; Lightning introduces no virtual slot. The adjacent template table starts at VA 0x00C1BBB0. Constructors and assignment 0x003A6B8F copy coordinate triples at +8/+0x14 and nine 12-byte values at +0x20/+0x2C/+0x38/+0x44/+0x50/+0x5C/+0x68/+0x74/+0x80; default construction passes each value to GameClientRandomVariable::setRange at 0x002341E7, whose enum and float stores prove their types.
Template construction 0x003A6C59 calls the default constructor at 0x003A6C88; template copy construction 0x003A6CB0 calls the copy constructor at 0x003A6CD0. These constructors, assignment 0x003A6B8F and virtual destructor 0x0049B47C have ledger rows and remain out of line. Field names identify offsets, not original source spellings. */
#pragma once

#ifndef __BFME2_LIGHTNINGEMISSIONINFO_H_
#define __BFME2_LIGHTNINGEMISSIONINFO_H_

#include "EmissionVolumeInfo.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
    LightningEmissionInfo();
    LightningEmissionInfo(const LightningEmissionInfo &that);
    LightningEmissionInfo &operator=(const LightningEmissionInfo &that);
    virtual ~LightningEmissionInfo();

    Coord3D m_08;
    Coord3D m_14;
    GameClientRandomVariable m_20;
    GameClientRandomVariable m_2C;
    GameClientRandomVariable m_38;
    GameClientRandomVariable m_44;
    GameClientRandomVariable m_50;
    GameClientRandomVariable m_5C;
    GameClientRandomVariable m_68;
    GameClientRandomVariable m_74;
    GameClientRandomVariable m_80;
};

}

using FXParticleSystem::LightningEmissionInfo;

#endif
