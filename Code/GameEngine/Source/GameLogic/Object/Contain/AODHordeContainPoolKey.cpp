// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@AODHordeContain@@UBE?AW4NameKeyType@@XZ @0x47B51E
// (69B): cached pool-name key for AODHordeContain. The class
// identity comes from the pool-name string the body pushes
// ("AODHordeContain"); the body guards a function-local static
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

class AODHordeContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AODHordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType AODHordeContain::getModuleNameKey() const
{
	static NameKeyType TheAODHordeContainPoolKey =
		TheNameKeyGenerator->nameToKey("AODHordeContain");
	return TheAODHordeContainPoolKey;
}
