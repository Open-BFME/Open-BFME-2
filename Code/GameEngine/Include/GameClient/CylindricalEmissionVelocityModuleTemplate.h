/* Target facts: FXParticleSystem::CylindricalEmissionVelocityModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
CylindricalEmissionVelocityInfo table at +8 (the -8 deleting-destructor thunk, then CylindricalEmissionVelocityInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the CylindricalEmissionVelocityInfo copy out of line. */
#pragma once

#ifndef __BFME2_CYLINDRICALEMISSIONVELOCITYMODULETEMPLATE_H_
#define __BFME2_CYLINDRICALEMISSIONVELOCITYMODULETEMPLATE_H_

#include "CylindricalEmissionVelocityInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class CylindricalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public CylindricalEmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityModuleTemplate();
    CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &that);
    virtual ~CylindricalEmissionVelocityModuleTemplate();

    FX_MODULE_TEMPLATE_SLOTS;
};

}

#endif
