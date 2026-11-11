// Rva00800550Chain: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00800550CHAIN_H
#define CANONICAL_RVA00800550CHAIN_H

class Rva00800550Chain
{
public:
	void *append(int size);
	void clear();
	void *first();
	void popFront();
};

#endif // CANONICAL_RVA00800550CHAIN_H
