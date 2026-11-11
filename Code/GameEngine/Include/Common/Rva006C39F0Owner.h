// Rva006C39F0Owner: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA006C39F0OWNER_H
#define CANONICAL_RVA006C39F0OWNER_H

class Rva006C39F0Owner
{
public:
	void *rva006C3940Alloc(unsigned int size);
	bool rva006C39F0(unsigned int block, unsigned int externalTotal, unsigned int a, void *b);
};

#endif // CANONICAL_RVA006C39F0OWNER_H
