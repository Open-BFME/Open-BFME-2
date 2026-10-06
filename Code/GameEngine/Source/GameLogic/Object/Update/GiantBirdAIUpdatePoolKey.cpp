// cl: /DNDEBUG /MD /EHsc
// ?rva00036B89B@GiantBirdAIUpdate@@SA?AW4NameKeyType@@XZ @0x36b89b
// (69B): cached pool-name key for GiantBirdAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("GiantBirdAIUpdate"); the body guards a function-local static
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

class GiantBirdAIUpdate
{
public:
	static NameKeyType rva00036B89B();
};

// ?rva00036B89B@GiantBirdAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType GiantBirdAIUpdate::rva00036B89B()
{
	static NameKeyType TheGiantBirdAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("GiantBirdAIUpdate");
	return TheGiantBirdAIUpdatePoolKey;
}

