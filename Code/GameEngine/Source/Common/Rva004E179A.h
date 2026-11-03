#pragma once

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
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

// Native C61B78 proves the four Snapshot slots for the record whose slot-2
// getter returns SpawnBuilding. Parser 4E17EB, destructor 4E179A and xfer
// 4E1398 establish three string words at +4/+8/+C and the bool at +10.
// The original C++ class name remains unresolved.
class Rva004E179A : public Snapshot
{
public:
 virtual ~Rva004E179A();
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
 AsciiString m_member08;
 AsciiString m_member0C;
 bool m_bool10;
};
