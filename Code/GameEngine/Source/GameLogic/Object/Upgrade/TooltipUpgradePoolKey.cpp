// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@TooltipUpgrade@@UBE?AW4NameKeyType@@XZ @0x004B79E9
// (69B): cached pool-name key for TooltipUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("TooltipUpgrade"); the body guards a function-local static
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

class TooltipUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@TooltipUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType TooltipUpgrade::getModuleNameKey() const
{
	static NameKeyType TheTooltipUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("TooltipUpgrade");
	return TheTooltipUpgradePoolKey;
}
