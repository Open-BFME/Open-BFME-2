// cl: /DNDEBUG /MD /EHsc
// ?rva00028CB96@ObjectWeaponStatusHelper@@SA?AW4NameKeyType@@XZ @0x28CB96
// (69B): cached pool-name key for ObjectWeaponStatusHelper. The class
// identity comes from the pool-name string the body pushes
// ("ObjectWeaponStatusHelper"); the body guards a function-local static
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

class ObjectWeaponStatusHelper
{
public:
	static NameKeyType rva00028CB96();
};

// ?rva00028CB96@ObjectWeaponStatusHelper@@SA?AW4NameKeyType@@XZ
NameKeyType ObjectWeaponStatusHelper::rva00028CB96()
{
	static NameKeyType TheObjectWeaponStatusHelperPoolKey =
		TheNameKeyGenerator->nameToKey("ObjectWeaponStatusHelper");
	return TheObjectWeaponStatusHelperPoolKey;
}
