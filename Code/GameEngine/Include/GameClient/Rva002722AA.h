// Rva002722AA: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002722AA_H
#define CANONICAL_RVA002722AA_H

class Rva002722AA
{
public:
	void *get() const;
};

#endif // CANONICAL_RVA002722AA_H
