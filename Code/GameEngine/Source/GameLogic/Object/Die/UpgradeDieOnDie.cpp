// ?onDie@UpgradeDie@@UAEXPBVDamageInfo@@@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// ?onDie@UpgradeDie@@UAEXPBVDamageInfo@@@Z, retail 0x00486C00 118B (ret 4 at
// 0x486C73-75 pops 0x486C71-72 extent [0x486C00,0x486C76) next body at 0x486C76): findUpgrade-first plus UpgradeTemplate m_04
// ternary. A m_04==0 (player-scoped) upgrade is removed from the
// controlling player via Player::rva002ADAC3 (pinned 0x002ADAC3, ret 8,
// hoisted pushes); otherwise the producer is looked up via
// TheGameLogic->findObjectByID(getObject()->getProducerID()) and gated
// through has/remove (rowed 0x290D2B/0x290D42).
//
// Donor-carried (ZH GeneralsMD UpgradeDie::onDie at committed 6583b3c1, not
// target proof): producer lookup, UpgradeCenter findUpgrade, has/remove
// pair; the donor DEBUG_ASSERTCRASH else-path compiles to ((void)0) under
// /DNDEBUG so retail carries no assert calls. Target facts: Rva00485C86Finish
// ternary spelling precedent for the same m_04 split (t->m_04 int at +0x04);
// SalvageCrateCollide precedent that m_type==0 at +0x04 means a player
// upgrade; DieModule base keeps m_moduleData at +0x04 and m_object at +0x08;
// Object producer ID word at +0x78; UpgradeDieModuleData carries the
// AsciiString m_upgradeName at +0x38. All seven emitted callees are rowed or
// pinned: isDieApplicable 0x45CEA7, findUpgrade 0x26F26D,
// getControllingPlayer 0x28AFA9, rva002ADAC3 0x2ADAC3 (pin), findObjectByID
// 0x49DC5, rva00290D2B, rva00290D42. TheUpgradeCenter via the
// Rva00485C86Finish alternatename precedent; TheGameLogic via the
// HeroDieOnDie plain-extern precedent.
#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

class DamageInfo;
class Player;

class UpgradeTemplate
{
public:
	int m_00;
	int m_04;	// +0x04 (0 a player upgrade; Rva00485C86Finish precedent)
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	ObjectID getProducerID() const { return m_producerID; }
	bool rva00290D2B(const UpgradeTemplate *tmpl) const;
	void rva00290D42(const UpgradeTemplate *upgrade);

private:
	unsigned char m_pad00[0x04];
	const void *m_template04;	// +0x04 (opaque; DEBUG path compiled out)
	unsigned char m_pad08[0x78 - 0x08];
	ObjectID m_producerID;		// +0x78
};

class Player
{
public:
	void rva002ADAC3(const UpgradeTemplate *upgrade, int flag);	// 0x002ADAC3
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ModuleData;

struct UpgradeDieModuleData
{
	unsigned char m_pad00[0x38];
	AsciiString m_upgradeName;	// +0x38
};

class ModuleBase
{
public:
	virtual ~ModuleBase();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieModule : public ModuleBase,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	bool isDieApplicable(const DamageInfo *damageInfo) const;
	Object *getObject() { return m_object; }
	const UpgradeDieModuleData *getUpgradeDieModuleData() const
	{
		return (const UpgradeDieModuleData *)m_moduleData;
	}
};

class UpgradeDie : public DieModule
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

// ?onDie@UpgradeDie@@UAEXPBVDamageInfo@@@Z
void UpgradeDie::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;
	// Look for the upgrade first; a player-scoped upgrade is freed from the
	// controlling player, otherwise from the producer object.
	const UpgradeTemplate *upgrade =
		TheUpgradeCenter->findUpgrade(getUpgradeDieModuleData()->m_upgradeName);
	if (!upgrade)
		return;
	if (upgrade->m_04 == 0)
	{
		getObject()->getControllingPlayer()->rva002ADAC3(upgrade, 0);
		return;
	}
	// Look for the object that created me.
	Object *producer = TheGameLogic->findObjectByID(getObject()->getProducerID());
	if (!producer)
		return;
	// We found our parent: see if it has the upgrade set, then remove it.
	if (!producer->rva00290D2B(upgrade))
		return;
	producer->rva00290D42(upgrade);
}
