/* Target facts (RVAs): FXParticleSystem::StreakDrawModuleInfo's slots are LoadPostProcess 0x000B3FD0,
non-const GetSnapshotName 0x003A613F and DoXfer(Xfer &) at the shared Version1-only body 0x00306A9B after the
deleting destructor. Its destructor 0x0049B47C only restores Snapshot's table; the copy constructor 0x003A7AB2
stores only the table, and the template's deleting destructor 0x003A7B9F uses stride 0xC with this
class at +8, so the class holds no fields beyond Snapshot's vptr. */
#pragma once

#ifndef __BFME2_STREAKDRAWMODULEINFO_H_
#define __BFME2_STREAKDRAWMODULEINFO_H_

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
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class StreakDrawModuleInfo : public Snapshot
{
public:
    StreakDrawModuleInfo();
    StreakDrawModuleInfo(const StreakDrawModuleInfo &that);
    StreakDrawModuleInfo &operator=(const StreakDrawModuleInfo &that);
    virtual ~StreakDrawModuleInfo();

    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);
};

}

#endif
