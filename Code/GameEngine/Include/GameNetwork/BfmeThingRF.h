// BfmeThingRF: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGRF_H
#define CANONICAL_BFMETHINGRF_H

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *key, void *fallback);
};

#endif // CANONICAL_BFMETHINGRF_H
