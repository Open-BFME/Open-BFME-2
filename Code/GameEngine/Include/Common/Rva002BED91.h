// Rva002BED91: one retained TargetRef00217D4C pointer at +0. clear 0x002BED91 releases and nulls it,
// set 0x003F8396 stores its argument there; the ledger rows spell the class-key struct.
#ifndef CANONICAL_RVA002BED91_H
#define CANONICAL_RVA002BED91_H

struct TargetRef00217D4C;

struct Rva002BED91
{
	void clear();
	void set(TargetRef00217D4C *);

	TargetRef00217D4C *m_00;
};

#endif // CANONICAL_RVA002BED91_H
