// BfmeHub982: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEHUB982_H
#define CANONICAL_BFMEHUB982_H

class BfmeHub982
{
public:
	void bfmeBegin982C();
	void bfmeEnd982C();
	void *__fastcall rva00111312(int count);
	void rva001116E2();
};

#endif // CANONICAL_BFMEHUB982_H
