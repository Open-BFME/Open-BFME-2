/* Target facts (RVAs): FXParticleSystem::DefaultColorModuleInfo's slots are LoadPostProcess 0x000B3FD0,
non-const GetSnapshotName 0x003A6121 and DoXfer(Xfer &) 0x0055B8CD (retail export) after the deleting
destructor. Its destructor 0x0049B47C only restores Snapshot's table. DefaultModuleTemplate<0>'s deleting
destructor 0x003A63EE uses stride 0x98 with this class at +8, so sizeof is 0x90.
Field storage is named by layout, not by an original source spelling. */
#pragma once

#ifndef __BFME2_DEFAULTCOLORMODULEINFO_H_
#define __BFME2_DEFAULTCOLORMODULEINFO_H_

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

class DefaultColorModuleInfo : public Snapshot
{
public:
    DefaultColorModuleInfo();
    DefaultColorModuleInfo(const DefaultColorModuleInfo &that);
    DefaultColorModuleInfo &operator=(const DefaultColorModuleInfo &that);
    virtual ~DefaultColorModuleInfo();

    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

private:
    unsigned char m_body[0x8C];   // +0x04
};

}

#endif
