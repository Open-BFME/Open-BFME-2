// cl: /DNDEBUG /MD /EHsc
// ?rva00047C03A@SiegeEngineContain@@SA?AW4NameKeyType@@XZ @0x47C03A
// (69B): cached pool-name key for SiegeEngineContain. The class
// identity comes from the pool-name string the body pushes
// ("SiegeEngineContain"); the body guards a function-local static
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

class SiegeEngineContain
{
public:
	static NameKeyType rva00047C03A();
};

// ?rva00047C03A@SiegeEngineContain@@SA?AW4NameKeyType@@XZ
NameKeyType SiegeEngineContain::rva00047C03A()
{
	static NameKeyType TheSiegeEngineContainPoolKey =
		TheNameKeyGenerator->nameToKey("SiegeEngineContain");
	return TheSiegeEngineContainPoolKey;
}
