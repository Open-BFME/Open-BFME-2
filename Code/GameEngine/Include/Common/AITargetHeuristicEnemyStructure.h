// AITargetHeuristicEnemyStructure: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AITARGETHEURISTICENEMYSTRUCTURE_H
#define CANONICAL_AITARGETHEURISTICENEMYSTRUCTURE_H

class AITarget;
class Player;
class Thing;

class AITargetHeuristicEnemyStructure
{
public:
	void findBestTarget(AITarget *, Player *, Player *);
	int isValidTarget(Thing *thing, void *owner);
};

#endif // CANONICAL_AITARGETHEURISTICENEMYSTRUCTURE_H
