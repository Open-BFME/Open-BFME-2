// CarryoverUnit ABI view, not a recovered BFME 2 header.
// Native copy 001EB79E and ctor 0037DF2C install table VA 00BDF158;
// dtor 0037DEE4 restores Snapshot's table after destroying +94 and +4.
// The allocated/copied extent is AC. Field offsets +4/+8/+C/+10/+90/+94
// are established by those bodies. The 0x80-byte block and 0x18-byte tail
// below remain opaque storage; their original types are not asserted.
// Existing real-named methods and native table slots supply declarations.
// Assignment 001EB20E receives a live CarryoverUnit temporary through native
// fill 001EB84E, and derived base-assignment independently corroborates it.
#pragma once

#ifndef BFME2_CARRYOVERUNIT_H
#define BFME2_CARRYOVERUNIT_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// An already-parsed legacy crc surface adds a fifth slot to the named view.
// Refuse that context; it needs separate Snapshot-interface reconciliation.
#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error CarryoverUnit requires the native Snapshot name-slot surface first
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_CARRYOVER_RESTORE_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#ifdef BFME_CARRYOVER_RESTORE_NAME_SLOT
#undef BFME_CARRYOVER_RESTORE_NAME_SLOT
#undef BFME_SNAPSHOT_NAME_SLOT
#endif

class Object;
class Player;
class Xfer;

class CarryoverUnit : public Snapshot
{
public:
    CarryoverUnit();
    CarryoverUnit(const CarryoverUnit &);
    virtual ~CarryoverUnit();
    CarryoverUnit &operator=(const CarryoverUnit &);

    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    Object *createSingleObject(Player *);

protected:
    // The existing native owner at 0037DE79 has protected virtual access.
    virtual void xfer(Xfer *);

public:
    AsciiString m_name;                // +04
    float m_f08;                       // +08
    int m_c0C;                         // +0C
    unsigned char m_h10[0x80];         // +10, representation only
    int m_90;                          // +90
    unsigned char m_tail94[0x18];      // +94, representation only
};

#endif
