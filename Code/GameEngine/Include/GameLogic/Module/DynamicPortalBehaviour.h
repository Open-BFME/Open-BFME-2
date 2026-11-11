// DynamicPortalBehaviour: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_DYNAMICPORTALBEHAVIOUR_H
#define CANONICAL_DYNAMICPORTALBEHAVIOUR_H

struct Coord3D;
class Module;
class ModuleData;
class Object;
class Thing;

class DynamicPortalBehaviour
{
public:
	bool IsEndPortalAboveWall(Coord3D *pos);
	void createWaypoints();
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static Module *rva004608E0(Object *obj);
	void rva0046094C();
};

#endif // CANONICAL_DYNAMICPORTALBEHAVIOUR_H
