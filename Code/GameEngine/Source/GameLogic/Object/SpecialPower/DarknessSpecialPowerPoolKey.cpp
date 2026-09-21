// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004C4E02@DarknessSpecialPower@@SA?AW4NameKeyType@@XZ @0x4C4E02
// (69B): cached pool-name key for DarknessSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("DarknessSpecialPower"); the body guards a function-local static
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

class DarknessSpecialPower
{
public:
	static NameKeyType rva0004C4E02();
};

// ?rva0004C4E02@DarknessSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType DarknessSpecialPower::rva0004C4E02()
{
	static NameKeyType TheDarknessSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("DarknessSpecialPower");
	return TheDarknessSpecialPowerPoolKey;
}
