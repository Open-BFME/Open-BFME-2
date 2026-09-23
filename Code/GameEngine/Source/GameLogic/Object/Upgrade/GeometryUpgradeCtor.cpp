// cl: /O1 /DNDEBUG /MD /GX
//
// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B6A5E,
// 91 bytes. Behavior-side module ctor: UpgradeModule base plus the four
// most-derived vtable slots and the upgrade-name string cleared in the body.
// Identity is the rowed GeometryUpgrade::friend_newModuleInstance at
// 0x0025060A (news 0x20, calls this ctor with Thing* and ModuleData*) plus
// the BFME1 GeometryUpgradeConstructor donor (same base call, same four
// vtable slots at +0/+0xC/+0x10/+0x18, same AsciiString at +0x1C cleared
// through the folded 0x36410).
//
// Shape follows the donor and the SubObjectsUpgrade file-unit (same four
// slots; +0xC/+0x18 reuse 0xC57328/0xC58790 family-wide): the slots live
// inside the 0x1C UpgradeModule footprint, so the most-derived ctor
// re-emits all four before the member init (sibling
// GeometryUpgradeModuleDataCtor precedent: compiler vtable store precedes
// member nulls). No explicit stores and no statics; all four immediates
// are DIR32-masked in comparison.

class Thing;
class ModuleData;

class __declspec(novtable) UpgradeIfaceA
{
public:
	virtual void upgradeIfaceAAnchor();

private:
	unsigned char m_padA[8];
};

class __declspec(novtable) UpgradeIfaceB
{
public:
	virtual void upgradeIfaceBAnchor();
};

class BehaviorModule : public UpgradeIfaceA, public UpgradeIfaceB
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	~BehaviorModule();
};

class __declspec(novtable) UpgradeMuxBase
{
public:
	virtual void upgradeMuxAnchor();

private:
	unsigned int m_executed;
};

class UpgradeMux : public UpgradeMuxBase
{
public:
	UpgradeMux();
};

class __declspec(novtable) UpgradeTailBase
{
public:
	virtual void upgradeTailAnchor();
};

class UpgradeModule : public BehaviorModule, public UpgradeMux, public UpgradeTailBase
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	~UpgradeModule();
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class GeometryUpgrade : public UpgradeModule
{
public:
	GeometryUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~GeometryUpgrade();

private:
	AsciiString m_upgradeName; // +0x1C
};

// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B6A5E
GeometryUpgrade::GeometryUpgrade(Thing *thing, const ModuleData *moduleData) :
	UpgradeModule(thing, moduleData)
{
	m_upgradeName.clear();
}
