// cl: /DNDEBUG /MD
//
// ??0CallHelpOnDamage@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BB43C,
// 44 bytes. Behavior-side ctor completing the CallHelpOnDamage file-unit
// (poolkey rowed at 0x4BB470, ModuleData factory rowed at 0x250F5D,
// behavior instance factory rowed at 0x250F25 news 0x34 with this ctor as
// sole raw caller).
//
// Shape: frameless ctor over the pinned DamageModule base 0x4B9704 with a
// leading and-zero member at +0x14; the compiler installs the +0/+0xC/+0x10
// tables (cl schedules the and-zero first, as retail).
// Zero new pins (base resolves via the existing DamageModule pin).

class Thing;
class ModuleData;
struct DamageInfo;

// Zero Hour's DamageModule shape (ObjectModule at +0, BehaviorModuleInterface
// at +0x0C, DamageModuleInterface at +0x10), the interface views
// CreateCrateDie.cpp and CallHelpOnDamageOnDamage.cpp declare. The
// DamageModule ctor is pinned at 0x004B9704. The compiler installs the three
// tables: 0x00C59FDC, the folded BehaviorModuleInterface table 0x00C597F8 and
// the DamageModuleInterface table 0x00C59FD0, whose slot 0 is the rowed
// CallHelpOnDamage::onDamage 0x004BB547.
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
};

class DamageModule : public ObjectModule, public BehaviorModuleInterface, public DamageModuleInterface
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageModule();	// 0x004B96CC, out of line
};

class CallHelpOnDamage : public DamageModule
{
public:
	CallHelpOnDamage(Thing *thing, const ModuleData *moduleData);
	virtual ~CallHelpOnDamage();	// 0x004BB4D1, out of line
	virtual void onDamage(DamageInfo *damageInfo);
private:
	int m_14;	// +0x14
};

// ??0CallHelpOnDamage@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB43C
CallHelpOnDamage::CallHelpOnDamage(Thing *thing, const ModuleData *moduleData) :
	DamageModule(thing, moduleData)
{
	m_14 = 0;
}
