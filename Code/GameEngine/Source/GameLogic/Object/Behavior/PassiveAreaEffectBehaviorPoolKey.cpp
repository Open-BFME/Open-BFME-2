// cl: /DNDEBUG /MD /EHsc
// ?rva000484ADD@PassiveAreaEffectBehavior@@SA?AW4NameKeyType@@XZ @0x484add
// (69B): cached pool-name key for PassiveAreaEffectBehavior. The class
// identity comes from the pool-name string the body pushes
// ("PassiveAreaEffectBehavior"); the body guards a function-local static
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

class PassiveAreaEffectBehavior
{
public:
	static NameKeyType rva000484ADD();
};

// ?rva000484ADD@PassiveAreaEffectBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType PassiveAreaEffectBehavior::rva000484ADD()
{
	static NameKeyType ThePassiveAreaEffectBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("PassiveAreaEffectBehavior");
	return ThePassiveAreaEffectBehaviorPoolKey;
}

