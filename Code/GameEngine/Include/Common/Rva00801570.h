// Rva00801570: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00801570_H
#define CANONICAL_RVA00801570_H

class Rva00801570
{
public:
	void allocate(int);
	void clear();
};

#endif // CANONICAL_RVA00801570_H
