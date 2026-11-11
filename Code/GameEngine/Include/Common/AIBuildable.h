// AIBuildable: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AIBUILDABLE_H
#define CANONICAL_AIBUILDABLE_H

class Player;

class AIBuildable
{
public:
	void addNeed(int a);
	bool doBuild(Player *);
	int doCanMake(Player *);
};

#endif // CANONICAL_AIBUILDABLE_H
