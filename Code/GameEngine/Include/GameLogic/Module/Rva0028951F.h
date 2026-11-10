// Rva0028951F: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0028951F_H
#define CANONICAL_RVA0028951F_H

class Overridable;

class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);
	const Overridable *rva002897A8(void *list, int level);
};

#endif // CANONICAL_RVA0028951F_H
