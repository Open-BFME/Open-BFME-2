// cl: /DNDEBUG /MD /EHsc
// ?rva0004B57F4@GarrisonUpgrade@@SA?AW4NameKeyType@@XZ @0x4B57F4
// (69B): cached pool-name key for GarrisonUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("GarrisonUpgrade"); the body guards a function-local static
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

class GarrisonUpgrade
{
public:
	static NameKeyType rva0004B57F4();
};

// ?rva0004B57F4@GarrisonUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType GarrisonUpgrade::rva0004B57F4()
{
	static NameKeyType TheGarrisonUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("GarrisonUpgrade");
	return TheGarrisonUpgradePoolKey;
}
