// cl: /DNDEBUG /MD /EHsc
// ?rva0047801C@GarrisonContain@@SA?AW4NameKeyType@@XZ @0x47801C
// (68B): cached pool-name key for GarrisonContain. The class
// identity comes from the pool-name string the body pushes
// ("GarrisonContain"); the body guards a function-local static
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

class GarrisonContain
{
public:
	static NameKeyType rva0047801C();
};

// ?rva0047801C@GarrisonContain@@SA?AW4NameKeyType@@XZ
NameKeyType GarrisonContain::rva0047801C()
{
	static NameKeyType TheGarrisonContainPoolKey =
		TheNameKeyGenerator->nameToKey("GarrisonContain");
	return TheGarrisonContainPoolKey;
}
