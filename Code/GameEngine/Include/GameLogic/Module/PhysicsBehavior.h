// PhysicsBehavior: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_PHYSICSBEHAVIOR_H
#define CANONICAL_PHYSICSBEHAVIOR_H

class Module;
class ModuleData;
class Object;
class Thing;

class PhysicsBehavior
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void rva00390629(bool value);
	void rva003906BF();
	void setIgnoreCollisionsWith(const Object *);
};

#endif // CANONICAL_PHYSICSBEHAVIOR_H
