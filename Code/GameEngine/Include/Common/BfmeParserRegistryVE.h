// BfmeParserRegistryVE: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEPARSERREGISTRYVE_H
#define CANONICAL_BFMEPARSERREGISTRYVE_H

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

#endif // CANONICAL_BFMEPARSERREGISTRYVE_H
