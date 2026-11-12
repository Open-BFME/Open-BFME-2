// Rva00894D90Accessor: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00894D90ACCESSOR_H
#define CANONICAL_RVA00894D90ACCESSOR_H

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(int *p);
	static unsigned int decrement(unsigned int *value);
};

#endif // CANONICAL_RVA00894D90ACCESSOR_H
