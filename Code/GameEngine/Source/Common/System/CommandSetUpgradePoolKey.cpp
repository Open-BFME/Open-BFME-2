// cl: /DNDEBUG /MD /EHsc
// ?rva0004B3A4B@CommandSetUpgrade@@SA?AW4NameKeyType@@XZ @0x4B3A4B
// (69B): cached pool-name key for CommandSetUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("CommandSetUpgrade"); the body guards a function-local static
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

class CommandSetUpgrade
{
public:
	static NameKeyType rva0004B3A4B();
};

// ?rva0004B3A4B@CommandSetUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType CommandSetUpgrade::rva0004B3A4B()
{
	static NameKeyType TheCommandSetUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("CommandSetUpgrade");
	return TheCommandSetUpgradePoolKey;
}
