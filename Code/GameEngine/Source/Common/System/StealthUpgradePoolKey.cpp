// cl: /DNDEBUG /MD /EHsc
// ?rva0004B5333@StealthUpgrade@@SA?AW4NameKeyType@@XZ @0x4B5333
// (69B): cached pool-name key for StealthUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("StealthUpgrade"); the body guards a function-local static
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

class StealthUpgrade
{
public:
	static NameKeyType rva0004B5333();
};

// ?rva0004B5333@StealthUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType StealthUpgrade::rva0004B5333()
{
	static NameKeyType TheStealthUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("StealthUpgrade");
	return TheStealthUpgradePoolKey;
}
