// cl: /DNDEBUG /MD /EHsc
// ?rva00047F97E@CivilianSpawnUpdate@@SA?AW4NameKeyType@@XZ @0x47f97e
// (69B): cached pool-name key for CivilianSpawnUpdate. The class
// identity comes from the pool-name string the body pushes
// ("CivilianSpawnUpdate"); the body guards a function-local static
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

class CivilianSpawnUpdate
{
public:
	static NameKeyType rva00047F97E();
};

// ?rva00047F97E@CivilianSpawnUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType CivilianSpawnUpdate::rva00047F97E()
{
	static NameKeyType TheCivilianSpawnUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("CivilianSpawnUpdate");
	return TheCivilianSpawnUpdatePoolKey;
}

