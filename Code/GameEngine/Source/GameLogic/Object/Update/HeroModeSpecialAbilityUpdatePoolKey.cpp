// cl: /DNDEBUG /MD /EHsc
// ?rva0004921D0@HeroModeSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x4921d0
// (69B): cached pool-name key for HeroModeSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HeroModeSpecialAbilityUpdate"); the body guards a function-local static
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

class HeroModeSpecialAbilityUpdate
{
public:
	static NameKeyType rva0004921D0();
};

// ?rva0004921D0@HeroModeSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HeroModeSpecialAbilityUpdate::rva0004921D0()
{
	static NameKeyType TheHeroModeSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HeroModeSpecialAbilityUpdate");
	return TheHeroModeSpecialAbilityUpdatePoolKey;
}

