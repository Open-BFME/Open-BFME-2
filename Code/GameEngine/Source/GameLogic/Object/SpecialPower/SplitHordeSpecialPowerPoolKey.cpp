// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C85BD@SplitHordeSpecialPower@@SA?AW4NameKeyType@@XZ @0x004C85BD
// (69B): cached pool-name key for SplitHordeSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("SplitHordeSpecialPower"); the body guards a function-local static
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

class SplitHordeSpecialPower
{
public:
	static NameKeyType rva004C85BD();
};

// ?rva004C85BD@SplitHordeSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType SplitHordeSpecialPower::rva004C85BD()
{
	static NameKeyType TheSplitHordeSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("SplitHordeSpecialPower");
	return TheSplitHordeSpecialPowerPoolKey;
}
