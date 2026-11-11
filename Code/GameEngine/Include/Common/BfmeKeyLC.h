// BfmeKeyLC: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEKEYLC_H
#define CANONICAL_BFMEKEYLC_H

struct BfmeNodeLC;

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

#endif // CANONICAL_BFMEKEYLC_H
