/* Target facts (RVAs unless marked VA): FXParticleSystem::TerrainFireEmissionInfo constructors 0x003A6D5F and 0x003A6E0E install VA 0x00C1BBD0 at +0. Copy construction calls EmissionVolumeInfo's copy constructor 0x001F3550 at 0x003A6E19; the default constructor clears the inherited byte at +4. The table has four slots: vector deleting destructor 0x003A6E82, inherited LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x001F354A (returns "EmissionVolumeInfo" at VA 0x00BE1558), and DoXfer(Xfer &) 0x0047A69C. The next table starts at VA 0x00C1BBE0.
The deleting destructor pushes stride 0x30 at 0x003A6E9A, proving sizeof 0x30. The complete destructor 0x0049B47C only restores Snapshot's VA 0x00BBB554: empty derived and EmissionVolumeInfo teardown leave the base store. EmissionVolumeInfo's own VA 0x00BE1548 has a deleting destructor with stride 8 at 0x001F358C, so the inherited Snapshot name does not identify the derived object as the base. LightningDrawModuleInfo shares the 0x30-byte deleting body but has a distinct VA 0x00C1BD80 and getter 0x003A6157.
Default construction passes +8, +0x14 and +0x20 to GameClientRandomVariable::setRange (0x002341E7), then stores 0.7f at +0x2C. Copy construction and assignment 0x003A6E4E copy three 12-byte aggregates at those offsets and one dword at +0x2C; assignment also copies the inherited byte at +4. The template constructor 0x003A6ECD and copy caller 0x003AF9A9 call the info constructors out of line. The ledger proves the namespace and the default/copy/assignment/virtual-destructor declarations; member names are neutral placeholders. */
#pragma once

#ifndef __BFME2_TERRAINFIREEMISSIONINFO_H_
#define __BFME2_TERRAINFIREEMISSIONINFO_H_

#include "EmissionVolumeInfo.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
    TerrainFireEmissionInfo();
    TerrainFireEmissionInfo(const TerrainFireEmissionInfo &that);
    TerrainFireEmissionInfo &operator=(const TerrainFireEmissionInfo &that);
    virtual ~TerrainFireEmissionInfo();

    GameClientRandomVariable m_08;
    GameClientRandomVariable m_14;
    GameClientRandomVariable m_20;
    float m_2C;
};

}

using FXParticleSystem::TerrainFireEmissionInfo;

#endif
