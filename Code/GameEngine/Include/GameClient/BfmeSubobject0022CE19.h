// Target facts (addresses are retail RVAs unless marked VA):
// The member's constructors 0022CE19/002DD173 store VA 00BE7560 at +0.
// Destructor 002DD1E9 restores that table at 002DD1FA, then Snapshot's
// VA 00BBB554 at 002DD272 after member cleanup. This is base teardown,
// not a competing table for the member or a vptr of the outer record.
// VA 00BE7560 has four slots: 0022CEF7 (deleting destructor calling
// 002DD1E9), 000B3FD0 (RET), 0022CEF1 (returns "SaveGameInfo" at
// VA 00BE7570), and 002DDEC0 (rowed xfer). The following bytes are the
// name string. VA 00BBB554 has destructor 00001750 and three purecalls.
// BfmeSubobject0022CE19 retains its ledger identity and opaque member
// storage; its registered parent is Snapshot. Not registered yet.
#pragma once
#ifndef __BFME2_BFMESUBOBJECT0022CE19_H_
#define __BFME2_BFMESUBOBJECT0022CE19_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

struct BfmeSubobject0022CE19 : public Snapshot
{
    BfmeSubobject0022CE19();
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
    BfmeSubobject0022CE19 &operator=(const BfmeSubobject0022CE19 &);
    virtual ~BfmeSubobject0022CE19();
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
    virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif

    unsigned char m_opaque[0xDE4];
};

#endif
