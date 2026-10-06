// cl: /DNDEBUG /MD /EHsc
// ?rva000452DA3@WallHubBehavior@@SA?AW4NameKeyType@@XZ @0x452DA3
// (69B): cached pool-name key for WallHubBehavior. The class
// identity comes from the pool-name string the body pushes
// ("WallHubBehavior"); the body guards a function-local static
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

class WallHubBehavior
{
public:
	static NameKeyType rva000452DA3();
};

// ?rva000452DA3@WallHubBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType WallHubBehavior::rva000452DA3()
{
	static NameKeyType TheWallHubBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("WallHubBehavior");
	return TheWallHubBehaviorPoolKey;
}
