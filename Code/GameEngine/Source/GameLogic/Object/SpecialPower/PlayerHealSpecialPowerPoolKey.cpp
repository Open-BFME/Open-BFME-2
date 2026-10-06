// cl: /DNDEBUG /MD /EHsc
// ?rva0004C7EFB@PlayerHealSpecialPower@@SA?AW4NameKeyType@@XZ @0x4C7EFB
// (69B): cached pool-name key for PlayerHealSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("PlayerHealSpecialPower"); the body guards a function-local static
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

class PlayerHealSpecialPower
{
public:
	static NameKeyType rva0004C7EFB();
};

// ?rva0004C7EFB@PlayerHealSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType PlayerHealSpecialPower::rva0004C7EFB()
{
	static NameKeyType ThePlayerHealSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("PlayerHealSpecialPower");
	return ThePlayerHealSpecialPowerPoolKey;
}
