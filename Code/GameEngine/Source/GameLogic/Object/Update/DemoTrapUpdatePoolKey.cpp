// cl: /DNDEBUG /MD /EHsc
// ?rva000495935@DemoTrapUpdate@@SA?AW4NameKeyType@@XZ @0x495935
// (69B): cached pool-name key for DemoTrapUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DemoTrapUpdate"); the body guards a function-local static
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

class DemoTrapUpdate
{
public:
	static NameKeyType rva000495935();
};

// ?rva000495935@DemoTrapUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType DemoTrapUpdate::rva000495935()
{
	static NameKeyType TheDemoTrapUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DemoTrapUpdate");
	return TheDemoTrapUpdatePoolKey;
}

