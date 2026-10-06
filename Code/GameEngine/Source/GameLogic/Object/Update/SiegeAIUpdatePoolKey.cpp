// cl: /DNDEBUG /MD /EHsc
// ?rva00049056B@SiegeAIUpdate@@SA?AW4NameKeyType@@XZ @0x49056b
// (69B): cached pool-name key for SiegeAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("SiegeAIUpdate"); the body guards a function-local static
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

class SiegeAIUpdate
{
public:
	static NameKeyType rva00049056B();
};

// ?rva00049056B@SiegeAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType SiegeAIUpdate::rva00049056B()
{
	static NameKeyType TheSiegeAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("SiegeAIUpdate");
	return TheSiegeAIUpdatePoolKey;
}

