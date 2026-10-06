// cl: /DNDEBUG /MD /EHsc
// ?rva000460BD3@DynamicPortalBehaviour@@SA?AW4NameKeyType@@XZ @0x460BD3
// (69B): cached pool-name key for DynamicPortalBehaviour. The class
// identity comes from the pool-name string the body pushes
// ("DynamicPortalBehaviour"); the body guards a function-local static
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

class DynamicPortalBehaviour
{
public:
	static NameKeyType rva000460BD3();
};

// ?rva000460BD3@DynamicPortalBehaviour@@SA?AW4NameKeyType@@XZ
NameKeyType DynamicPortalBehaviour::rva000460BD3()
{
	static NameKeyType TheDynamicPortalBehaviourPoolKey =
		TheNameKeyGenerator->nameToKey("DynamicPortalBehaviour");
	return TheDynamicPortalBehaviourPoolKey;
}
