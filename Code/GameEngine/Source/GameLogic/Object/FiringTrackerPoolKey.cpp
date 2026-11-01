// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@FiringTracker@@UBE?AW4NameKeyType@@XZ @0x4DEACB
// (69B): cached pool-name key for FiringTracker. The class
// identity comes from the pool-name string the body pushes
// ("FiringTracker"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class FiringTracker
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FiringTracker@@UBE?AW4NameKeyType@@XZ
NameKeyType FiringTracker::getModuleNameKey() const
{
	static NameKeyType TheFiringTrackerPoolKey =
		TheNameKeyGenerator->nameToKey("FiringTracker");
	return TheFiringTrackerPoolKey;
}
