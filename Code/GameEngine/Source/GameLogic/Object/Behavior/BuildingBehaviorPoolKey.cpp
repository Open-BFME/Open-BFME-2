// cl: /DNDEBUG /MD /EHsc
// ?rva0004561C1@BuildingBehavior@@SA?AW4NameKeyType@@XZ @0x4561C1
// (69B): cached pool-name key for BuildingBehavior. The class
// identity comes from the pool-name string the body pushes
// ("BuildingBehavior"); the body guards a function-local static
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

class BuildingBehavior
{
public:
	static NameKeyType rva0004561C1();
};

// ?rva0004561C1@BuildingBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType BuildingBehavior::rva0004561C1()
{
	static NameKeyType TheBuildingBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("BuildingBehavior");
	return TheBuildingBehaviorPoolKey;
}
