// ResourceGatheringManager: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RESOURCEGATHERINGMANAGER_H
#define CANONICAL_RESOURCEGATHERINGMANAGER_H

struct Coord3D;
class Object;

class ResourceGatheringManager
{
public:
	Object *findBestSupplyCenter(Object *queryObject);
	Object *findBestSupplyWarehouse(Object *queryObject);
	bool rva004F5A67(Object *obj, Coord3D *pos);
	void rva004F5C44(Object *obj);
};

#endif // CANONICAL_RESOURCEGATHERINGMANAGER_H
