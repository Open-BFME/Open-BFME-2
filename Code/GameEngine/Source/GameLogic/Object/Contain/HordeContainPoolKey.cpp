// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@HordeContain@@UBE?AW4NameKeyType@@XZ @0x46f860
// (69B): cached pool-name key for HordeContain. The class
// identity comes from the pool-name string the body pushes
// ("HordeContain"); the body guards a function-local static
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

class HordeContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeContain::getModuleNameKey() const
{
	static NameKeyType TheHordeContainPoolKey =
		TheNameKeyGenerator->nameToKey("HordeContain");
	return TheHordeContainPoolKey;
}

