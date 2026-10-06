// cl: /DNDEBUG /MD /EHsc
// ?rva000486A2F@SpecialPowerCompletionDie@@SA?AW4NameKeyType@@XZ @0x486a2f
// (69B): cached pool-name key for SpecialPowerCompletionDie. The class
// identity comes from the pool-name string the body pushes
// ("SpecialPowerCompletionDie"); the body guards a function-local static
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

class SpecialPowerCompletionDie
{
public:
	static NameKeyType rva000486A2F();
};

// ?rva000486A2F@SpecialPowerCompletionDie@@SA?AW4NameKeyType@@XZ
NameKeyType SpecialPowerCompletionDie::rva000486A2F()
{
	static NameKeyType TheSpecialPowerCompletionDiePoolKey =
		TheNameKeyGenerator->nameToKey("SpecialPowerCompletionDie");
	return TheSpecialPowerCompletionDiePoolKey;
}

