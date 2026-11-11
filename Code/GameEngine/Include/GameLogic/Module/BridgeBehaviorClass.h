// BridgeBehavior: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BRIDGEBEHAVIOR_H
#define CANONICAL_BRIDGEBEHAVIOR_H

class BridgeBehaviorInterface;
class Module;
class ModuleData;
class Object;
class Thing;

class BridgeBehavior
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

#endif // CANONICAL_BRIDGEBEHAVIOR_H
