// cl: /DNDEBUG /MD /EHsc
// ?rva00048FFD4@LargeGroupBonusUpdate@@SA?AW4NameKeyType@@XZ @0x48ffd4
// (69B): cached pool-name key for LargeGroupBonusUpdate. The class
// identity comes from the pool-name string the body pushes
// ("LargeGroupBonusUpdate"); the body guards a function-local static
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

class LargeGroupBonusUpdate
{
public:
	static NameKeyType rva00048FFD4();
};

// ?rva00048FFD4@LargeGroupBonusUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType LargeGroupBonusUpdate::rva00048FFD4()
{
	static NameKeyType TheLargeGroupBonusUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("LargeGroupBonusUpdate");
	return TheLargeGroupBonusUpdatePoolKey;
}

