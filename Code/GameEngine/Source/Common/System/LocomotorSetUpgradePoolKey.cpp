// cl: /DNDEBUG /MD /EHsc
// ?rva0004B3EC6@LocomotorSetUpgrade@@SA?AW4NameKeyType@@XZ @0x4B3EC6
// (69B): cached pool-name key for LocomotorSetUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("LocomotorSetUpgrade"); the body guards a function-local static
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

class LocomotorSetUpgrade
{
public:
	static NameKeyType rva0004B3EC6();
};

// ?rva0004B3EC6@LocomotorSetUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType LocomotorSetUpgrade::rva0004B3EC6()
{
	static NameKeyType TheLocomotorSetUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("LocomotorSetUpgrade");
	return TheLocomotorSetUpgradePoolKey;
}
