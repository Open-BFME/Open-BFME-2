// cl: /DNDEBUG /MD /EHsc
// ?rva000492CB0@TeleportSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x492cb0
// (69B): cached pool-name key for TeleportSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("TeleportSpecialAbilityUpdate"); the body guards a function-local static
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

class TeleportSpecialAbilityUpdate
{
public:
	static NameKeyType rva000492CB0();
};

// ?rva000492CB0@TeleportSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType TeleportSpecialAbilityUpdate::rva000492CB0()
{
	static NameKeyType TheTeleportSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("TeleportSpecialAbilityUpdate");
	return TheTeleportSpecialAbilityUpdatePoolKey;
}

