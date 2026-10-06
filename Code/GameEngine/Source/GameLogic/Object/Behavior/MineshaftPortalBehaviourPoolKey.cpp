// cl: /DNDEBUG /MD /EHsc
// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ @0x373109
// (69B): cached pool-name key for MineshaftPortalBehaviour. The class
// identity comes from the pool-name string the body pushes
// ("MineshaftPortalBehaviour"); the body guards a function-local static
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

class MineshaftPortalBehaviour
{
public:
	static NameKeyType rva000373109();
};

// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ
NameKeyType MineshaftPortalBehaviour::rva000373109()
{
	static NameKeyType TheMineshaftPortalBehaviourPoolKey =
		TheNameKeyGenerator->nameToKey("MineshaftPortalBehaviour");
	return TheMineshaftPortalBehaviourPoolKey;
}
