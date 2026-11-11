// AIDifficulty: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AIDIFFICULTY_H
#define CANONICAL_AIDIFFICULTY_H

class Rva002A9BF2;

class AIDifficulty
{
public:
	bool allowEconomyUpgrade(Rva002A9BF2 *p);
	bool allowOffensiveTactic(Rva002A9BF2 *p);
};

#endif // CANONICAL_AIDIFFICULTY_H
