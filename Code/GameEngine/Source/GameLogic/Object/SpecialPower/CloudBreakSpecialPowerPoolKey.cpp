// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004C4521@CloudBreakSpecialPower@@SA?AW4NameKeyType@@XZ @0x4C4521
// (69B): cached pool-name key for CloudBreakSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("CloudBreakSpecialPower"); the body guards a function-local static
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

class CloudBreakSpecialPower
{
public:
	static NameKeyType rva0004C4521();
};

// ?rva0004C4521@CloudBreakSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType CloudBreakSpecialPower::rva0004C4521()
{
	static NameKeyType TheCloudBreakSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("CloudBreakSpecialPower");
	return TheCloudBreakSpecialPowerPoolKey;
}
