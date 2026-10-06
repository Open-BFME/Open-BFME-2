// cl: /DNDEBUG /MD /EHsc
// ?rva000483CF4@ClearanceTestingSlowDeathBehavior@@SA?AW4NameKeyType@@XZ @0x483cf4
// (69B): cached pool-name key for ClearanceTestingSlowDeathBehavior. The class
// identity comes from the pool-name string the body pushes
// ("ClearanceTestingSlowDeathBehavior"); the body guards a function-local static
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

class ClearanceTestingSlowDeathBehavior
{
public:
	static NameKeyType rva000483CF4();
};

// ?rva000483CF4@ClearanceTestingSlowDeathBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType ClearanceTestingSlowDeathBehavior::rva000483CF4()
{
	static NameKeyType TheClearanceTestingSlowDeathBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("ClearanceTestingSlowDeathBehavior");
	return TheClearanceTestingSlowDeathBehaviorPoolKey;
}

