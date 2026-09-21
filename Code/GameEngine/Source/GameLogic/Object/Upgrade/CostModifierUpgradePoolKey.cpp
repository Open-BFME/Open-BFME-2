// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B59B7@CostModifierUpgrade@@SA?AW4NameKeyType@@XZ @0x004B59B7
// (69B): cached pool-name key for CostModifierUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("CostModifierUpgrade"); the body guards a function-local static
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

class CostModifierUpgrade
{
public:
	static NameKeyType rva004B59B7();
};

// ?rva004B59B7@CostModifierUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType CostModifierUpgrade::rva004B59B7()
{
	static NameKeyType TheCostModifierUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("CostModifierUpgrade");
	return TheCostModifierUpgradePoolKey;
}
