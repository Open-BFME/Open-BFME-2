// PhysicsBehavior: canonical declarations for the members units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
// Retail's instance factory 0x0024E73C news 0x68 bytes and runs the rowed constructor 0x003907A6.
#ifndef CANONICAL_PHYSICSBEHAVIOR_H
#define CANONICAL_PHYSICSBEHAVIOR_H

class Module;
class ModuleData;
class Object;
class Thing;

class PhysicsBehavior
{
public:
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	void rva00390629(bool value);
	void rva003906BF();
	void setIgnoreCollisionsWith(const Object *);
private:
	unsigned char m_storage00[0x68];
};

#endif // CANONICAL_PHYSICSBEHAVIOR_H
