// cl: /DNDEBUG /MD /EHsc
// ?rva000461EA0@GiantBirdSlowDeathBehavior@@SA?AW4NameKeyType@@XZ @0x461ea0
// (69B): cached pool-name key for GiantBirdSlowDeathBehavior. The class
// identity comes from the pool-name string the body pushes
// ("GiantBirdSlowDeathBehavior"); the body guards a function-local static
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

class GiantBirdSlowDeathBehavior
{
public:
	static NameKeyType rva000461EA0();
};

// ?rva000461EA0@GiantBirdSlowDeathBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType GiantBirdSlowDeathBehavior::rva000461EA0()
{
	static NameKeyType TheGiantBirdSlowDeathBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("GiantBirdSlowDeathBehavior");
	return TheGiantBirdSlowDeathBehaviorPoolKey;
}

