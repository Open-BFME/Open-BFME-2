/* Target facts (RVAs unless marked VA): FXParticleSystem::LifeEventModuleInfo constructors 0x003A9900 and 0x00564001 install VA 0x00C1C188 at +0. Its four slots are the vector deleting destructor 0x003A9951, empty post-load callback 0x000B3FD0, GetSnapshotName 0x003A6139 (returns "LifeEventModuleInfo" at VA 0x00C1B984), and xfer 0x00563E72. The vector destructor passes stride 0x18, proving sizeof 0x18.
The destructor 0x003A9F8A releases the narrow string at +4 through 0x00036410, then restores Snapshot's VA 0x00BBB554; this is the base table, not a second LifeEventModuleInfo table. Constructor unwind 0x00799D2F calls Snapshot::~Snapshot at 0x0049B47C, while 0x00799D37 destroys AsciiString at +4 through 0x0048BA39. Snapshot occupies +0..+3; AsciiString occupies +4..+7; setRange 0x002341E7 and xferRandomVariable 0x00306183 receive the GameClientRandomVariable at +8..+0x13. getEventFX 0x0056410F resolves the +4 string through findFXList 0x001E281A and caches its const FXList pointer at +0x14.
Copy construction 0x003A9900 and assignment 0x003A7A51 call the narrow-string operations 0x000365F0 and 0x000366F0, copy three dwords at +8 and the pointer at +0x14. The ledger names the default/copy constructors, assignment, virtual destructor, non-const GetSnapshotName, protected xfer(Xfer *) and getEventFX; these bodies remain out of line. Field names identify offsets rather than original source spellings. */
#pragma once

#ifndef __BFME2_LIFEEVENTMODULEINFO_H_
#define __BFME2_LIFEEVENTMODULEINFO_H_

#if !defined(__SNAPSHOT_H_)
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "GameClientRandomVariable.h"

class FXList;

namespace FXParticleSystem
{

class LifeEventModuleInfo : public Snapshot
{
public:
    LifeEventModuleInfo();
    LifeEventModuleInfo(const LifeEventModuleInfo &that);
    LifeEventModuleInfo &operator=(const LifeEventModuleInfo &that);
    virtual ~LifeEventModuleInfo();

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
    virtual void crc(Xfer *xfer);
#endif

    const FXList *getEventFX();

    AsciiString m_04;
    GameClientRandomVariable m_08;
    const FXList *m_14;

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) && defined(BFME_SNAPSHOT_REFERENCE_XFER)
public:
    // Retail export ?DoXfer@LifeEventModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z (0x00563E72).
    virtual void DoXfer(Xfer &xfer);
#else
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void DoXfer(Xfer *xfer);
#else
    virtual void xfer(Xfer *xfer);
#endif
#endif
};

}

using FXParticleSystem::LifeEventModuleInfo;

#endif
