// cl: /DNDEBUG /MD /EHsc
// ?rva0004BF848@ActiveBody@@SA?AW4NameKeyType@@XZ @0x4BF848
// (69B): cached pool-name key for ActiveBody. The class
// identity comes from the pool-name string the body pushes
// ("ActiveBody"); the body guards a function-local static
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

class ActiveBody
{
public:
	static NameKeyType rva0004BF848();
};

// ?rva0004BF848@ActiveBody@@SA?AW4NameKeyType@@XZ
NameKeyType ActiveBody::rva0004BF848()
{
	static NameKeyType TheActiveBodyPoolKey =
		TheNameKeyGenerator->nameToKey("ActiveBody");
	return TheActiveBodyPoolKey;
}
