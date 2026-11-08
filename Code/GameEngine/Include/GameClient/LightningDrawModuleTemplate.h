/* Target facts (RVAs): FXParticleSystem::LightningDrawModuleTemplate constructors 0x003A7E38 and
0x003A7E8F install VA 0x00C1BD90 at +0, the folded single-pure table VA 0x00C1C780 at +4 and
VA 0x00C1BDA0 at +8.
Table 0x0081BD90: the 0x38-stride vector deleting destructor 0x003A6F85 (calls ~LightningDrawModuleTemplate
0x003A6201), two pure calls and writeINI 0x00561DB3. CategoryModuleTemplate<6>'s own table holds its
deleting destructor 0x00001EAE and three pure calls, so it introduces the three slots and the lightning
template overrides only slot 3.
Table 0x0081BDA0: the -8 adjusting thunk 0x003A964D to that deleting destructor, then
LightningDrawModuleInfo's LoadPostProcess 0x000B3FD0, GetSnapshotName 0x003A6157 and DoXfer 0x005614D9.
Structural inference: slots 1 and 2 are the clone/getClass pair ConcreteModuleTemplate implements
(its 0x0081BE90 table); their spellings here identify storage, not original source. */
#pragma once

#ifndef __BFME2_LIGHTNINGDRAWMODULETEMPLATE_H_
#define __BFME2_LIGHTNINGDRAWMODULETEMPLATE_H_

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
#include "LightningDrawModuleInfo.h"

#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class LightningDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public LightningDrawModuleInfo
{
public:
    LightningDrawModuleTemplate();
    LightningDrawModuleTemplate(const LightningDrawModuleTemplate &that);
    virtual ~LightningDrawModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
