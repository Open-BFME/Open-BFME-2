// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B8C57@LockWeaponCreate@@SA?AW4NameKeyType@@XZ @0x004B8C57
// (69B): cached pool-name key for LockWeaponCreate. The class
// identity comes from the pool-name string the body pushes
// ("LockWeaponCreate"); the body guards a function-local static
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

class LockWeaponCreate
{
public:
	static NameKeyType rva004B8C57();
};

// ?rva004B8C57@LockWeaponCreate@@SA?AW4NameKeyType@@XZ
NameKeyType LockWeaponCreate::rva004B8C57()
{
	static NameKeyType TheLockWeaponCreatePoolKey =
		TheNameKeyGenerator->nameToKey("LockWeaponCreate");
	return TheLockWeaponCreatePoolKey;
}
