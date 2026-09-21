// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004BCE7B@VeterancyCrateCollide@@SA?AW4NameKeyType@@XZ @0x4BCE7B
// (69B): cached pool-name key for VeterancyCrateCollide. The class
// identity comes from the pool-name string the body pushes
// ("VeterancyCrateCollide"); the body guards a function-local static
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

class VeterancyCrateCollide
{
public:
	static NameKeyType rva0004BCE7B();
};

// ?rva0004BCE7B@VeterancyCrateCollide@@SA?AW4NameKeyType@@XZ
NameKeyType VeterancyCrateCollide::rva0004BCE7B()
{
	static NameKeyType TheVeterancyCrateCollidePoolKey =
		TheNameKeyGenerator->nameToKey("VeterancyCrateCollide");
	return TheVeterancyCrateCollidePoolKey;
}
