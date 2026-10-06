// cl: /DNDEBUG /MD /EHsc
// ?rva00049E15E@ProductionUpdate@@SA?AW4NameKeyType@@XZ @0x49e15e
// (69B): cached pool-name key for ProductionUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ProductionUpdate"); the body guards a function-local static
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

class ProductionUpdate
{
public:
	static NameKeyType rva00049E15E();
};

// ?rva00049E15E@ProductionUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ProductionUpdate::rva00049E15E()
{
	static NameKeyType TheProductionUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ProductionUpdate");
	return TheProductionUpdatePoolKey;
}

