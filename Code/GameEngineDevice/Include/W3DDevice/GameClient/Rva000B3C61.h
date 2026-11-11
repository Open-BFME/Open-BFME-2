// Rva000B3C61: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA000B3C61_H
#define CANONICAL_RVA000B3C61_H

class RefCounted;

class Rva000B3C61
{
public:
	void rva000B3BCF(int, RefCounted *, unsigned char, int, float, float, float, unsigned char, int);
	void rva000B3C61(int);
	void rva000B3CCF(int, int);
};

#endif // CANONICAL_RVA000B3C61_H
