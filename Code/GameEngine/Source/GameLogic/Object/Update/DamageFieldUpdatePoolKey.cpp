// cl: /DNDEBUG /MD /EHsc
// ?rva000491264@DamageFieldUpdate@@SA?AW4NameKeyType@@XZ @0x491264
// (69B): cached pool-name key for DamageFieldUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DamageFieldUpdate"); the body guards a function-local static
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

class DamageFieldUpdate
{
public:
	static NameKeyType rva000491264();
};

// ?rva000491264@DamageFieldUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType DamageFieldUpdate::rva000491264()
{
	static NameKeyType TheDamageFieldUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DamageFieldUpdate");
	return TheDamageFieldUpdatePoolKey;
}
