// BfmeThingUPB: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGUPB_H
#define CANONICAL_BFMETHINGUPB_H

class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *s, char *dst, void *n);
};

#endif // CANONICAL_BFMETHINGUPB_H
