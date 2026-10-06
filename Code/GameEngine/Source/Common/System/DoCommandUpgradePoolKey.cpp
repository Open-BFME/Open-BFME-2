// cl: /DNDEBUG /MD /EHsc
// ?rva0004B4BC7@DoCommandUpgrade@@SA?AW4NameKeyType@@XZ @0x4B4BC7
// (69B): cached pool-name key for DoCommandUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("DoCommandUpgrade"); the body guards a function-local static
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

class DoCommandUpgrade
{
public:
	static NameKeyType rva0004B4BC7();
};

// ?rva0004B4BC7@DoCommandUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType DoCommandUpgrade::rva0004B4BC7()
{
	static NameKeyType TheDoCommandUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("DoCommandUpgrade");
	return TheDoCommandUpgradePoolKey;
}
