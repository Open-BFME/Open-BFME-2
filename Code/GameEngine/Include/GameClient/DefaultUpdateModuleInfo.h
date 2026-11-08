/* Target facts (RVAs): FXParticleSystem::DefaultUpdateModuleInfo's table VA 0x00C1BCE0 holds the 0x68-stride
deleting destructor 0x003A795A, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x003A6133 and
DoXfer(Xfer &) 0x0055F67C (retail export). Its destructor 0x0049B47C only restores Snapshot's table;
the stride gives sizeof 0x68. Field storage is named by layout, not by an original source spelling. */
#pragma once

#ifndef __BFME2_DEFAULTUPDATEMODULEINFO_H_
#define __BFME2_DEFAULTUPDATEMODULEINFO_H_

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

class DefaultUpdateModuleInfo : public Snapshot
{
public:
    DefaultUpdateModuleInfo();
    DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &that);
    DefaultUpdateModuleInfo &operator=(const DefaultUpdateModuleInfo &that);
    virtual ~DefaultUpdateModuleInfo();

    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

private:
    unsigned char m_body[0x64];   // +0x04
};

}

#endif
