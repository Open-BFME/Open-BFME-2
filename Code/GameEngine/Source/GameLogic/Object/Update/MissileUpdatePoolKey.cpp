// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004A7699@MissileUpdate@@SA?AW4NameKeyType@@XZ @0x4A7699
// (69B): cached pool-name key for MissileUpdate. The class
// identity comes from the pool-name string the body pushes
// ("MissileUpdate"); the body guards a function-local static
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

class MissileUpdate
{
public:
	static NameKeyType rva0004A7699();
};

// ?rva0004A7699@MissileUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType MissileUpdate::rva0004A7699()
{
	static NameKeyType TheMissileUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("MissileUpdate");
	return TheMissileUpdatePoolKey;
}
