// SkirmishAI: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SKIRMISHAI_H
#define CANONICAL_SKIRMISHAI_H

class Object;
class Team;
class Xfer;

class SkirmishAI
{
public:
	void DoXfer(Xfer *xfer);
	void Register(Team *);
	void UnRegister(Team *team);
	bool isAPartialBrain();
	void onHordeCreated(Object *horde, Object *member);
	void onUnitCreated(Object *object, Object *other);
	void update();
};

#endif // CANONICAL_SKIRMISHAI_H
