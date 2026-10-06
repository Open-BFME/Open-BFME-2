// cl: /DNDEBUG /MD /EHsc
// ?rva00048D761@FloatUpdate@@SA?AW4NameKeyType@@XZ @0x48D761
// (69B): cached pool-name key for FloatUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FloatUpdate"); the body guards a function-local static
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

class FloatUpdate
{
public:
	static NameKeyType rva00048D761();
};

// ?rva00048D761@FloatUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType FloatUpdate::rva00048D761()
{
	static NameKeyType TheFloatUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FloatUpdate");
	return TheFloatUpdatePoolKey;
}
