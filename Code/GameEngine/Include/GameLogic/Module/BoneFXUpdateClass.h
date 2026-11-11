// BoneFXUpdate: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BONEFXUPDATE_H
#define CANONICAL_BONEFXUPDATE_H

class Module;
class ModuleData;
class Thing;

class BoneFXUpdate
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void stopAllBoneFX();
};

#endif // CANONICAL_BONEFXUPDATE_H
