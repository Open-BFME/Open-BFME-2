// BfmeThingEC: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGEC_H
#define CANONICAL_BFMETHINGEC_H

class BfmeThingEC
{
public:
	int bfmeTakeEC(int *size);
};

#endif // CANONICAL_BFMETHINGEC_H
