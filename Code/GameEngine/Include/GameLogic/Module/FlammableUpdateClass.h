// FlammableUpdate: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_FLAMMABLEUPDATE_H
#define CANONICAL_FLAMMABLEUPDATE_H

class Module;
class ModuleData;
class Thing;

class FlammableUpdate
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void rva0048C8F9();
	void tryToIgnite();
};

#endif // CANONICAL_FLAMMABLEUPDATE_H
