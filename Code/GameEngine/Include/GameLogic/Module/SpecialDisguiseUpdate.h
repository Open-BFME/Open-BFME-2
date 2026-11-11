// SpecialDisguiseUpdate: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SPECIALDISGUISEUPDATE_H
#define CANONICAL_SPECIALDISGUISEUPDATE_H

class Module;
class ModuleData;
class Thing;

class SpecialDisguiseUpdate
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void rva004B04B2(bool);
	void rva004B05F5(bool keep);
};

#endif // CANONICAL_SPECIALDISGUISEUPDATE_H
