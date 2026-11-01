// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@TerrainResourceClientBehavior@@UBE?AW4NameKeyType@@XZ @0x252E0B
// (69B): cached pool-name key for TerrainResourceClientBehavior. The class
// identity comes from the pool-name string the body pushes
// ("TerrainResourceClientBehavior"); the body guards a function-local static
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

class TerrainResourceClientBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@TerrainResourceClientBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType TerrainResourceClientBehavior::getModuleNameKey() const
{
	static NameKeyType TheTerrainResourceClientBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("TerrainResourceClientBehavior");
	return TheTerrainResourceClientBehaviorPoolKey;
}
