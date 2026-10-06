// cl: /DNDEBUG /MD /EHsc
// ?rva000484187@ReplenishUnitsBehavior@@SA?AW4NameKeyType@@XZ @0x484187
// (69B): cached pool-name key for ReplenishUnitsBehavior. The class
// identity comes from the pool-name string the body pushes
// ("ReplenishUnitsBehavior"); the body guards a function-local static
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

class ReplenishUnitsBehavior
{
public:
	static NameKeyType rva000484187();
};

// ?rva000484187@ReplenishUnitsBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType ReplenishUnitsBehavior::rva000484187()
{
	static NameKeyType TheReplenishUnitsBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("ReplenishUnitsBehavior");
	return TheReplenishUnitsBehaviorPoolKey;
}

