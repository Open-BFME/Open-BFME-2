// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00004BC988@MoneyCrateCollide@@SA?AW4NameKeyType@@XZ @0x4BC988
// (69B): cached pool-name key for MoneyCrateCollide. The class
// identity comes from the pool-name string the body pushes
// ("MoneyCrateCollide"); the body guards a function-local static
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

class MoneyCrateCollide
{
public:
	static NameKeyType rva00004BC988();
};

// ?rva00004BC988@MoneyCrateCollide@@SA?AW4NameKeyType@@XZ
NameKeyType MoneyCrateCollide::rva00004BC988()
{
	static NameKeyType TheMoneyCrateCollidePoolKey =
		TheNameKeyGenerator->nameToKey("MoneyCrateCollide");
	return TheMoneyCrateCollidePoolKey;
}
