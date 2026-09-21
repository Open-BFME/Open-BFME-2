// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004CC9DF@DominateEnemySpecialPower@@SA?AW4NameKeyType@@XZ @0x4CC9DF
// (69B): cached pool-name key for DominateEnemySpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("DominateEnemySpecialPower"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row). The body ends
// exactly where the DominateEnemySpecialPowerModuleData ctor at 0x4CCA24
// begins (poolkey-ends-where-ctor-begins linkage).

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

class DominateEnemySpecialPower
{
public:
	static NameKeyType rva004CC9DF();
};

// ?rva004CC9DF@DominateEnemySpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType DominateEnemySpecialPower::rva004CC9DF()
{
	static NameKeyType TheDominateEnemySpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("DominateEnemySpecialPower");
	return TheDominateEnemySpecialPowerPoolKey;
}
