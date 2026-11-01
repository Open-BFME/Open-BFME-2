// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@RampageBehavior@@UBE?AW4NameKeyType@@XZ @0x458b0a
// (69B): cached pool-name key for RampageBehavior. The class
// identity comes from the pool-name string the body pushes
// ("RampageBehavior"); the body guards a function-local static
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

class RampageBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RampageBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType RampageBehavior::getModuleNameKey() const
{
	static NameKeyType TheRampageBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("RampageBehavior");
	return TheRampageBehaviorPoolKey;
}

