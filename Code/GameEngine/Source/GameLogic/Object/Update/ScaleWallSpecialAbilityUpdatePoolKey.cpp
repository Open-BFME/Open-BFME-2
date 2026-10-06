// cl: /DNDEBUG /MD /EHsc
// ?rva000494E83@ScaleWallSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x494e83
// (69B): cached pool-name key for ScaleWallSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ScaleWallSpecialAbilityUpdate"); the body guards a function-local static
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

class ScaleWallSpecialAbilityUpdate
{
public:
	static NameKeyType rva000494E83();
};

// ?rva000494E83@ScaleWallSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ScaleWallSpecialAbilityUpdate::rva000494E83()
{
	static NameKeyType TheScaleWallSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ScaleWallSpecialAbilityUpdate");
	return TheScaleWallSpecialAbilityUpdatePoolKey;
}

