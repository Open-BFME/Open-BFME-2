// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// ?addSupplyWarehouse@ResourceGatheringManager@@QAEXPAVObject@@@Z, retail 0x004F5C64, 32 bytes.
// BFME1 donor game/GameEngine/Source/Common/RTS/ResourceGatheringManagerLists.cpp
// addSupplyWarehouse: null check then m_supplyWarehouses.push_back(newWarehouse->getID()).
// Slice: vtbl +0x00, warehouses +0x04, centers +0x08, ObjectID at Object+0x74.
// Repair for target: list<int> to match rowed push_back 0x0005548F (H not I).
// _STLP_NO_EXCEPTIONS so _M_create_node inlines (donor note).
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int ObjectID;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

class ResourceGatheringManager
{
public:
	void addSupplyWarehouse(Object *newWarehouse);
	void rva004F5C44(Object *newCenter);
private:
	typedef _STL::list<ObjectID> objectIDList;
	void *m_slice_vtbl;
	objectIDList m_supplyWarehouses;
	objectIDList m_supplyCenters;
};

void ResourceGatheringManager::addSupplyWarehouse(Object *newWarehouse)
{
	if (newWarehouse == NULL)
		return;
	m_supplyWarehouses.push_back(newWarehouse->getID());
}

void ResourceGatheringManager::rva004F5C44(Object *newCenter)
{
	if (newCenter == NULL)
		return;
	m_supplyCenters.push_back(newCenter->getID());
}
