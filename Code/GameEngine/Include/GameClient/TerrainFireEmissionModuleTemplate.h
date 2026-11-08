/* Target facts: FXParticleSystem::TerrainFireEmissionModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
TerrainFireEmissionInfo table at +8 (the -8 deleting-destructor thunk, then TerrainFireEmissionInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the TerrainFireEmissionInfo copy out of line. */
#pragma once

#ifndef __BFME2_TERRAINFIREEMISSIONMODULETEMPLATE_H_
#define __BFME2_TERRAINFIREEMISSIONMODULETEMPLATE_H_

#include "TerrainFireEmissionInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class TerrainFireEmissionModuleTemplate : public CategoryModuleTemplate<5>,
    public TerrainFireEmissionInfo
{
public:
    TerrainFireEmissionModuleTemplate();
    TerrainFireEmissionModuleTemplate(const TerrainFireEmissionModuleTemplate &that);
    virtual ~TerrainFireEmissionModuleTemplate();

    FX_MODULE_TEMPLATE_SLOTS;
};

}

#endif
