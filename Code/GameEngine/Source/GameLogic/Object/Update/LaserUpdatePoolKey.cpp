// cl: /DNDEBUG /MD /EHsc
// ?rva000363102@LaserUpdate@@SA?AW4NameKeyType@@XZ @0x363102
// (69B): cached pool-name key for LaserUpdate. The class
// identity comes from the pool-name string the body pushes
// ("LaserUpdate"); the body guards a function-local static
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

class LaserUpdate
{
public:
	static NameKeyType rva000363102();
};

// ?rva000363102@LaserUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType LaserUpdate::rva000363102()
{
	static NameKeyType TheLaserUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("LaserUpdate");
	return TheLaserUpdatePoolKey;
}
