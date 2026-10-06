// cl: /DNDEBUG /MD /EHsc
// ?rva00049FE9A@ProneUpdate@@SA?AW4NameKeyType@@XZ @0x49FE9A
// (69B): cached pool-name key for ProneUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ProneUpdate"); the body guards a function-local static
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

class ProneUpdate
{
public:
	static NameKeyType rva00049FE9A();
};

// ?rva00049FE9A@ProneUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ProneUpdate::rva00049FE9A()
{
	static NameKeyType TheProneUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ProneUpdate");
	return TheProneUpdatePoolKey;
}
