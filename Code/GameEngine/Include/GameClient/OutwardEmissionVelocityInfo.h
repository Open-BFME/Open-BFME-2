/* Target facts (RVAs): FXParticleSystem::OutwardEmissionVelocityInfo's copy constructor is the ICF twin
0x003A7501 of CylindricalEmissionVelocityInfo's, its deleting destructor the twin 0x003A7532 (stride 0x1C)
and its assignment 0x003A765F copies two three-dword blocks at +4/+0x10, so the layout matches the
cylindrical info. OutwardEmissionVelocityModuleTemplate's +8 table is the folded 0x0081BC80 it shares with
the cylindrical template: the -8 thunk, then the inherited EmissionVelocityInfo slots.
Member names are neutral ordinals. */
#pragma once

#ifndef __BFME2_OUTWARDEMISSIONVELOCITYINFO_H_
#define __BFME2_OUTWARDEMISSIONVELOCITYINFO_H_

#include "EmissionVelocityInfo.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class OutwardEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    OutwardEmissionVelocityInfo();
    OutwardEmissionVelocityInfo(const OutwardEmissionVelocityInfo &that);
    OutwardEmissionVelocityInfo &operator=(const OutwardEmissionVelocityInfo &that);
    virtual ~OutwardEmissionVelocityInfo();

    ::GameClientRandomVariable m_04;
    ::GameClientRandomVariable m_10;
};

}

using FXParticleSystem::OutwardEmissionVelocityInfo;

#endif
