// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C6C7C@FellBeastSwoopPower@@SA?AW4NameKeyType@@XZ @0x4C6C7C
// (69B): cached pool-name key for FellBeastSwoopPower. The class
// identity comes from the pool-name string the body pushes
// ("FellBeastSwoopPower"); the body guards a function-local static
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

class FellBeastSwoopPower
{
public:
	static NameKeyType rva004C6C7C();
};

// ?rva004C6C7C@FellBeastSwoopPower@@SA?AW4NameKeyType@@XZ
NameKeyType FellBeastSwoopPower::rva004C6C7C()
{
	static NameKeyType TheFellBeastSwoopPowerPoolKey =
		TheNameKeyGenerator->nameToKey("FellBeastSwoopPower");
	return TheFellBeastSwoopPowerPoolKey;
}
