// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C08B7@ImmortalBody@@SA?AW4NameKeyType@@XZ @0x004C08B7
// (69B): cached pool-name key for ImmortalBody. The class
// identity comes from the pool-name string the body pushes
// ("ImmortalBody"); the body guards a function-local static
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

class ImmortalBody
{
public:
	static NameKeyType rva004C08B7();
};

// ?rva004C08B7@ImmortalBody@@SA?AW4NameKeyType@@XZ
NameKeyType ImmortalBody::rva004C08B7()
{
	static NameKeyType TheImmortalBodyPoolKey =
		TheNameKeyGenerator->nameToKey("ImmortalBody");
	return TheImmortalBodyPoolKey;
}
