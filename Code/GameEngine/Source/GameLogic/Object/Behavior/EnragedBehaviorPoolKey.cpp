// cl: /DNDEBUG /MD /EHsc
// ?rva000459002@EnragedBehavior@@SA?AW4NameKeyType@@XZ @0x459002
// (69B): cached pool-name key for EnragedBehavior. The class
// identity comes from the pool-name string the body pushes
// ("EnragedBehavior"); the body guards a function-local static
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

class EnragedBehavior
{
public:
	static NameKeyType rva000459002();
};

// ?rva000459002@EnragedBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType EnragedBehavior::rva000459002()
{
	static NameKeyType TheEnragedBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("EnragedBehavior");
	return TheEnragedBehaviorPoolKey;
}
