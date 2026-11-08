/* Target facts: FXParticleSystem::RenderObjectUpdateModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
RenderObjectUpdateModuleInfo table at +8 (the -8 deleting-destructor thunk, then RenderObjectUpdateModuleInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the RenderObjectUpdateModuleInfo copy out of line. */
#pragma once

#ifndef __BFME2_RENDEROBJECTUPDATEMODULETEMPLATE_H_
#define __BFME2_RENDEROBJECTUPDATEMODULETEMPLATE_H_

#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#include "RenderObjectUpdateModuleInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class RenderObjectUpdateModuleTemplate : public CategoryModuleTemplate<2>,
    public RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleTemplate();
    RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &that);
    virtual ~RenderObjectUpdateModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
