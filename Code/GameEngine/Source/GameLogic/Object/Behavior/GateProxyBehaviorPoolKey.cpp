// cl: /DNDEBUG /MD /EHsc
// ?rva0024E30E@GateProxyBehavior@@SA?AW4NameKeyType@@XZ @0x24E30E
// (69B): cached pool-name key for GateProxyBehavior. The class
// identity comes from the pool-name string the body pushes
// ("GateProxyBehavior"); the body guards a function-local static
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

class GateProxyBehavior
{
public:
	static NameKeyType rva0024E30E();
};

// ?rva0024E30E@GateProxyBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType GateProxyBehavior::rva0024E30E()
{
	static NameKeyType TheGateProxyBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("GateProxyBehavior");
	return TheGateProxyBehaviorPoolKey;
}
