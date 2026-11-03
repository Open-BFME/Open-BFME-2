// Target facts: retail RVAs unless marked VA. Constructors 0x002B644A and 0x004FC002 store VA 0x00BFE280 at +0; allocations at 0x002B9AC0 and 0x002B9D4D request 0x20 bytes.
// Destructor 0x004FC05C installs the same table, releases +0x18, frees the vector at +8 and restores Snapshot's VA 0x00BBB554 at 0x004FC09D. This is the base teardown table, not a second RegionAwardDispute table.
// VA 0x00BFE280 has four slots: deleting destructor 0x002B647C, loadPostProcess 0x004FBFFD, GetSnapshotName 0x002B6476 and xfer 0x004FBDF7. The following VA 0x00BFE290 is the "RegionAwardDispute" literal returned by slot 2.
// Both constructors write dwords at +4, +0x14 and +0x18, and a byte at +0x1C. The default values are -1, 0, -1 and 0. The argument constructor copies vector<unsigned int> at +8 through 0x002CFAB9; 0x004FBE7A reads begin/end at +8/+0xC with four-byte elements.
// 0x004FBDF7 transfers +4, +0x14, the bool at +0x1C and the vector at +8. 0x004FBF8E stores a beacon identifier at +0x18; 0x004FBDB0 passes it to the rowed NameKeyType lookup 0x002120A4. Field spellings remain neutral because these accesses do not establish source member names; the vector's 12-byte storage stays opaque.
// Nonvirtual declarations follow ledger rows: GetResolvableBy 0x004FBED6, rva004FBE7A 0x004FBE7A, rva004FBF8E 0x004FBF8E, rva004FBDB0(bool) 0x004FBDB0, rva004FC0AD(const Rva002E2903Player *) 0x004FC0AD and rva004FC0ED(const vector<int> &) 0x004FC0ED.

#pragma once

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace _STL
{
template<class T> class allocator;
template<class T, class A> class vector;
}
enum NameKeyType;
class Rva002E2903Player;

class RegionAwardDispute : public Snapshot
{
public:
	RegionAwardDispute();
	RegionAwardDispute(int, const _STL::vector<unsigned int, _STL::allocator<unsigned int> > &, int);
	virtual ~RegionAwardDispute();

	int GetResolvableBy();
	int rva004FBE7A();
	void rva004FBF8E();
	void rva004FBDB0(bool);
	void rva004FC0AD(const Rva002E2903Player *);
	void rva004FC0ED(const _STL::vector<int, _STL::allocator<int> > &);

protected:
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

public:
	int m_04;
	unsigned char m_08[0x0C];
	int m_14;
	NameKeyType m_18;
	bool m_1C;
};
