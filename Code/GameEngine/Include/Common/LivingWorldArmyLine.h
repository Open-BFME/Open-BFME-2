// LivingWorldArmyLine: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDARMYLINE_H
#define CANONICAL_LIVINGWORLDARMYLINE_H

class LivingWorldArmyLine
{
public:
	void allocatePoints(unsigned int count);
	void rva00538F6B(void *a, void *b, void *c, void *d);
	void rva00539141();
};

#endif // CANONICAL_LIVINGWORLDARMYLINE_H
