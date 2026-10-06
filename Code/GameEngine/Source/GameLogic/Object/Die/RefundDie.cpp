// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DestroyModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;
class UpgradeModuleInterface;
class ParkingPlaceBehaviorInterface;
class RebuildHoleBehaviorInterface;
class BridgeBehaviorInterface;
class BridgeTowerBehaviorInterface;
class BridgeScaffoldBehaviorInterface;
class OverchargeBehaviorInterface;
class TransportPassengerInterface;
class CaveInterface;
class LandMineInterface;
class ProjectileUpdateInterface;
class AIUpdateInterface;
class ExitInterface;
class DockUpdateInterface;
class RailedTransportDockUpdateInterface;
class SlowDeathBehaviorInterface;
class SpecialPowerUpdateInterface;
class SlavedUpdateInterface;
class ProductionUpdateInterface;
class HordeUpdateInterface;
class PowerPlantUpdateInterface;
class SpawnBehaviorInterface;
class CountermeasuresBehaviorInterface;
class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;
	virtual CollideModuleInterface *getCollide() = 0;
	virtual ContainModuleInterface *getContain() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
	virtual DamageModuleInterface *getDamage() = 0;
	virtual DestroyModuleInterface *getDestroy() = 0;
	virtual DieModuleInterface *getDie() = 0;
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;
	virtual UpdateModuleInterface *getUpdate() = 0;
	virtual UpgradeModuleInterface *getUpgrade() = 0;
	virtual ParkingPlaceBehaviorInterface *getParkingPlaceBehaviorInterface() = 0;
	virtual RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterface() = 0;
	virtual BridgeBehaviorInterface *getBridgeBehaviorInterface() = 0;
	virtual BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterface() = 0;
	virtual BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterface() = 0;
	virtual OverchargeBehaviorInterface *getOverchargeBehaviorInterface() = 0;
	virtual TransportPassengerInterface *getTransportPassengerInterface() = 0;
	virtual CaveInterface *getCaveInterface() = 0;
	virtual LandMineInterface *getLandMineInterface() = 0;
	virtual DieModuleInterface *getEjectPilotDieInterface() = 0;
	virtual ProjectileUpdateInterface *getProjectileUpdateInterface() = 0;
	virtual AIUpdateInterface *getAIUpdateInterface() = 0;
	virtual ExitInterface *getUpdateExitInterface() = 0;
	virtual DockUpdateInterface *getDockUpdateInterface() = 0;
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface() = 0;
	virtual SlowDeathBehaviorInterface *getSlowDeathBehaviorInterface() = 0;
	virtual SpecialPowerUpdateInterface *getSpecialPowerUpdateInterface() = 0;
	virtual SlavedUpdateInterface *getSlavedUpdateInterface() = 0;
	virtual ProductionUpdateInterface *getProductionUpdateInterface() = 0;
	virtual HordeUpdateInterface *getHordeUpdateInterface() = 0;
	virtual PowerPlantUpdateInterface *getPowerPlantUpdateInterface() = 0;
	virtual SpawnBehaviorInterface *getSpawnBehaviorInterface() = 0;
	virtual CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface() = 0;
	virtual const CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DamageInfo;
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	DieModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}
};

class RefundDie : public DieModule
{
public:
	RefundDie( Thing *thing, const ModuleData *moduleData );
};

RefundDie::RefundDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}
