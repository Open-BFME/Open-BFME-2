// cl: /DNDEBUG /MD /EHsc
// ?rva00048FC30@HeightDieUpdate@@SA?AW4NameKeyType@@XZ @0x48fc30
// (69B): cached pool-name key for HeightDieUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HeightDieUpdate"); the body guards a function-local static
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

class HeightDieUpdate
{
public:
	static NameKeyType rva00048FC30();
};

// ?rva00048FC30@HeightDieUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HeightDieUpdate::rva00048FC30()
{
	static NameKeyType TheHeightDieUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HeightDieUpdate");
	return TheHeightDieUpdatePoolKey;
}

