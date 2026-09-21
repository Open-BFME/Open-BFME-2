// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00004BD220@SalvageCrateCollide@@SA?AW4NameKeyType@@XZ @0x4BD220
// (69B): cached pool-name key for SalvageCrateCollide. The class
// identity comes from the pool-name string the body pushes
// ("SalvageCrateCollide"); the body guards a function-local static
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

class SalvageCrateCollide
{
public:
	static NameKeyType rva00004BD220();
};

// ?rva00004BD220@SalvageCrateCollide@@SA?AW4NameKeyType@@XZ
NameKeyType SalvageCrateCollide::rva00004BD220()
{
	static NameKeyType TheSalvageCrateCollidePoolKey =
		TheNameKeyGenerator->nameToKey("SalvageCrateCollide");
	return TheSalvageCrateCollidePoolKey;
}
