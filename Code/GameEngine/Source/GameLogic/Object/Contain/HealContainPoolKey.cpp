// cl: /DNDEBUG /MD /EHsc
// ?rva000466B88@HealContain@@SA?AW4NameKeyType@@XZ @0x466b88
// (69B): cached pool-name key for HealContain. The class
// identity comes from the pool-name string the body pushes
// ("HealContain"); the body guards a function-local static
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

class HealContain
{
public:
	static NameKeyType rva000466B88();
};

// ?rva000466B88@HealContain@@SA?AW4NameKeyType@@XZ
NameKeyType HealContain::rva000466B88()
{
	static NameKeyType TheHealContainPoolKey =
		TheNameKeyGenerator->nameToKey("HealContain");
	return TheHealContainPoolKey;
}

