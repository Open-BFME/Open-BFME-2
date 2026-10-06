// cl: /DNDEBUG /MD /EHsc
// ?rva00048C25E@OilSpillUpdate@@SA?AW4NameKeyType@@XZ @0x48c25e
// (69B): cached pool-name key for OilSpillUpdate. The class
// identity comes from the pool-name string the body pushes
// ("OilSpillUpdate"); the body guards a function-local static
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

class OilSpillUpdate
{
public:
	static NameKeyType rva00048C25E();
};

// ?rva00048C25E@OilSpillUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType OilSpillUpdate::rva00048C25E()
{
	static NameKeyType TheOilSpillUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("OilSpillUpdate");
	return TheOilSpillUpdatePoolKey;
}

