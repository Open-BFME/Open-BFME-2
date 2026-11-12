// ScoreKeeper: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SCOREKEEPER_H
#define CANONICAL_SCOREKEEPER_H

class Object;
class Player;

class ScoreKeeper
{
public:
	void addObjectBuilt(Object *obj, int a2);
	void addObjectDestroyed(const Object *victim);
	void addObjectLost(const Object *victim);
	void addObjectsDestroyed(unsigned int key, Player *other, unsigned int amount);
	void addObjectsLost(unsigned int key, int amount);
	void reset(int);
	void updateFrame(int frame);
};

#endif // CANONICAL_SCOREKEEPER_H
