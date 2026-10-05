// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class DamageInfo;
class Object;
typedef bool Bool;

class GameLogic
{
public:
	void destroyObject(Object *obj);
};
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );
	Object *getObject() const { return m_object; }

private:
	unsigned char m_data[4];
	Object *m_object; // +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
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
protected:
	Bool isDieApplicable( const DamageInfo *damageInfo ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DestroyDie.h
class DestroyDie : public DieModule
{
public:
	DestroyDie( Thing *thing, const ModuleData *moduleData );
	virtual void onDie( const DamageInfo *damageInfo );
};

DestroyDie::DestroyDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}

// ?onDie@DestroyDie@@UAEXPBVDamageInfo@@@Z retail 0x00486554 35B: Zero Hour's
// DestroyDie::onDie, entered through the DieModuleInterface vtable at VA
// 0x00C4ACC4 with this on the +0x10 interface (hence the -0x10 adjust); a
// start missing from the Ghidra inventory.
void DestroyDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;
	TheGameLogic->destroyObject(getObject());
}
