// BfmeCopyElementA: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMECOPYELEMENTA_H
#define CANONICAL_BFMECOPYELEMENTA_H

struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
};

#endif // CANONICAL_BFMECOPYELEMENTA_H
