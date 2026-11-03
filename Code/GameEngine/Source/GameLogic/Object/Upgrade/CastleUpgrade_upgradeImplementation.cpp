// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?upgradeImplementation@CastleUpgrade@@MAEXXZ, retail 0x004b698a, 178 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
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

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
	friend class CastleUpgrade;

public:
	void rva00293003(const void *upgrade); // rowed: applies the upgrade to the object's upgrade modules

protected:
	Module *findModule(NameKeyType key) const;
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Upgrade.h"

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

#include "../../../../Include/GameLogic/Module/CastleUpgradeModuleData.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
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
	const UpgradeTemplate *upgrade = (TheUpgradeCenter?TheUpgradeCenter:TheUpgradeCenter)->findUpgrade(data->m_upgradeToGrant);
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
