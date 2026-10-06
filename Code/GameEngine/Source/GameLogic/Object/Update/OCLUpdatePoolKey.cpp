// cl: /DNDEBUG /MD /EHsc
// ?rva00049B310@OCLUpdate@@SA?AW4NameKeyType@@XZ @0x49B310
// (69B): cached pool-name key for OCLUpdate. The class
// identity comes from the pool-name string the body pushes
// ("OCLUpdate"); the body guards a function-local static
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

class OCLUpdate
{
public:
	static NameKeyType rva00049B310();
};

// ?rva00049B310@OCLUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType OCLUpdate::rva00049B310()
{
	static NameKeyType TheOCLUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("OCLUpdate");
	return TheOCLUpdatePoolKey;
}
