// cl: /DNDEBUG /MD /EHsc
// ?rva0004583BD@BridgeScaffoldBehavior@@SA?AW4NameKeyType@@XZ @0x4583bd
// (69B): cached pool-name key for BridgeScaffoldBehavior. The class
// identity comes from the pool-name string the body pushes
// ("BridgeScaffoldBehavior"); the body guards a function-local static
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

class BridgeScaffoldBehavior
{
public:
	static NameKeyType rva0004583BD();
};

// ?rva0004583BD@BridgeScaffoldBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType BridgeScaffoldBehavior::rva0004583BD()
{
	static NameKeyType TheBridgeScaffoldBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("BridgeScaffoldBehavior");
	return TheBridgeScaffoldBehaviorPoolKey;
}

