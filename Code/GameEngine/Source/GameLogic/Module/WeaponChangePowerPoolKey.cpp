// cl: /DNDEBUG /MD /EHsc
// ?rva004C4075@WeaponChangeSpecialPowerModule@@SA?AW4NameKeyType@@XZ @0x4C4075
// (68B): cached pool-name key for WeaponChangeSpecialPowerModule. The class
// identity comes from the pool-name string the body pushes
// ("WeaponChangeSpecialPowerModule"); the body guards a function-local static
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

class WeaponChangeSpecialPowerModule
{
public:
	static NameKeyType rva004C4075();
};

// ?rva004C4075@WeaponChangeSpecialPowerModule@@SA?AW4NameKeyType@@XZ
NameKeyType WeaponChangeSpecialPowerModule::rva004C4075()
{
	static NameKeyType TheWeaponChangeSpecialPowerModulePoolKey =
		TheNameKeyGenerator->nameToKey("WeaponChangeSpecialPowerModule");
	return TheWeaponChangeSpecialPowerModulePoolKey;
}
