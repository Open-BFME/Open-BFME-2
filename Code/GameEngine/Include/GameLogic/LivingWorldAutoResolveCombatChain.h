// LivingWorldAutoResolveCombatChain: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDAUTORESOLVECOMBATCHAIN_H
#define CANONICAL_LIVINGWORLDAUTORESOLVECOMBATCHAIN_H

struct Out00418CC8;

class LivingWorldAutoResolveCombatChain
{
public:
	bool getHighestPriorityTarget(Out00418CC8 *out);
};

#endif // CANONICAL_LIVINGWORLDAUTORESOLVECOMBATCHAIN_H
