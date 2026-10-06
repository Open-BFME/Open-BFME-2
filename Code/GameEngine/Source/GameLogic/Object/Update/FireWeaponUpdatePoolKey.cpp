// cl: /DNDEBUG /MD /EHsc
// ?rva00048BDB3@FireWeaponUpdate@@SA?AW4NameKeyType@@XZ @0x48BDB3
// (69B): cached pool-name key for FireWeaponUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FireWeaponUpdate"); the body guards a function-local static
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

class FireWeaponUpdate
{
public:
	static NameKeyType rva00048BDB3();
};

// ?rva00048BDB3@FireWeaponUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType FireWeaponUpdate::rva00048BDB3()
{
	static NameKeyType TheFireWeaponUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FireWeaponUpdate");
	return TheFireWeaponUpdatePoolKey;
}
