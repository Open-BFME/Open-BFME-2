// LivingWorldRegionBonusRule: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDREGIONBONUSRULE_H
#define CANONICAL_LIVINGWORLDREGIONBONUSRULE_H

class INI;
class Rva00210390;
class Rva002E071E;

class LivingWorldRegionBonusRule
{
public:
	void CacheRegionIDs(Rva00210390 *a1);
	bool IsRuleSatisfied(Rva002E071E *player, float *value);
	static void ParseINI(INI *, void *, void *, const void *);
};

#endif // CANONICAL_LIVINGWORLDREGIONBONUSRULE_H
