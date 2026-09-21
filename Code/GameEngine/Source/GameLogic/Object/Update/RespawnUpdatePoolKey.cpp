// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004AF116@RespawnUpdate@@SA?AW4NameKeyType@@XZ @0x4AF116
// (69B): cached pool-name key for RespawnUpdate. The class
// identity comes from the pool-name string the body pushes
// ("RespawnUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key not a pool pointer) and returns it
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail no pins; nameToKey resolves via its matched row).

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

class RespawnUpdate
{
public:
	static NameKeyType rva004AF116();
};

// ?rva004AF116@RespawnUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType RespawnUpdate::rva004AF116()
{
	static NameKeyType TheRespawnUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("RespawnUpdate");
	return TheRespawnUpdatePoolKey;
}
