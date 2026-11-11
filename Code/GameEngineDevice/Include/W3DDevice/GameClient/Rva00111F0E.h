// Rva00111F0E: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00111F0E_H
#define CANONICAL_RVA00111F0E_H

class RvaRef;

class Rva00111F0E
{
public:
	void rva00111F0E();
	void rva00111F6F(RvaRef *, int, int, int);
	int rva00111FBC(unsigned char *culled);
};

#endif // CANONICAL_RVA00111F0E_H
