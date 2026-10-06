// ?upgradeImplementation@CastleUpgrade@@MAEXXZ
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"

class Thing;
class ModuleData;
class Module;
class UpgradeTemplate;
class CastleUpgrade;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
	friend class CastleUpgrade;

public:
	void rva00293003(const void *upgrade); // rowed: applies the upgrade to the object's upgrade modules

protected:
	Module *findModule(NameKeyType key) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA(); // rowed pool-key getter
};

// Castle-side behaviour found under CastleBehavior's key; 0x00397357 grants it the upgrade.
class Rva003972D3
{
public:
	void rva00397357(const UpgradeTemplate *upgrade);
};

// Module found under "CastleMemberBehavior": the owning castle's ID at +0x18 (retail-measured).
struct CastleMemberBehaviorView
{
	unsigned char m_pad00[0x18];
	ObjectID m_castleID; // +0x18
};

struct CastleUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	AsciiString m_upgradeToGrant; // +0x118 retail-measured
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

protected:
	virtual void upgradeImplementation() = 0;

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
};

class CastleUpgrade : public UpgradeModule
{
public:
	CastleUpgrade( Thing *thing, const ModuleData *moduleData );

protected:
	virtual void upgradeImplementation();

private:
	const CastleUpgradeModuleData *getCastleUpgradeModuleData() const
	{
		return (const CastleUpgradeModuleData *)getModuleData();
	}
	void rva004B68B6(const UpgradeTemplate *upgrade); // unrowed: nearby-object pass at 0x004B68B6
};

CastleUpgrade::CastleUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// CastleUpgrade::upgradeImplementation, retail 0x004B698A (178 bytes).
// Identity (target): WorldBuilder debug CastleUpgrade.cpp lines 64..77
// (wb-lead 2/callgraph); entered through the UpgradeMux subobject (+0x10).
// Retail callees in order: nameToKey("CastleMemberBehavior") into a
// function-static key, Object::findModule, UpgradeCenter::findUpgrade on the
// module data's +0x118 name, GameLogic::findObjectByID on the member module's
// +0x18 castle ID, CastleBehavior's key, findModule, 0x00397357 and
// 0x00293003 on the castle, then 0x004B68B6 on this module.
void CastleUpgrade::upgradeImplementation()
{
	const CastleUpgradeModuleData *data = getCastleUpgradeModuleData();
	Object *obj = getObject();

	static const NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	CastleMemberBehaviorView *member = (CastleMemberBehaviorView *)obj->findModule(key);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_upgradeToGrant);
	if (member)
	{
		Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
		if (castle)
		{
			Rva003972D3 *castleBehavior = (Rva003972D3 *)castle->findModule(CastleBehavior::rva0003955DA());
			castleBehavior->rva00397357(upgrade);
			castle->rva00293003(upgrade);
		}
	}
	rva004B68B6(upgrade);
}
