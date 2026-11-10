// BfmeThingCIB: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGCIB_H
#define CANONICAL_BFMETHINGCIB_H

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *name, void *value);
};

#endif // CANONICAL_BFMETHINGCIB_H
