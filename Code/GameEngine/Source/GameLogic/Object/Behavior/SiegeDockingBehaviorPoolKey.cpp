// cl: /DNDEBUG /MD /EHsc
// ?rva0004599E5@SiegeDockingBehavior@@SA?AW4NameKeyType@@XZ @0x4599E5
// (69B): cached pool-name key for SiegeDockingBehavior. The class
// identity comes from the pool-name string the body pushes
// ("SiegeDockingBehavior"); the body guards a function-local static
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

class SiegeDockingBehavior
{
public:
	static NameKeyType rva0004599E5();
};

// ?rva0004599E5@SiegeDockingBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType SiegeDockingBehavior::rva0004599E5()
{
	static NameKeyType TheSiegeDockingBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	return TheSiegeDockingBehaviorPoolKey;
}
