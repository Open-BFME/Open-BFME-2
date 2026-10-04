// ?upgradeImplementation@CastleUpgrade@@MAEXXZ
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?upgradeImplementation@CastleUpgrade@@MAEXXZ, retail 0x004B698A, 178 bytes:
// slot 10 of CastleUpgrade's +0x10 UpgradeMux vftable 0x00C58838 (the
// upgradeImplementation slot of the Zero Hour UpgradeMux, whose
// attemptUpgrade / forceRefreshUpgrade sit in slots 1 and 5), so `this` is
// that subobject. Resolves the upgrade the module data names at +0x118; when
// the Object has a "CastleMemberBehavior" module (function-static NAMEKEY,
// Zero Hour style) whose +0x18 castle Object still exists, hands the upgrade
// to that castle's CastleBehavior (0x00397357) and to the castle Object
// (rowed 0x00293003); then always to the class's own 0x004B68B6 on the
// primary this. Helper identities are address names.
//
// NEAR MISS: identical but for an esi/edi swap (retail keeps `this` in edi
// and the module data, then the upgrade, in esi).
#include "ascii_string.h"

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

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Module;
class CastleUpgrade;

class Object
{
public:
	void rva00293003(const void *upgrade);
protected:
	Module *findModule(NameKeyType key) const;
	friend class CastleUpgrade;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
	void rva00397357(const UpgradeTemplate *upgrade);
};

struct CastleMemberBehaviorView
{
	unsigned char m_pad00[0x18];
	ObjectID m_castleID; // +0x18
};

struct CastleUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	AsciiString m_upgradeName; // +0x118
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const CastleUpgradeModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeMux
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09();
protected:
	virtual void upgradeImplementation() = 0;
};

class CastleUpgrade : public ObjectModule, public BehaviorModuleInterface, public UpgradeMux
{
protected:
	virtual void upgradeImplementation();
private:
	void rva004B68B6(const UpgradeTemplate *upgrade);
};

void CastleUpgrade::upgradeImplementation()
{
	const CastleUpgradeModuleData *data = m_moduleData;
	Object *obj = m_object;
	static NameKeyType key_CastleMemberBehavior = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	CastleMemberBehaviorView *member = (CastleMemberBehaviorView *)obj->findModule(key_CastleMemberBehavior);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_upgradeName);
	if (member)
	{
		Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
		if (castle)
		{
			CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
			behavior->rva00397357(upgrade);
			castle->rva00293003(upgrade);
		}
	}
	rva004B68B6(upgrade);
}
