// cl: /DNDEBUG /MD /EHsc
// ?rva00048828E@DelayedWeaponSetUpgradeUpdate@@SA?AW4NameKeyType@@XZ @0x48828e
// (69B): cached pool-name key for DelayedWeaponSetUpgradeUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DelayedWeaponSetUpgradeUpdate"); the body guards a function-local static
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

class DelayedWeaponSetUpgradeUpdate
{
public:
	static NameKeyType rva00048828E();
};

// ?rva00048828E@DelayedWeaponSetUpgradeUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType DelayedWeaponSetUpgradeUpdate::rva00048828E()
{
	static NameKeyType TheDelayedWeaponSetUpgradeUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DelayedWeaponSetUpgradeUpdate");
	return TheDelayedWeaponSetUpgradeUpdatePoolKey;
}

