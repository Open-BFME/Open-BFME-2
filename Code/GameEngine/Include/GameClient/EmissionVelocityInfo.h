/* Target facts (RVAs unless marked VA): FXParticleSystem::EmissionVelocityInfo constructors 0x001F35C5 and 0x001F35CE install VA 0x00BE1584 at +0 without writing any data fields. Its four slots are vector deleting destructor 0x003A7ABD, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x001F35BF ("EmissionVelocityInfo", VA 0x00BE156C), and DoXfer(Xfer &) 0x0047A69C. The deleting destructor passes element stride 4 at 0x003A7AD5, proving sizeof 4.
Destructor 0x0049B47C restores Snapshot's VA 0x00BBB554, whose slot 0 is 0x00001750 and slots 1-3 are purecall 0x0003B810. Snapshot constructors 0x000053A6 and 0x00001745 install that base table; the shared destructor is base teardown, not a second EmissionVelocityInfo layout. The sole storage is Snapshot's vptr at +0.
Derived default constructors 0x003A721F and 0x003A7489 inline base construction before installing their own tables. Copy constructor 0x001F35CE ignores its source and is called by 0x003A707A, 0x003A727A and 0x003A750C. Assignment 0x001FD28E only returns this. Both, the virtual destructor and the named callbacks remain out of line. The ledger proves the namespace, class key and callback signatures. */
#pragma once

#ifndef __BFME2_EMISSIONVELOCITYINFO_H_
#define __BFME2_EMISSIONVELOCITYINFO_H_

#ifndef __SNAPSHOT_H_
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class EmissionVelocityInfo : public ::Snapshot
{
public:
    EmissionVelocityInfo() {}
    EmissionVelocityInfo(const EmissionVelocityInfo &that);
    EmissionVelocityInfo &operator=(const EmissionVelocityInfo &that);
    virtual ~EmissionVelocityInfo();

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(::Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(::Xfer &xfer);
#else
    virtual void DoXfer(::Xfer *xfer);
#endif
#else
    virtual void xfer(::Xfer *xfer);
#endif
};

}

using FXParticleSystem::EmissionVelocityInfo;

#endif
