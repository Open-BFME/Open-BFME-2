// cl: /DNDEBUG /MD /EHsc
// ?rva000487A19@BoneFXUpdate@@SA?AW4NameKeyType@@XZ @0x487a19
// (69B): cached pool-name key for BoneFXUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BoneFXUpdate"); the body guards a function-local static
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

class BoneFXUpdate
{
public:
	static NameKeyType rva000487A19();
};

// ?rva000487A19@BoneFXUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType BoneFXUpdate::rva000487A19()
{
	static NameKeyType TheBoneFXUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BoneFXUpdate");
	return TheBoneFXUpdatePoolKey;
}

