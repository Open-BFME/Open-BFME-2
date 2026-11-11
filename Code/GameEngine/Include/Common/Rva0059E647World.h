// Rva0059E647World: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0059E647WORLD_H
#define CANONICAL_RVA0059E647WORLD_H

struct Rva0059E647Arg;
struct Rva0059E647Entry;

struct Rva0059E647World
{
	void Apply(Rva0059E647Entry *, void *, Rva0059E647Arg *);
	void rva002B77AD();
};

#endif // CANONICAL_RVA0059E647WORLD_H
