// cl: /DNDEBUG /MD /EHsc
// ?rva00045ADE0@DualWeaponBehavior@@SA?AW4NameKeyType@@XZ @0x45ade0
// (69B): cached pool-name key for DualWeaponBehavior. The class
// identity comes from the pool-name string the body pushes
// ("DualWeaponBehavior"); the body guards a function-local static
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

class DualWeaponBehavior
{
public:
	static NameKeyType rva00045ADE0();
};

// ?rva00045ADE0@DualWeaponBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType DualWeaponBehavior::rva00045ADE0()
{
	static NameKeyType TheDualWeaponBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
	return TheDualWeaponBehaviorPoolKey;
}

