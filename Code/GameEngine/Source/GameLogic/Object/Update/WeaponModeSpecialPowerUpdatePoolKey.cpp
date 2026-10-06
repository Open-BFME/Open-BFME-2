// cl: /DNDEBUG /MD /EHsc
// ?rva000494AF3@WeaponModeSpecialPowerUpdate@@SA?AW4NameKeyType@@XZ @0x494af3
// (69B): cached pool-name key for WeaponModeSpecialPowerUpdate. The class
// identity comes from the pool-name string the body pushes
// ("WeaponModeSpecialPowerUpdate"); the body guards a function-local static
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

class WeaponModeSpecialPowerUpdate
{
public:
	static NameKeyType rva000494AF3();
};

// ?rva000494AF3@WeaponModeSpecialPowerUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType WeaponModeSpecialPowerUpdate::rva000494AF3()
{
	static NameKeyType TheWeaponModeSpecialPowerUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("WeaponModeSpecialPowerUpdate");
	return TheWeaponModeSpecialPowerUpdatePoolKey;
}

