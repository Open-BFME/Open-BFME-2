// cl: /DNDEBUG /MD /EHsc
// ?rva00045876C@BridgeTowerBehavior@@SA?AW4NameKeyType@@XZ @0x45876C
// (69B): cached pool-name key for BridgeTowerBehavior. The class
// identity comes from the pool-name string the body pushes
// ("BridgeTowerBehavior"); the body guards a function-local static
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

class BridgeTowerBehavior
{
public:
	static NameKeyType rva00045876C();
};

// ?rva00045876C@BridgeTowerBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType BridgeTowerBehavior::rva00045876C()
{
	static NameKeyType TheBridgeTowerBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("BridgeTowerBehavior");
	return TheBridgeTowerBehaviorPoolKey;
}
