// BfmeSubBIC: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMESUBBIC_H
#define CANONICAL_BFMESUBBIC_H

class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

#endif // CANONICAL_BFMESUBBIC_H
