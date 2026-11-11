// SlaveWatcherBehavior: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SLAVEWATCHERBEHAVIOR_H
#define CANONICAL_SLAVEWATCHERBEHAVIOR_H

class Module;
class ModuleData;
class Thing;

class SlaveWatcherBehavior
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void rva00484869(int objectID);
};

#endif // CANONICAL_SLAVEWATCHERBEHAVIOR_H
