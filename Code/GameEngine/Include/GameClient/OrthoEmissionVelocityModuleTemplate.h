/* Target facts: FXParticleSystem::OrthoEmissionVelocityModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
OrthoEmissionVelocityInfo table at +8 (the -8 deleting-destructor thunk, then OrthoEmissionVelocityInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the OrthoEmissionVelocityInfo copy out of line. */
#pragma once

#ifndef __BFME2_ORTHOEMISSIONVELOCITYMODULETEMPLATE_H_
#define __BFME2_ORTHOEMISSIONVELOCITYMODULETEMPLATE_H_

#include "OrthoEmissionVelocityInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class OrthoEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public OrthoEmissionVelocityInfo
{
public:
    OrthoEmissionVelocityModuleTemplate();
    OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &that);
    virtual ~OrthoEmissionVelocityModuleTemplate();

    FX_MODULE_TEMPLATE_SLOTS;
};

}

#endif
