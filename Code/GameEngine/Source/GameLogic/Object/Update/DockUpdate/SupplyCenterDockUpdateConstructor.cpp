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
	virtual void behaviorAnchor();
	virtual void ifaceAnchor();
};

void BehaviorModuleInterface::behaviorModuleInterfaceAnchor()
{
}
// ?behaviorAnchor@BehaviorModuleInterface@@UAEXXZ present-unmatched
void BehaviorModuleInterface::behaviorAnchor()
{
}
// ?ifaceAnchor@BehaviorModuleInterface@@UAEXXZ present-unmatched
void BehaviorModuleInterface::ifaceAnchor()
{
}

// ?upgradeMuxAnchor@UpgradeMux@@UAEXXZ present-unmatched
struct UpgradeMux
{
	virtual void upgradeMuxAnchor();
	virtual void muxAnchor();
};

void UpgradeMux::upgradeMuxAnchor()
{
}
// ?muxAnchor@UpgradeMux@@UAEXXZ present-unmatched
void UpgradeMux::muxAnchor()
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

// More single-definition vftable anchors of the same shape: each is
// declared virtual in its subsystem TU(s) and defined nowhere. Defined once
// here; no retail bytes claimed.
// ?clearanceTestingSlowDeathBehaviorIface2Anchor@ClearanceTestingSlowDeathBehaviorIface2@@UAEXXZ present-unmatched
struct ClearanceTestingSlowDeathBehaviorIface2
{
	virtual void clearanceTestingSlowDeathBehaviorIface2Anchor();
};

void ClearanceTestingSlowDeathBehaviorIface2::clearanceTestingSlowDeathBehaviorIface2Anchor()
{
}

// ?clearanceTestingSlowDeathBehaviorIface3Anchor@ClearanceTestingSlowDeathBehaviorIface3@@UAEXXZ present-unmatched
struct ClearanceTestingSlowDeathBehaviorIface3
{
	virtual void clearanceTestingSlowDeathBehaviorIface3Anchor();
};

void ClearanceTestingSlowDeathBehaviorIface3::clearanceTestingSlowDeathBehaviorIface3Anchor()
{
}

// ?clearanceTestingSlowDeathBehaviorIface4Anchor@ClearanceTestingSlowDeathBehaviorIface4@@UAEXXZ present-unmatched
struct ClearanceTestingSlowDeathBehaviorIface4
{
	virtual void clearanceTestingSlowDeathBehaviorIface4Anchor();
};

void ClearanceTestingSlowDeathBehaviorIface4::clearanceTestingSlowDeathBehaviorIface4Anchor()
{
}

// ?clearanceTestingSlowDeathBehaviorIface5Anchor@ClearanceTestingSlowDeathBehaviorIface5@@UAEXXZ present-unmatched
struct ClearanceTestingSlowDeathBehaviorIface5
{
	virtual void clearanceTestingSlowDeathBehaviorIface5Anchor();
};

void ClearanceTestingSlowDeathBehaviorIface5::clearanceTestingSlowDeathBehaviorIface5Anchor()
{
}

// ?collideModuleInterfaceAnchor@InlineCollideModuleInterface@@UAEXXZ present-unmatched
struct InlineCollideModuleInterface
{
	virtual void collideModuleInterfaceAnchor();
};

void InlineCollideModuleInterface::collideModuleInterfaceAnchor()
{
}

// ?damageModuleInterfaceAnchor@InlineDamageModuleInterface@@UAEXXZ present-unmatched
struct InlineDamageModuleInterface
{
	virtual void damageModuleInterfaceAnchor();
};

void InlineDamageModuleInterface::damageModuleInterfaceAnchor()
{
}

// ?deflectSpecialPowerIface2Anchor@DeflectSpecialPowerIface2@@UAEXXZ present-unmatched
struct DeflectSpecialPowerIface2
{
	virtual void deflectSpecialPowerIface2Anchor();
};

void DeflectSpecialPowerIface2::deflectSpecialPowerIface2Anchor()
{
}

// ?deflectSpecialPowerIface3Anchor@DeflectSpecialPowerIface3@@UAEXXZ present-unmatched
struct DeflectSpecialPowerIface3
{
	virtual void deflectSpecialPowerIface3Anchor();
};

void DeflectSpecialPowerIface3::deflectSpecialPowerIface3Anchor()
{
}

// ?deflectSpecialPowerIface4Anchor@DeflectSpecialPowerIface4@@UAEXXZ present-unmatched
struct DeflectSpecialPowerIface4
{
	virtual void deflectSpecialPowerIface4Anchor();
};

void DeflectSpecialPowerIface4::deflectSpecialPowerIface4Anchor()
{
}

// ?deflectSpecialPowerIface5Anchor@DeflectSpecialPowerIface5@@UAEXXZ present-unmatched
struct DeflectSpecialPowerIface5
{
	virtual void deflectSpecialPowerIface5Anchor();
};

void DeflectSpecialPowerIface5::deflectSpecialPowerIface5Anchor()
{
}

// ?siegeAIUpdateIface2Anchor@SiegeAIUpdateIface2@@UAEXXZ present-unmatched
struct SiegeAIUpdateIface2
{
	virtual void siegeAIUpdateIface2Anchor();
};

void SiegeAIUpdateIface2::siegeAIUpdateIface2Anchor()
{
}

// ?siegeAIUpdateIface3Anchor@SiegeAIUpdateIface3@@UAEXXZ present-unmatched
struct SiegeAIUpdateIface3
{
	virtual void siegeAIUpdateIface3Anchor();
};

void SiegeAIUpdateIface3::siegeAIUpdateIface3Anchor()
{
}

// ?siegeAIUpdateIface4Anchor@SiegeAIUpdateIface4@@UAEXXZ present-unmatched
struct SiegeAIUpdateIface4
{
	virtual void siegeAIUpdateIface4Anchor();
};

void SiegeAIUpdateIface4::siegeAIUpdateIface4Anchor()
{
}

// ?specialPowerExtraAnchor@SpecialPowerModuleExtra@@UAEXXZ present-unmatched
struct SpecialPowerModuleExtra
{
	virtual void specialPowerExtraAnchor();
};

void SpecialPowerModuleExtra::specialPowerExtraAnchor()
{
}

// ?transportAIUpdateIface2Anchor@TransportAIUpdateIface2@@UAEXXZ present-unmatched
struct TransportAIUpdateIface2
{
	virtual void transportAIUpdateIface2Anchor();
};

void TransportAIUpdateIface2::transportAIUpdateIface2Anchor()
{
}

// ?transportAIUpdateIface3Anchor@TransportAIUpdateIface3@@UAEXXZ present-unmatched
struct TransportAIUpdateIface3
{
	virtual void transportAIUpdateIface3Anchor();
};

void TransportAIUpdateIface3::transportAIUpdateIface3Anchor()
{
}

// ?transportAIUpdateIface4Anchor@TransportAIUpdateIface4@@UAEXXZ present-unmatched
struct TransportAIUpdateIface4
{
	virtual void transportAIUpdateIface4Anchor();
};

void TransportAIUpdateIface4::transportAIUpdateIface4Anchor()
{
}

// ?weaponModeIface2Anchor@WeaponModeSpecialPowerUpdateIface2@@UAEXXZ present-unmatched
struct WeaponModeSpecialPowerUpdateIface2
{
	virtual void weaponModeIface2Anchor();
};

void WeaponModeSpecialPowerUpdateIface2::weaponModeIface2Anchor()
{
}

// ?weaponModeIface3Anchor@WeaponModeSpecialPowerUpdateIface3@@UAEXXZ present-unmatched
struct WeaponModeSpecialPowerUpdateIface3
{
	virtual void weaponModeIface3Anchor();
};

void WeaponModeSpecialPowerUpdateIface3::weaponModeIface3Anchor()
{
}

// ?weaponModeIface4Anchor@WeaponModeSpecialPowerUpdateIface4@@UAEXXZ present-unmatched
struct WeaponModeSpecialPowerUpdateIface4
{
	virtual void weaponModeIface4Anchor();
};

void WeaponModeSpecialPowerUpdateIface4::weaponModeIface4Anchor()
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

// Further single-definition vftable anchors of the same shape: one struct
// per class; each out-of-line body carries its own present-unmatched marker
// directly above it (a marker above the struct does not bind to later
// definitions); no retail bytes claimed.

struct AudioLoopBase0C
{
	virtual void base0CAnchor();
};

// ?base0CAnchor@AudioLoopBase0C@@UAEXXZ present-unmatched
void AudioLoopBase0C::base0CAnchor()
{
}

struct AudioLoopBase10
{
	virtual void base10Anchor();
};

// ?base10Anchor@AudioLoopBase10@@UAEXXZ present-unmatched
void AudioLoopBase10::base10Anchor()
{
}

struct AudioLoopBase20
{
	virtual void base20Anchor();
};

// ?base20Anchor@AudioLoopBase20@@UAEXXZ present-unmatched
void AudioLoopBase20::base20Anchor()
{
}

struct AudioLoopBase28
{
	virtual void base28Anchor();
};

// ?base28Anchor@AudioLoopBase28@@UAEXXZ present-unmatched
void AudioLoopBase28::base28Anchor()
{
}

struct AutoPickUpUpdateInterface
{
	virtual void autoPickUpAnchor();
};

// ?autoPickUpAnchor@AutoPickUpUpdateInterface@@UAEXXZ present-unmatched
void AutoPickUpUpdateInterface::autoPickUpAnchor()
{
}

struct BehaviorIface
{
	virtual void behaviorIfaceAnchor();
};

// ?behaviorIfaceAnchor@BehaviorIface@@UAEXXZ present-unmatched
void BehaviorIface::behaviorIfaceAnchor()
{
}

struct BehaviorModuleBase
{
	virtual void behaviorModuleBaseAnchor();
};

// ?behaviorModuleBaseAnchor@BehaviorModuleBase@@UAEXXZ present-unmatched
void BehaviorModuleBase::behaviorModuleBaseAnchor()
{
}

struct BehaviorModuleOther
{
	virtual void behaviorModuleOtherAnchor();
};

// ?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ present-unmatched
void BehaviorModuleOther::behaviorModuleOtherAnchor()
{
}

struct ClearanceTestingSlowDeathBehaviorIface1
{
	virtual void clearanceTestingSlowDeathBehaviorIface1Anchor();
};

// ?clearanceTestingSlowDeathBehaviorIface1Anchor@ClearanceTestingSlowDeathBehaviorIface1@@UAEXXZ present-unmatched
void ClearanceTestingSlowDeathBehaviorIface1::clearanceTestingSlowDeathBehaviorIface1Anchor()
{
}

struct CreateModuleInterface
{
	virtual void createModuleInterfaceAnchor();
};

// ?createModuleInterfaceAnchor@CreateModuleInterface@@UAEXXZ present-unmatched
void CreateModuleInterface::createModuleInterfaceAnchor()
{
}

struct DeflectSpecialPowerIface1
{
	virtual void deflectSpecialPowerIface1Anchor();
};

// ?deflectSpecialPowerIface1Anchor@DeflectSpecialPowerIface1@@UAEXXZ present-unmatched
void DeflectSpecialPowerIface1::deflectSpecialPowerIface1Anchor()
{
}

struct DeflectSpecialPowerModuleDataBase
{
	virtual void moduleDataAnchor();
};

// ?moduleDataAnchor@DeflectSpecialPowerModuleDataBase@@UAEXXZ present-unmatched
void DeflectSpecialPowerModuleDataBase::moduleDataAnchor()
{
}

struct DemoTrapUpdate
{
	virtual void behaviorAnchor();
	virtual void objectModuleAnchor();
};

// ?behaviorAnchor@DemoTrapUpdate@@UAEXXZ present-unmatched
void DemoTrapUpdate::behaviorAnchor()
{
}

// ?objectModuleAnchor@DemoTrapUpdate@@UAEXXZ present-unmatched
void DemoTrapUpdate::objectModuleAnchor()
{
}

struct DockUpdate
{
	virtual void behaviorAnchor();
	virtual void dockAnchor();
	virtual void objectModuleAnchor();
};

// ?behaviorAnchor@DockUpdate@@UAEXXZ present-unmatched
void DockUpdate::behaviorAnchor()
{
}

// ?dockAnchor@DockUpdate@@UAEXXZ present-unmatched
void DockUpdate::dockAnchor()
{
}

// ?objectModuleAnchor@DockUpdate@@UAEXXZ present-unmatched
void DockUpdate::objectModuleAnchor()
{
}

struct DrawModule
{
	virtual void drawModuleAnchor();
};

// ?drawModuleAnchor@DrawModule@@UAEXXZ present-unmatched
void DrawModule::drawModuleAnchor()
{
}

struct ExperienceLevelCreateIface1
{
	virtual void experienceLevelCreateIface1Anchor();
};

// ?experienceLevelCreateIface1Anchor@ExperienceLevelCreateIface1@@UAEXXZ present-unmatched
void ExperienceLevelCreateIface1::experienceLevelCreateIface1Anchor()
{
}

struct ExperienceLevelCreateIface2
{
	virtual void experienceLevelCreateIface2Anchor();
};

// ?experienceLevelCreateIface2Anchor@ExperienceLevelCreateIface2@@UAEXXZ present-unmatched
void ExperienceLevelCreateIface2::experienceLevelCreateIface2Anchor()
{
}

struct ObjectModule
{
	virtual void objectAnchor();
};

// ?objectAnchor@ObjectModule@@UAEXXZ present-unmatched
void ObjectModule::objectAnchor()
{
}

struct ObjectModuleBase
{
	virtual void objectModuleAnchor();
};

// ?objectModuleAnchor@ObjectModuleBase@@UAEXXZ present-unmatched
void ObjectModuleBase::objectModuleAnchor()
{
}

struct RadarUpdate
{
	virtual void behaviorAnchor();
	virtual void objectModuleAnchor();
	virtual void updateAnchor();
};

// ?behaviorAnchor@RadarUpdate@@UAEXXZ present-unmatched
void RadarUpdate::behaviorAnchor()
{
}

// ?objectModuleAnchor@RadarUpdate@@UAEXXZ present-unmatched
void RadarUpdate::objectModuleAnchor()
{
}

// ?updateAnchor@RadarUpdate@@UAEXXZ present-unmatched
void RadarUpdate::updateAnchor()
{
}

struct Rva0056B218B1
{
	virtual void b1Anchor();
};

// ?b1Anchor@Rva0056B218B1@@UAEXXZ present-unmatched
void Rva0056B218B1::b1Anchor()
{
}

struct SiegeAIUpdateIface1
{
	virtual void siegeAIUpdateIface1Anchor();
};

// ?siegeAIUpdateIface1Anchor@SiegeAIUpdateIface1@@UAEXXZ present-unmatched
void SiegeAIUpdateIface1::siegeAIUpdateIface1Anchor()
{
}

struct SpecialPowerModuleInterface
{
	virtual void specialPowerModuleInterfaceAnchor();
};

// ?specialPowerModuleInterfaceAnchor@SpecialPowerModuleInterface@@UAEXXZ present-unmatched
void SpecialPowerModuleInterface::specialPowerModuleInterfaceAnchor()
{
}

struct TransportAIUpdateIface1
{
	virtual void transportAIUpdateIface1Anchor();
};

// ?transportAIUpdateIface1Anchor@TransportAIUpdateIface1@@UAEXXZ present-unmatched
void TransportAIUpdateIface1::transportAIUpdateIface1Anchor()
{
}

struct UpgradeIfaceA
{
	virtual void upgradeIfaceAAnchor();
};

// ?upgradeIfaceAAnchor@UpgradeIfaceA@@UAEXXZ present-unmatched
void UpgradeIfaceA::upgradeIfaceAAnchor()
{
}

struct UpgradeIfaceB
{
	virtual void upgradeIfaceBAnchor();
};

// ?upgradeIfaceBAnchor@UpgradeIfaceB@@UAEXXZ present-unmatched
void UpgradeIfaceB::upgradeIfaceBAnchor()
{
}

struct UpgradeModuleInterface
{
	virtual void upgradeModuleInterfaceAnchor();
};

// ?upgradeModuleInterfaceAnchor@UpgradeModuleInterface@@UAEXXZ present-unmatched
void UpgradeModuleInterface::upgradeModuleInterfaceAnchor()
{
}

struct UpgradeMuxBase
{
	virtual void upgradeMuxAnchor();
};

// ?upgradeMuxAnchor@UpgradeMuxBase@@UAEXXZ present-unmatched
void UpgradeMuxBase::upgradeMuxAnchor()
{
}

struct UpgradeTailBase
{
	virtual void upgradeTailAnchor();
};

// ?upgradeTailAnchor@UpgradeTailBase@@UAEXXZ present-unmatched
void UpgradeTailBase::upgradeTailAnchor()
{
}

struct WeaponModeSpecialPowerUpdateIface1
{
	virtual void weaponModeIface1Anchor();
};

// ?weaponModeIface1Anchor@WeaponModeSpecialPowerUpdateIface1@@UAEXXZ present-unmatched
void WeaponModeSpecialPowerUpdateIface1::weaponModeIface1Anchor()
{
}
