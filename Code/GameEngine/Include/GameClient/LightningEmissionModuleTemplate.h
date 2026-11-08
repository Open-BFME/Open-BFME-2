/* Target facts (RVAs): FXParticleSystem::LightningEmissionModuleTemplate constructors 0x003A6C59 and
0x003A6CB0 install VA 0x00C1BBB0 at +0, the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and
VA 0x00C1BBC0 at +8. Table 0x0081BBB0: the 0x94-stride vector deleting destructor 0x003A6D11, two pure
calls and writeINI 0x0055E39E. Table 0x0081BBC0: the -8 thunk 0x003A9635, then the Snapshot slots
LightningEmissionInfo inherits from EmissionVolumeInfo (0x000B3FD0, 0x001F354A, 0x0047A69C). */
#pragma once

#ifndef __BFME2_LIGHTNINGEMISSIONMODULETEMPLATE_H_
#define __BFME2_LIGHTNINGEMISSIONMODULETEMPLATE_H_

#include "LightningEmissionInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class LightningEmissionModuleTemplate : public CategoryModuleTemplate<5>,
    public LightningEmissionInfo
{
public:
    LightningEmissionModuleTemplate();
    LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that);
    virtual ~LightningEmissionModuleTemplate();

    FX_MODULE_TEMPLATE_SLOTS;
};

}

#endif
