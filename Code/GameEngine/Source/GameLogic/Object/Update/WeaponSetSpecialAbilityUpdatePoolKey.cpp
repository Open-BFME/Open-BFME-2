// cl: /DNDEBUG /MD /EHsc
// ?rva000492459@WeaponSetSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x492459
// (69B): cached pool-name key for WeaponSetSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("WeaponSetSpecialAbilityUpdate"); the body guards a function-local static
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

class WeaponSetSpecialAbilityUpdate
{
public:
	static NameKeyType rva000492459();
};

// ?rva000492459@WeaponSetSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType WeaponSetSpecialAbilityUpdate::rva000492459()
{
	static NameKeyType TheWeaponSetSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("WeaponSetSpecialAbilityUpdate");
	return TheWeaponSetSpecialAbilityUpdatePoolKey;
}

