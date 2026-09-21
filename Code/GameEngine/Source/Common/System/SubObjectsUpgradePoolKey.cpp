// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004B4D1E@SubObjectsUpgrade@@SA?AW4NameKeyType@@XZ @0x4b4d1e
// (69B): cached pool-name key for SubObjectsUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("SubObjectsUpgrade"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row). The 69B
// tail is fused after an unrowed forwarder head (0x4B4D05 pushing through a
// vtable slot then tail-jumping to 0x58B03E); the C3 pad at 0x4B4D1D is the
// clean boundary. Recipe: StatusBitsUpgradePoolKey.cpp.

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

class SubObjectsUpgrade
{
public:
	static NameKeyType rva0004B4D1E();
};

// ?rva0004B4D1E@SubObjectsUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType SubObjectsUpgrade::rva0004B4D1E()
{
	static NameKeyType TheSubObjectsUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("SubObjectsUpgrade");
	return TheSubObjectsUpgradePoolKey;
}
