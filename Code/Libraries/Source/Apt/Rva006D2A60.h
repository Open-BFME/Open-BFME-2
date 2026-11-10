// Rva006D2A60: canonical declarations for the members 42 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA006D2A60_H
#define CANONICAL_RVA006D2A60_H

class Rva006D2A60
{
public:
	void *allocBlock(int);
	void freeBlock(void *, int);
};

#endif // CANONICAL_RVA006D2A60_H
