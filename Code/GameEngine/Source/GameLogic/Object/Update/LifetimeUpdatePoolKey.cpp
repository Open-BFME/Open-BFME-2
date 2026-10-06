// cl: /DNDEBUG /MD /EHsc
// ?rva0003A4A27@LifetimeUpdate@@SA?AW4NameKeyType@@XZ @0x3a4a27
// (69B): cached pool-name key for LifetimeUpdate. The class
// identity comes from the pool-name string the body pushes
// ("LifetimeUpdate"); the body guards a function-local static
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

class LifetimeUpdate
{
public:
	static NameKeyType rva0003A4A27();
};

// ?rva0003A4A27@LifetimeUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType LifetimeUpdate::rva0003A4A27()
{
	static NameKeyType TheLifetimeUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("LifetimeUpdate");
	return TheLifetimeUpdatePoolKey;
}

