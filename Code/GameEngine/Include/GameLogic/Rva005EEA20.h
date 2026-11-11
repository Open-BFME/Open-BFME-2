// Rva005EEA20: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005EEA20_H
#define CANONICAL_RVA005EEA20_H

class Object;
class Player;
class Rva005EE9CE;

class Rva005EEA20
{
public:
	Object *findUnitInCombat(Player *player, bool skipStealth, bool skipVictimCheck);
	void getStatsInCombatRange(Rva005EE9CE *stats, Object *unit, float range);
};

#endif // CANONICAL_RVA005EEA20_H
