// cl: /DNDEBUG /MD /EHsc
// ?rva000455167@FoundationAIUpdate@@SA?AW4NameKeyType@@XZ @0x455167
// (69B): cached pool-name key for FoundationAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FoundationAIUpdate"); the body guards a function-local static
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

class FoundationAIUpdate
{
public:
	static NameKeyType rva000455167();
};

// ?rva000455167@FoundationAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType FoundationAIUpdate::rva000455167()
{
	static NameKeyType TheFoundationAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FoundationAIUpdate");
	return TheFoundationAIUpdatePoolKey;
}

