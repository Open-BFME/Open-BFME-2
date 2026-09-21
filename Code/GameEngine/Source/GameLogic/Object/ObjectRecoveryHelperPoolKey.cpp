// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva000028CA4D@ObjectRecoveryHelper@@SA?AW4NameKeyType@@XZ @0x28CA4D
// (69B): cached pool-name key for ObjectRecoveryHelper. The class
// identity comes from the pool-name string the body pushes
// ("ObjectRecoveryHelper"); the body guards a function-local static
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

class ObjectRecoveryHelper
{
public:
	static NameKeyType rva000028CA4D();
};

// ?rva000028CA4D@ObjectRecoveryHelper@@SA?AW4NameKeyType@@XZ
NameKeyType ObjectRecoveryHelper::rva000028CA4D()
{
	static NameKeyType TheObjectRecoveryHelperPoolKey =
		TheNameKeyGenerator->nameToKey("ObjectRecoveryHelper");
	return TheObjectRecoveryHelperPoolKey;
}
