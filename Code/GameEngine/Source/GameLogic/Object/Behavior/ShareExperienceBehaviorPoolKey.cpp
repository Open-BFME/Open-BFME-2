// cl: /DNDEBUG /MD /EHsc
// ?rva00047FE4B@ShareExperienceBehavior@@SA?AW4NameKeyType@@XZ @0x47fe4b
// (69B): cached pool-name key for ShareExperienceBehavior. The class
// identity comes from the pool-name string the body pushes
// ("ShareExperienceBehavior"); the body guards a function-local static
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

class ShareExperienceBehavior
{
public:
	static NameKeyType rva00047FE4B();
};

// ?rva00047FE4B@ShareExperienceBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType ShareExperienceBehavior::rva00047FE4B()
{
	static NameKeyType TheShareExperienceBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("ShareExperienceBehavior");
	return TheShareExperienceBehaviorPoolKey;
}

