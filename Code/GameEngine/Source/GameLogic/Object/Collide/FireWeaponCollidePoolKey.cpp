// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00004BB755@FireWeaponCollide@@SA?AW4NameKeyType@@XZ @0x4BB755
// (69B): cached pool-name key for FireWeaponCollide. The class
// identity comes from the pool-name string the body pushes
// ("FireWeaponCollide"); the body guards a function-local static
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

class FireWeaponCollide
{
public:
	static NameKeyType rva00004BB755();
};

// ?rva00004BB755@FireWeaponCollide@@SA?AW4NameKeyType@@XZ
NameKeyType FireWeaponCollide::rva00004BB755()
{
	static NameKeyType TheFireWeaponCollidePoolKey =
		TheNameKeyGenerator->nameToKey("FireWeaponCollide");
	return TheFireWeaponCollidePoolKey;
}
