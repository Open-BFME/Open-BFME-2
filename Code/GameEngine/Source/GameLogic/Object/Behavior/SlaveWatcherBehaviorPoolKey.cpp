// cl: /DNDEBUG /MD /EHsc
// ?rva00048462E@SlaveWatcherBehavior@@SA?AW4NameKeyType@@XZ @0x48462e
// (69B): cached pool-name key for SlaveWatcherBehavior. The class
// identity comes from the pool-name string the body pushes
// ("SlaveWatcherBehavior"); the body guards a function-local static
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

class SlaveWatcherBehavior
{
public:
	static NameKeyType rva00048462E();
};

// ?rva00048462E@SlaveWatcherBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType SlaveWatcherBehavior::rva00048462E()
{
	static NameKeyType TheSlaveWatcherBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	return TheSlaveWatcherBehaviorPoolKey;
}

