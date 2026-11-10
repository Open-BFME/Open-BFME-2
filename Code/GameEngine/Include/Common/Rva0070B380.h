// Rva0070B380: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0070B380_H
#define CANONICAL_RVA0070B380_H

class EAStringC;

class Rva0070B380
{
public:
	void *lookup(const EAStringC &key);
};

#endif // CANONICAL_RVA0070B380_H
