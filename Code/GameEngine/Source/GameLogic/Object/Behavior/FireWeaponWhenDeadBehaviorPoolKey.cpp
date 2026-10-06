// cl: /DNDEBUG /MD /EHsc
// ?rva000482E51@FireWeaponWhenDeadBehavior@@SA?AW4NameKeyType@@XZ @0x482e51
// (69B): cached pool-name key for FireWeaponWhenDeadBehavior. The class
// identity comes from the pool-name string the body pushes
// ("FireWeaponWhenDeadBehavior"); the body guards a function-local static
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

class FireWeaponWhenDeadBehavior
{
public:
	static NameKeyType rva000482E51();
};

// ?rva000482E51@FireWeaponWhenDeadBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType FireWeaponWhenDeadBehavior::rva000482E51()
{
	static NameKeyType TheFireWeaponWhenDeadBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("FireWeaponWhenDeadBehavior");
	return TheFireWeaponWhenDeadBehaviorPoolKey;
}

