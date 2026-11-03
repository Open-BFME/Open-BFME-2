// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@WallUpgradeUpdate@@UBE?AW4NameKeyType@@XZ @0x004AB2D2
// (69B): cached pool-name key for WallUpgradeUpdate. The class
// identity comes from the pool-name string the body pushes
// ("WallUpgradeUpdate"); the body guards a function-local static
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

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/GameLogic/Module/WallUpgradeUpdate.h"

// ?getModuleNameKey@WallUpgradeUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType WallUpgradeUpdate::getModuleNameKey() const
{
	static NameKeyType TheWallUpgradeUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("WallUpgradeUpdate");
	return TheWallUpgradeUpdatePoolKey;
}
