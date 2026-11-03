#pragma once

#include "ascii_string.h"
#if !defined(__SNAPSHOT_H_)
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

// Native C61DC4 is the four-slot Snapshot table for the record named by
// its slot-2 literal SetPlayerControlOfArmy. Constructor 4E1B61 and parser
// 4E1C7B establish AsciiString +4 and bool +8; retain the address-based
// class identity until an original declaration establishes its C++ name.
class Rva004E1B72 : public Snapshot
{
public:
 Rva004E1B72() : m_bool08(false) {}
 virtual ~Rva004E1B72();
 // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
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
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer &xfer);
#else
 virtual void DoXfer(Xfer *xfer);
#endif
#else
 virtual void xfer(Xfer *xfer);
#endif

 AsciiString m_member04;
 bool m_bool08;
};
