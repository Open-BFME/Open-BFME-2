// cl: /DNDEBUG /MD /EHsc
// ?rva0004BD60C@CivilianSpawnCollide@@SA?AW4NameKeyType@@XZ @0x4BD60C
// (69B): cached pool-name key for CivilianSpawnCollide. The class
// identity comes from the pool-name string the body pushes
// ("CivilianSpawnCollide"); the body guards a function-local static
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

class CivilianSpawnCollide
{
public:
	static NameKeyType rva0004BD60C();
};

// ?rva0004BD60C@CivilianSpawnCollide@@SA?AW4NameKeyType@@XZ
NameKeyType CivilianSpawnCollide::rva0004BD60C()
{
	static NameKeyType TheCivilianSpawnCollidePoolKey =
		TheNameKeyGenerator->nameToKey("CivilianSpawnCollide");
	return TheCivilianSpawnCollidePoolKey;
}
