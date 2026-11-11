// Rva004FB0C7Registry: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA004FB0C7REGISTRY_H
#define CANONICAL_RVA004FB0C7REGISTRY_H

struct Rva004FAFF2;

class Rva004FB0C7Registry
{
public:
	bool rva004FB0C7(int key, Rva004FAFF2 *out);
};

#endif // CANONICAL_RVA004FB0C7REGISTRY_H
