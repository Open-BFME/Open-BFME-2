// cl: /DNDEBUG /MD /EHsc
// ?rva00048B690@FireSpreadUpdate@@SA?AW4NameKeyType@@XZ @0x48B690
// (69B): cached pool-name key for FireSpreadUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FireSpreadUpdate"); the body guards a function-local static
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

class FireSpreadUpdate
{
public:
	static NameKeyType rva00048B690();
};

// ?rva00048B690@FireSpreadUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType FireSpreadUpdate::rva00048B690()
{
	static NameKeyType TheFireSpreadUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FireSpreadUpdate");
	return TheFireSpreadUpdatePoolKey;
}
