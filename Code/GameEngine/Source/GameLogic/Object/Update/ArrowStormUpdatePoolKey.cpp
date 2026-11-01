// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@ArrowStormUpdate@@UBE?AW4NameKeyType@@XZ @0x4907F7
// (69B): cached pool-name key for ArrowStormUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ArrowStormUpdate"); the body guards a function-local static
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

class ArrowStormUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ArrowStormUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType ArrowStormUpdate::getModuleNameKey() const
{
	static NameKeyType TheArrowStormUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ArrowStormUpdate");
	return TheArrowStormUpdatePoolKey;
}
