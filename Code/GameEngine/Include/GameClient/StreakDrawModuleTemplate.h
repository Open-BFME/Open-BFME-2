/* Target facts: FXParticleSystem::StreakDrawModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
StreakDrawModuleInfo table at +8 (the -8 deleting-destructor thunk, then StreakDrawModuleInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the StreakDrawModuleInfo copy out of line. */
#pragma once

#ifndef __BFME2_STREAKDRAWMODULETEMPLATE_H_
#define __BFME2_STREAKDRAWMODULETEMPLATE_H_

#include "StreakDrawModuleInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class StreakDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public StreakDrawModuleInfo
{
public:
    StreakDrawModuleTemplate();
    StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that);
    virtual ~StreakDrawModuleTemplate();

    FX_MODULE_TEMPLATE_SLOTS;
};

}

#endif
