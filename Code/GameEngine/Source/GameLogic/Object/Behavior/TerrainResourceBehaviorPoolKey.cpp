// cl: /DNDEBUG /MD /EHsc
// ?rva000481FBD@TerrainResourceBehavior@@SA?AW4NameKeyType@@XZ @0x481fbd
// (69B): cached pool-name key for TerrainResourceBehavior. The class
// identity comes from the pool-name string the body pushes
// ("TerrainResourceBehavior"); the body guards a function-local static
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

class TerrainResourceBehavior
{
public:
	static NameKeyType rva000481FBD();
};

// ?rva000481FBD@TerrainResourceBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType TerrainResourceBehavior::rva000481FBD()
{
	static NameKeyType TheTerrainResourceBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("TerrainResourceBehavior");
	return TheTerrainResourceBehaviorPoolKey;
}

