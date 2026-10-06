// cl: /DNDEBUG /MD /EHsc
// ?rva00047E2E0@RiderChangeContain@@SA?AW4NameKeyType@@XZ @0x47e2e0
// (69B): cached pool-name key for RiderChangeContain. The class
// identity comes from the pool-name string the body pushes
// ("RiderChangeContain"); the body guards a function-local static
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

class RiderChangeContain
{
public:
	static NameKeyType rva00047E2E0();
};

// ?rva00047E2E0@RiderChangeContain@@SA?AW4NameKeyType@@XZ
NameKeyType RiderChangeContain::rva00047E2E0()
{
	static NameKeyType TheRiderChangeContainPoolKey =
		TheNameKeyGenerator->nameToKey("RiderChangeContain");
	return TheRiderChangeContainPoolKey;
}

