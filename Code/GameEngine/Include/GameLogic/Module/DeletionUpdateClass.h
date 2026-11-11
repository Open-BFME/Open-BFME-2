// DeletionUpdate: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_DELETIONUPDATE_H
#define CANONICAL_DELETIONUPDATE_H

class Module;
class ModuleData;
class Thing;

class DeletionUpdate
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void setLifetimeRange(unsigned int a, unsigned int b);
};

#endif // CANONICAL_DELETIONUPDATE_H
