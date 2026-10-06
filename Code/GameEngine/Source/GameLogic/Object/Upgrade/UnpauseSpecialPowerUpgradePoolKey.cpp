// cl: /DNDEBUG /MD /EHsc
// ?rva0004B5405@UnpauseSpecialPowerUpgrade@@SA?AW4NameKeyType@@XZ @0x4B5405
// (69B): cached pool-name key for UnpauseSpecialPowerUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("UnpauseSpecialPowerUpgrade"); the body guards a function-local static
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

class UnpauseSpecialPowerUpgrade
{
public:
	static NameKeyType rva0004B5405();
};

// ?rva0004B5405@UnpauseSpecialPowerUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType UnpauseSpecialPowerUpgrade::rva0004B5405()
{
	static NameKeyType TheUnpauseSpecialPowerUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("UnpauseSpecialPowerUpgrade");
	return TheUnpauseSpecialPowerUpgradePoolKey;
}
