// cl: /DNDEBUG /MD /EHsc
// ?rva0004663FF@CaveContain@@SA?AW4NameKeyType@@XZ @0x4663ff
// (69B): cached pool-name key for CaveContain. The class
// identity comes from the pool-name string the body pushes
// ("CaveContain"); the body guards a function-local static
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

class CaveContain
{
public:
	static NameKeyType rva0004663FF();
};

// ?rva0004663FF@CaveContain@@SA?AW4NameKeyType@@XZ
NameKeyType CaveContain::rva0004663FF()
{
	static NameKeyType TheCaveContainPoolKey =
		TheNameKeyGenerator->nameToKey("CaveContain");
	return TheCaveContainPoolKey;
}

