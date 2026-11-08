/* Target facts (RVAs): FXParticleSystem::DefaultAlphaModuleInfo's slots are LoadPostProcess 0x000B3FD0,
non-const GetSnapshotName 0x003A611B and DoXfer(Xfer &) 0x0055B266 (retail export) after the deleting
destructor 0x003A61B3. Its destructor 0x0049B47C only restores Snapshot's table. The copy constructor
0x003A616F block-copies 0x80 bytes after the Snapshot vptr; DefaultModuleTemplate<1>'s deleting
destructor 0x003A628B uses stride 0x8C with this class at +8, so sizeof is 0x84.
Field storage is named by layout, not by an original source spelling. */
#pragma once

#ifndef __BFME2_DEFAULTALPHAMODULEINFO_H_
#define __BFME2_DEFAULTALPHAMODULEINFO_H_

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

class DefaultAlphaModuleInfo : public Snapshot
{
public:
    DefaultAlphaModuleInfo();
    DefaultAlphaModuleInfo(const DefaultAlphaModuleInfo &that);
    DefaultAlphaModuleInfo &operator=(const DefaultAlphaModuleInfo &that);
    virtual ~DefaultAlphaModuleInfo();

    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

private:
    unsigned char m_keys[0x80];   // +0x04: eight keyframes
};

}

#endif
