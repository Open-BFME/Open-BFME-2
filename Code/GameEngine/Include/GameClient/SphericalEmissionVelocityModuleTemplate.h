/* Target facts: FXParticleSystem::SphericalEmissionVelocityModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
SphericalEmissionVelocityInfo table at +8 (the -8 deleting-destructor thunk, then SphericalEmissionVelocityInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the SphericalEmissionVelocityInfo copy out of line. */
#pragma once

#ifndef __BFME2_SPHERICALEMISSIONVELOCITYMODULETEMPLATE_H_
#define __BFME2_SPHERICALEMISSIONVELOCITYMODULETEMPLATE_H_

#include "SphericalEmissionVelocityInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityModuleTemplate();
    SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that);
    virtual ~SphericalEmissionVelocityModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
