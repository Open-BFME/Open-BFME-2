// cl: /DNDEBUG /MD /EHsc
// ?rva00046082D@WargBehavior@@SA?AW4NameKeyType@@XZ @0x46082D
// (69B): cached pool-name key for WargBehavior. The class
// identity comes from the pool-name string the body pushes
// ("WargBehavior"); the body guards a function-local static
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

class WargBehavior
{
public:
	static NameKeyType rva00046082D();
};

// ?rva00046082D@WargBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType WargBehavior::rva00046082D()
{
	static NameKeyType TheWargBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("WargBehavior");
	return TheWargBehaviorPoolKey;
}
