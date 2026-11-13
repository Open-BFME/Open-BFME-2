// Rva003B0D7C (Money): canonical layout from retail. Player's constructor 0x002B0F3C stores this class's vtable
// 0x00BE1AA0 at Player+0x90 and zeroes +0x94 and +0x98 through the same base; inside the class's method 0x003B0D7C
// the instructions at 0x003B0DC0 and 0x003B0E13 read [this+8]; the next Player field starts at +0x9C. So it is a
// 12-byte Snapshot: the vptr and two dwords. Slots follow vtable 0x00BE1AA0: the deleting destructor (0x004A10FD,
// the shared Snapshot-restoring body), loadPostProcess (0x000B3FD0, the shared empty body), GetSnapshotName
// (0x001FD2AE, returns "Money") and xfer (0x003B0E38). Overrides are spelled the way the included Snapshot spells
// its slots (as Player.h does), and public, as retail's rows spell them.
#ifndef CANONICAL_RVA003B0D7C_H
#define CANONICAL_RVA003B0D7C_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0039B795;
class Rva0039B7AD;

class Rva003B0D7C : public Snapshot
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
	unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
	virtual ~Rva003B0D7C() {}
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
	unsigned int m_val04;
	int m_val08;
};

typedef char canonical_Rva003B0D7C_sizeof[sizeof(Rva003B0D7C) == 12 ? 1 : -1];

#endif // CANONICAL_RVA003B0D7C_H
