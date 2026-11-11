// MineshaftPortalBehaviour: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_MINESHAFTPORTALBEHAVIOUR_H
#define CANONICAL_MINESHAFTPORTALBEHAVIOUR_H

class Module;
class ModuleData;
class Thing;

class MineshaftPortalBehaviour
{
public:
	void addArrivingObject(void *obj);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
};

#endif // CANONICAL_MINESHAFTPORTALBEHAVIOUR_H
