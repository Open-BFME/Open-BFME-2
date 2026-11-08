/* Target facts: FXParticleSystem::OutwardEmissionVelocityModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
OutwardEmissionVelocityInfo table at +8 (the -8 deleting-destructor thunk, then OutwardEmissionVelocityInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the OutwardEmissionVelocityInfo copy out of line. */
#pragma once

#ifndef __BFME2_OUTWARDEMISSIONVELOCITYMODULETEMPLATE_H_
#define __BFME2_OUTWARDEMISSIONVELOCITYMODULETEMPLATE_H_

#include "OutwardEmissionVelocityInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class OutwardEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public OutwardEmissionVelocityInfo
{
public:
    OutwardEmissionVelocityModuleTemplate();
    OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &that);
    virtual ~OutwardEmissionVelocityModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
