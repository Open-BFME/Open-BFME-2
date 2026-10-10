// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SupplyCenterDockUpdate module ctor.
// Out-of-line base MI, then four most-derived vtbls at +0/+0xC/+0x10/+0x20.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class SupplyCenterDockUpdateIface1
{
public:
	virtual void supplyCenterDockUpdateIface1Anchor();
};

class SupplyCenterDockUpdateIface2
{
public:
	virtual void supplyCenterDockUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class SupplyCenterDockUpdateIface3
{
public:
	virtual void supplyCenterDockUpdateIface3Anchor();
};

class SupplyCenterDockUpdateBase : public BehaviorModule,
	public SupplyCenterDockUpdateIface1,
	public SupplyCenterDockUpdateIface2,
	public SupplyCenterDockUpdateIface3
{
public:
	SupplyCenterDockUpdateBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h
class SupplyCenterDockUpdate : public SupplyCenterDockUpdateBase
{
public:
	SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData);
};

// The BehaviorModule vftable anchor: declared virtual in 60 TUs but defined
// nowhere, so every one of them carries U ?behaviorModuleAnchor. Defined once
// here (empty: retail inlines or dead-strips it; no retail bytes are claimed,
// hence present-unmatched rather than a row).
// The BehaviorModule vftable anchor: declared virtual in 60 TUs but defined
// nowhere, so every one of them carries U ?behaviorModuleAnchor. Defined once
// here (empty: retail inlines or dead-strips it; no retail bytes are claimed,
// hence present-unmatched rather than a row).
// ?behaviorModuleAnchor@BehaviorModule@@UAEXXZ present-unmatched
void BehaviorModule::behaviorModuleAnchor()
{
}

// Sibling vftable anchors, same story as behaviorModuleAnchor above: declared
// virtual across their subsystems, defined nowhere. Defined once here so the
// 29 + 23 + 5 units naming them resolve. No retail bytes claimed.
// ?behaviorModuleInterfaceAnchor@BehaviorModuleInterface@@UAEXXZ present-unmatched
struct BehaviorModuleInterface
{
	virtual void behaviorModuleInterfaceAnchor();
};

void BehaviorModuleInterface::behaviorModuleInterfaceAnchor()
{
}

// ?upgradeMuxAnchor@UpgradeMux@@UAEXXZ present-unmatched
struct UpgradeMux
{
	virtual void upgradeMuxAnchor();
};

void UpgradeMux::upgradeMuxAnchor()
{
}

// ?bodyModuleInterfaceAnchor@BodyModuleInterface@@UAEXXZ present-unmatched
struct BodyModuleInterface
{
	virtual void bodyModuleInterfaceAnchor();
};

void BodyModuleInterface::bodyModuleInterfaceAnchor()
{
}

// The MemoryPoolFactory pool lookup: 80 TUs reach it through the
// DEFINE_MEMORYPOOL macro (TheMemoryPoolFactory->findMemoryPool), but no TU
// defines it. Zero Hour's GameMemory.cpp walks the factory's pool list with
// strcmp; this TU-local view mirrors ZH's member order (factory head pointer
// first; pool factory-link, name, then the rest) and implements the same
// walk. Only the walked fields are touched; BFME2's own factory layout past
// them is unrecovered. No retail bytes are claimed (present-unmatched).
extern "C" int __cdecl strcmp(const char *a, const char *b);

class DynamicMemoryAllocator;

class MemoryPool
{
public:
	MemoryPool *getNextPoolInList() { return m_nextPoolInFactory; }
	const char *getPoolName() { return m_poolName; }

private:
	void *m_factory;
	MemoryPool *m_nextPoolInFactory;
	const char *m_poolName;
};

class MemoryPoolFactory
{
public:
	MemoryPool *findMemoryPool(const char *poolName);

private:
	MemoryPool *m_firstPoolInFactory;
	DynamicMemoryAllocator *m_firstDmaInFactory;
};

// ?findMemoryPool@MemoryPoolFactory@@QAEPAVMemoryPool@@PBD@Z present-unmatched
MemoryPool *MemoryPoolFactory::findMemoryPool(const char *poolName)
{
	for (MemoryPool *pool = m_firstPoolInFactory; pool; pool = pool->getNextPoolInList())
	{
		if (!strcmp(poolName, pool->getPoolName()))
			return pool;
	}
	return 0;
}

// ??0SupplyCenterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyCenterDockUpdate::SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData)
	: SupplyCenterDockUpdateBase(thing, moduleData)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface2Anchor@SupplyCenterDockUpdateIface2@@UAEXXZ=?update@SupplyCenterDockUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface1Anchor@SupplyCenterDockUpdateIface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface3Anchor@SupplyCenterDockUpdateIface3@@UAEXXZ=?isClearToApproach@DockUpdate@@UBE_NPBVObject@@@Z")
