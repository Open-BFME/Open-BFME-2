// BfmeThingRV: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGRV_H
#define CANONICAL_BFMETHINGRV_H

class BfmeMemberRV;

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

#endif // CANONICAL_BFMETHINGRV_H
