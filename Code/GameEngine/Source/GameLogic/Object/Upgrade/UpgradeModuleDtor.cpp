// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// UpgradeModule complete destructor, RVA 0x0046089D (32 bytes). Its protected
// scalar deleting destructor, RVA 0x00460B50, is emitted in the companion TU.
// Target identity: the verified UpgradeModule ctor 0x00460AEC installs the
// +0x10 table 0x00842720 and +0x18 table 0x00858790 restored here. Its primary
// table 0x00842768 has the deleting destructor in slot 0 and the verified
// UpgradeModule::xfer 0x004CE3F9 in slot 3. The named ArmorUpgrade,
// StealthUpgrade and DynamicPortalBehaviour destructors call this base.
// ZH's empty UpgradeModule destructor supplies the semantic lead; BFME2's
// fourth interface at +0x18 is established by those target stores, not ZH.
// The old FireWeaponWhenDeadBehavior spelling was a masked-placement error:
// that class's verified ctor 0x00482D80 uses UpdateModule and five tables,
// with UpgradeMux at +0x20 and DieModuleInterface at +0x28.

#include "Common/Snapshot.h"

// Destructor-only view: the empty Module/ObjectModule layers end in the
// canonical Snapshot fold at 0x0049B47C. Rva0049B47C is the existing opaque
// spelling for that fold; this definition is a 7-byte byte-and-relocation
// twin of the canonical destructor. The abstract prefix carries the
// module-data/object fields and needs no intermediate vptr restore.
#pragma inline_depth(1)
class __declspec(novtable) Rva0049B47C : public Snapshot
{
public:
	virtual ~Rva0049B47C() {}
protected:
	const void *m_moduleData;
	void *m_object;
};

class BodyModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;
};

#pragma inline_depth(0)
// A flattened destructor view, not a replacement declaration of BehaviorModule.
// Its base destruction is the same verified Snapshot fold; only the two
// vptr offsets of the cumulative 0x10-byte behavior prefix are modeled.
class UpgradeBehaviorBaseView : public Rva0049B47C, public BehaviorModuleInterface
{
protected:
	virtual ~UpgradeBehaviorBaseView() {}
};

class UpgradeMux
{
public:
	// Abstract layout placeholder; no virtual-slot identity is claimed here.
	virtual void upgradeMuxAnchor() = 0;
private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

class UpgradeModule : public UpgradeBehaviorBaseView, public UpgradeMux, public ModuleInterface
{
protected:
	virtual ~UpgradeModule();
};

// Inline the behavior layer, but keep the certified seven-byte prefix fold
// out of line as in retail's final tail call.
#pragma inline_depth(1)
UpgradeModule::~UpgradeModule()
{
}
#pragma inline_depth()
