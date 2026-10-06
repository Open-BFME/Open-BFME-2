// cl: /DNDEBUG /MD /EHsc
// ?rva0004DF351@ObjectGuardingHelper@@SA?AW4NameKeyType@@XZ @0x4DF351
// (69B): cached pool-name key for ObjectGuardingHelper. The class
// identity comes from the pool-name string the body pushes
// ("ObjectGuardingHelper"); the body guards a function-local static
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

class ObjectGuardingHelper
{
public:
	static NameKeyType rva0004DF351();
};

// ?rva0004DF351@ObjectGuardingHelper@@SA?AW4NameKeyType@@XZ
NameKeyType ObjectGuardingHelper::rva0004DF351()
{
	static NameKeyType TheObjectGuardingHelperPoolKey =
		TheNameKeyGenerator->nameToKey("ObjectGuardingHelper");
	return TheObjectGuardingHelperPoolKey;
}
