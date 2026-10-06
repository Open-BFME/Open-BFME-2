// cl: /DNDEBUG /MD /EHsc
// ?rva000252E0B@TerrainResourceClientBehavior@@SA?AW4NameKeyType@@XZ @0x252E0B
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

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class TerrainResourceClientBehavior
{
public:
	static NameKeyType rva000252E0B();
};

// ?rva000252E0B@TerrainResourceClientBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType TerrainResourceClientBehavior::rva000252E0B()
{
	static NameKeyType TheTerrainResourceClientBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("TerrainResourceClientBehavior");
	return TheTerrainResourceClientBehaviorPoolKey;
}
