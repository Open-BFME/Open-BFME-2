// cl: /DNDEBUG /MD /EHsc
// ?rva000485A2F@CreateObjectDieIfEldestKindof@@SA?AW4NameKeyType@@XZ @0x485A2F
// (69B): cached pool-name key for CreateObjectDieIfEldestKindof. The class
// identity comes from the pool-name string the body pushes
// ("CreateObjectDieIfEldestKindof"); the body guards a function-local static
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

class CreateObjectDieIfEldestKindof
{
public:
	static NameKeyType rva000485A2F();
};

// ?rva000485A2F@CreateObjectDieIfEldestKindof@@SA?AW4NameKeyType@@XZ
NameKeyType CreateObjectDieIfEldestKindof::rva000485A2F()
{
	static NameKeyType TheCreateObjectDieIfEldestKindofPoolKey =
		TheNameKeyGenerator->nameToKey("CreateObjectDieIfEldestKindof");
	return TheCreateObjectDieIfEldestKindofPoolKey;
}
