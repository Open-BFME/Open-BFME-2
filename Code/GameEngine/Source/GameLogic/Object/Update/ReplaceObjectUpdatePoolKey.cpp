// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B29FF@ReplaceObjectUpdate@@SA?AW4NameKeyType@@XZ @0x4B29FF
// (69B): cached pool-name key for ReplaceObjectUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ReplaceObjectUpdate"); the body guards a function-local static
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

class ReplaceObjectUpdate
{
public:
	static NameKeyType rva004B29FF();
};

// ?rva004B29FF@ReplaceObjectUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ReplaceObjectUpdate::rva004B29FF()
{
	static NameKeyType TheReplaceObjectUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ReplaceObjectUpdate");
	return TheReplaceObjectUpdatePoolKey;
}
