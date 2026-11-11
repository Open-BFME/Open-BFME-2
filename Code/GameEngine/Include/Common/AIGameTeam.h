// AIGameTeam: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AIGAMETEAM_H
#define CANONICAL_AIGAMETEAM_H

class ModuleData;

class AIGameTeam
{
public:
	void addPlayer(const ModuleData *);
	void *getMasterPlayer();
	void *getTargetByIndexForPlayer(int unused, int key);
	void rva004E94FB();
	void rva004E951C(void *);
	void update();
};

#endif // CANONICAL_AIGAMETEAM_H
