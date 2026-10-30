// cl: /O1 /DNDEBUG /MD /EHsc

enum NameKeyType;
class Object;
class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

class WeaponChangeSpecialPowerModule : public SpecialPowerModule
{
public:
	WeaponChangeSpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual ~WeaponChangeSpecialPowerModule();
};

WeaponChangeSpecialPowerModule::WeaponChangeSpecialPowerModule( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// ??1WeaponChangeSpecialPowerModule@@MAE@XZ present-unmatched
WeaponChangeSpecialPowerModule::~WeaponChangeSpecialPowerModule()
{
}
