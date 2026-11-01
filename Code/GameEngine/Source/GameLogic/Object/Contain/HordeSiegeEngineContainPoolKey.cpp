// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@HordeSiegeEngineContain@@UBE?AW4NameKeyType@@XZ @0x47d0a2
// (69B): cached pool-name key for HordeSiegeEngineContain. The class
// identity comes from the pool-name string the body pushes
// ("HordeSiegeEngineContain"); the body guards a function-local static
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

class HordeSiegeEngineContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeSiegeEngineContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeSiegeEngineContain::getModuleNameKey() const
{
	static NameKeyType TheHordeSiegeEngineContainPoolKey =
		TheNameKeyGenerator->nameToKey("HordeSiegeEngineContain");
	return TheHordeSiegeEngineContainPoolKey;
}

