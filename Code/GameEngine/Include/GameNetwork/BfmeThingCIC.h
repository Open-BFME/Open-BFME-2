// BfmeThingCIC: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGCIC_H
#define CANONICAL_BFMETHINGCIC_H

class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *key, void *value);
};

#endif // CANONICAL_BFMETHINGCIC_H
