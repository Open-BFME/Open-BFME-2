// cl: /DNDEBUG /MD /EHsc
// ?rva004A5511@StructureToppleUpdate@@SA?AW4NameKeyType@@XZ @0x4A5511
// (68B): cached pool-name key for StructureToppleUpdate. The class
// identity comes from the pool-name string the body pushes
// ("StructureToppleUpdate"); the body guards a function-local static
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

class StructureToppleUpdate
{
public:
	static NameKeyType rva004A5511();
};

// ?rva004A5511@StructureToppleUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType StructureToppleUpdate::rva004A5511()
{
	static NameKeyType TheStructureToppleUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("StructureToppleUpdate");
	return TheStructureToppleUpdatePoolKey;
}
