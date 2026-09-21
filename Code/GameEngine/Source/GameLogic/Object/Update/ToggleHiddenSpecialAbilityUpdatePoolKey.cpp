// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004AE1CC@ToggleHiddenSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x4AE1CC
// (69B): cached pool-name key for ToggleHiddenSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ToggleHiddenSpecialAbilityUpdate"); the body guards a function-local static
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

class ToggleHiddenSpecialAbilityUpdate
{
public:
	static NameKeyType rva004AE1CC();
};

// ?rva004AE1CC@ToggleHiddenSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ToggleHiddenSpecialAbilityUpdate::rva004AE1CC()
{
	static NameKeyType TheToggleHiddenSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
	return TheToggleHiddenSpecialAbilityUpdatePoolKey;
}
