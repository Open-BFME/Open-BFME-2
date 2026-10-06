// cl: /DNDEBUG /MD /EHsc
// ?rva0004B3423@ArmorUpgrade@@SA?AW4NameKeyType@@XZ @0x4B3423
// (69B): cached pool-name key for ArmorUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("ArmorUpgrade"); the body guards a function-local static
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

class ArmorUpgrade
{
public:
	static NameKeyType rva0004B3423();
};

// ?rva0004B3423@ArmorUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType ArmorUpgrade::rva0004B3423()
{
	static NameKeyType TheArmorUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("ArmorUpgrade");
	return TheArmorUpgradePoolKey;
}
