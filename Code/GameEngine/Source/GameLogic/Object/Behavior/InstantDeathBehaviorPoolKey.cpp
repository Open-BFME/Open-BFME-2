// cl: /DNDEBUG /MD /EHsc
// ?rva00045CF10@InstantDeathBehavior@@SA?AW4NameKeyType@@XZ @0x45cf10
// (69B): cached pool-name key for InstantDeathBehavior. The class
// identity comes from the pool-name string the body pushes
// ("InstantDeathBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"
#include "../../../../Include/GameLogic/Module/DieModule.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Thing;
class ModuleData;
class DamageInfo;
class InstantDeathBehavior : public DieModule
{
public:
	static NameKeyType rva00045CF10();
	InstantDeathBehavior(Thing *thing, const ModuleData *moduleData);
	virtual void onDie(const DamageInfo*);
};

// ?rva00045CF10@InstantDeathBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType InstantDeathBehavior::rva00045CF10()
{
	static NameKeyType TheInstantDeathBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("InstantDeathBehavior");
	return TheInstantDeathBehaviorPoolKey;
}

