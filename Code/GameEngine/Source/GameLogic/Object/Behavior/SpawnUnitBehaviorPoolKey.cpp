// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B8752@SpawnUnitBehavior@@SA?AW4NameKeyType@@XZ @0x004B8752
// (69B): cached pool-name key for SpawnUnitBehavior. The class
// identity comes from the pool-name string the body pushes
// ("SpawnUnitBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class SpawnUnitBehavior
{
public:
	static NameKeyType rva004B8752();
};

// ?rva004B8752@SpawnUnitBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType SpawnUnitBehavior::rva004B8752()
{
	static NameKeyType TheSpawnUnitBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("SpawnUnitBehavior");
	return TheSpawnUnitBehaviorPoolKey;
}
