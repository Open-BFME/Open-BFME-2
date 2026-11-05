// cl: /DNDEBUG /MD
// Retail 0x00460804: the BehaviorModule base constructor followed by the
// primary WargBehavior table and the inherited BehaviorModuleInterface table.
// Snapshot overrides remain to be recovered; see LINK-572.

enum NameKeyType { NK_UNKNOWN = 0 };
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class WargBehavior : public BehaviorModule
{
public:
	WargBehavior(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
};

// ??0WargBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x460804
WargBehavior::WargBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
}
