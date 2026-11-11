// Rva0059E647Factory: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0059E647FACTORY_H
#define CANONICAL_RVA0059E647FACTORY_H

struct Rva0059E647Entry;

struct Rva0059E647Factory
{
	Rva0059E647Entry *Lookup(int *token);
};

#endif // CANONICAL_RVA0059E647FACTORY_H
