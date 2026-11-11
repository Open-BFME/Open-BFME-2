// Rva0087DC00: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0087DC00_H
#define CANONICAL_RVA0087DC00_H

struct Rva0087DC00Vec;

class Rva0087DC00
{
public:
	void get(Rva0087DC00Vec *out);
};

#endif // CANONICAL_RVA0087DC00_H
