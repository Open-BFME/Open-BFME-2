/* Target facts (RVAs unless marked VA): FXParticleSystem::LightningDrawModuleInfo constructors 0x003A7DCA and 0x0056142E install VA 0x00C1BD80 at +0. Its four slots are the shared vector deleting destructor 0x003A6E82 (stride 0x30, proving sizeof 0x30), empty post-load callback 0x000B3FD0, non-const GetSnapshotName 0x003A6157 (returns "LightningDrawModuleInfo" at VA 0x00C1B9F8), and DoXfer(Xfer &) 0x005614D9 (retail export).
The destructor 0x0049B47C only restores Snapshot's VA 0x00BBB554, whose slots 1-3 are pure calls; it is the shared empty base cleanup, not a second class table. Constructor unwind 0x00799BA7 calls that body on the original this. Snapshot occupies +0..+3; constructor 0x0056142E passes +4, +0x10 and +0x1C to GameClientRandomVariable::setRange 0x002341E7, then stores a float at +0x28 and a byte at +0x2C. xfer 0x005614D9 passes the same three 12-byte members to xferRandomVariable 0x00306183, then transfers +0x28 as float and +0x2C as bool.
Copy constructor 0x003A7DCA and assignment 0x003A7E04 copy three 12-byte aggregates at +4/+0x10/+0x1C, one dword at +0x28 and one byte at +0x2C. Template constructors 0x003A7E38 and 0x003A7E8F call the default and copy constructors out of line on +8; particle constructor 0x00561C34 calls the default constructor on +0x18 and starts its following array at +0x48. The ledger proves the namespace, class key and method declarations; field names identify storage rather than original source spellings. */
#pragma once

#ifndef __BFME2_LIGHTNINGDRAWMODULEINFO_H_
#define __BFME2_LIGHTNINGDRAWMODULEINFO_H_

#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class LightningDrawModuleInfo : public Snapshot
{
public:
    LightningDrawModuleInfo();
    LightningDrawModuleInfo(const LightningDrawModuleInfo &that);
    LightningDrawModuleInfo &operator=(const LightningDrawModuleInfo &that);
    virtual ~LightningDrawModuleInfo();

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

    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
    float m_28;
    bool m_2c;

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) && defined(BFME_SNAPSHOT_REFERENCE_XFER)
public:
    // Retail export ?DoXfer@LightningDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z (0x005614D9).
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

using FXParticleSystem::LightningDrawModuleInfo;

#endif
