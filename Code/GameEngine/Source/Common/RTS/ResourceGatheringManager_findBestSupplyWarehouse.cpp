// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Source and names are carried from Open-BFME-1 revision
// 6583b3c1ff21db4a561285717028fdafc780b7db, where the same supply-manager
// helpers are named computeRelativeCost, findBestSupplyWarehouse and
// findBestSupplyCenter. That donor is semantic guidance, not BFME2 identity
// proof. BFME2 target evidence is the Ghidra boundary table and the four
// direct calls from 0x004F5C84/0x004F5DFB to 0x004F5A0D; the helper's calls to
// 0x0041BCA1, 0x0028BCB4, the dock interface's slot 0 and 0x001E435D; and the
// caller/helper offsets at Object+0x258 and Object+0x38. The BFME2 vector,
// manager-global and list layouts below follow target disassembly. The names
// and high-level purpose remain donor-carried until independent target
// evidence resolves them.

#include <float.h>
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectIDValue;
// GameLogic::findObjectByID (row 0x00049DC5) takes Zero Hour's ObjectID enum.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class ActionManager;
class AIUpdateInterface;
class DockUpdateInterface;
class Module;
class SupplyWarehouseDockUpdate;
class ResourceGatheringManager;
class SupplyTruckAIInterface;
class BfmeVec3EJ;
class Gen_000E5A50;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

static NameKeyType NAMEKEY(const char *name)
{
	return TheNameKeyGenerator->nameToKey(name);
}

class SupplyTruckAIInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Real getWarehouseScanDistance() const = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual ObjectIDValue getPreferredDockID() const = 0;
};

class AIUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12C() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual void slot144() = 0;
	virtual void slot148() = 0;
	virtual void slot14C() = 0;
	virtual void slot150() = 0;
	virtual void slot154() = 0;
	virtual void slot158() = 0;
	virtual void slot15C() = 0;
	virtual void slot160() = 0;
	virtual void slot164() = 0;
	virtual void slot168() = 0;
	virtual void slot16C() = 0;
	virtual void slot170() = 0;
	virtual void slot174() = 0;
	virtual void slot178() = 0;
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
};

class BfmeVec3EJ
{
public:
	Real m_x;
	Real m_y;
	Real m_z;
};

class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *point) const;

private:
	int m_head[14];
	Real m_x;
	Real m_y;
	Real m_z;
};

class Object : public Gen_000E5A50
{
protected:
	// Retail's Object::findModule (ILT 0x0002AE23): protected, const, returns
	// Module*. ResourceGatheringManager is the caller here, so it is befriended
	// rather than the declaration being made public (QBE, not IBE).
	friend class ResourceGatheringManager;
	Module *findModule(NameKeyType name) const;

public:
	AIUpdateInterface *getAI() const { return m_ai; }
	DockUpdateInterface *getDockUpdateInterface();
	BfmeVec3EJ *position() const
	{
		return (BfmeVec3EJ *)((char *)this + 0x38);
	}

private:
	char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;
};

class ActionManager
{
public:
	Bool canTransferSuppliesAt(const Object *object, const Object *destination);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern ActionManager *TheActionManager;
extern GameLogic *TheGameLogic;

class DockUpdateInterface
{
public:
	virtual Bool isClearToApproach(const Object *docker) const = 0;
};

static Real computeRelativeCost(Object *queryObject, Object *destObject, Real *pureDistanceSquared)
{
	if (queryObject == NULL || destObject == NULL)
		return FLT_MAX;

	if (!TheActionManager->canTransferSuppliesAt(queryObject, destObject))
		return FLT_MAX;

	DockUpdateInterface *dockInterface = destObject->getDockUpdateInterface();
	if (!dockInterface->isClearToApproach(queryObject))
		return FLT_MAX;

	Real distSquared = queryObject->bfmeDistanceSquared(destObject->position());
	if (pureDistanceSquared)
		*pureDistanceSquared = distSquared;

	return distSquared;
}

class ResourceGatheringManager
{
public:
	Object *findBestSupplyWarehouse(Object *queryObject);
	Object *findBestSupplyCenter(Object *queryObject);

private:
	typedef _STL::list<ObjectIDValue> objectIDList;
	typedef objectIDList::iterator objectIDListIterator;

	void *m_slice_vtbl;
	objectIDList m_supplyWarehouses;
	objectIDList m_supplyCenters;
};

// ?findBestSupplyWarehouse@ResourceGatheringManager@@QAEPAVObject@@PAV2@@Z
Object *ResourceGatheringManager::findBestSupplyWarehouse(Object *queryObject)
{
	Object *bestWarehouse = NULL;
	Real maxDistanceSquared = 100000;

	if (queryObject == NULL || queryObject->getAI() == NULL)
		return NULL;

	SupplyTruckAIInterface *supplyTruckAI =
		queryObject->getAI()->getSupplyTruckAIInterface();
	if (supplyTruckAI)
	{
		ObjectIDValue dockID = supplyTruckAI->getPreferredDockID();
		Object *dock = TheGameLogic->findObjectByID((ObjectID)dockID);
		if (dock)
		{
			static const NameKeyType key_warehouseUpdate =
				NAMEKEY("SupplyWarehouseDockUpdate");
			SupplyWarehouseDockUpdate *warehouseModule =
				(SupplyWarehouseDockUpdate *)dock->findModule(key_warehouseUpdate);
			if (warehouseModule &&
				computeRelativeCost(queryObject, dock, NULL) != FLT_MAX)
				return dock;
		}

		maxDistanceSquared = supplyTruckAI->getWarehouseScanDistance() *
			supplyTruckAI->getWarehouseScanDistance();
	}

	Real bestCost = FLT_MAX;
	objectIDListIterator iterator = m_supplyWarehouses.begin();
	while (iterator != m_supplyWarehouses.end())
	{
		Object *currentWarehouse =
			TheGameLogic->findObjectByID((ObjectID)*iterator);

		if (currentWarehouse == NULL)
		{
			iterator = m_supplyWarehouses.erase(iterator);
		}
		else
		{
			Real distanceSquared;
			Real currentCost = computeRelativeCost(queryObject,
				currentWarehouse, &distanceSquared);
			if (currentCost < bestCost && distanceSquared < maxDistanceSquared)
			{
				bestWarehouse = currentWarehouse;
				bestCost = currentCost;
			}

			iterator++;
		}
	}

	return bestWarehouse;
}

// ?findBestSupplyCenter@ResourceGatheringManager@@QAEPAVObject@@PAV2@@Z
Object *ResourceGatheringManager::findBestSupplyCenter(Object *queryObject)
{
	Object *bestCenter = NULL;

	if (queryObject == NULL || queryObject->getAI() == NULL)
		return NULL;

	SupplyTruckAIInterface *supplyTruckAI =
		queryObject->getAI()->getSupplyTruckAIInterface();
	if (supplyTruckAI)
	{
		ObjectIDValue dockID = supplyTruckAI->getPreferredDockID();
		Object *dock = TheGameLogic->findObjectByID((ObjectID)dockID);
		if (dock)
		{
			static const NameKeyType key_centerUpdate =
				NAMEKEY("SupplyCenterDockUpdate");
			SupplyWarehouseDockUpdate *centerModule =
				(SupplyWarehouseDockUpdate *)dock->findModule(key_centerUpdate);
			if (centerModule &&
				computeRelativeCost(queryObject, dock, NULL) != FLT_MAX)
				return dock;
		}
	}

	Real bestCost = FLT_MAX;
	objectIDListIterator iterator = m_supplyCenters.begin();
	while (iterator != m_supplyCenters.end())
	{
		Object *currentCenter =
			TheGameLogic->findObjectByID((ObjectID)*iterator);

		if (currentCenter == NULL)
		{
			iterator = m_supplyWarehouses.erase(iterator);
		}
		else
		{
			Real currentCost = computeRelativeCost(queryObject,
				currentCenter, NULL);
			if (currentCost < bestCost)
			{
				bestCenter = currentCenter;
				bestCost = currentCost;
			}

			iterator++;
		}
	}

	return bestCenter;
}
