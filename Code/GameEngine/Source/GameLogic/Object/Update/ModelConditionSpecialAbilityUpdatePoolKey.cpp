// cl: /DNDEBUG /MD /EHsc
// ?rva000490D96@ModelConditionSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ @0x490d96
// (69B): cached pool-name key for ModelConditionSpecialAbilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ModelConditionSpecialAbilityUpdate"); the body guards a function-local static
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

class ModelConditionSpecialAbilityUpdate
{
public:
	static NameKeyType rva000490D96();
};

// ?rva000490D96@ModelConditionSpecialAbilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ModelConditionSpecialAbilityUpdate::rva000490D96()
{
	static NameKeyType TheModelConditionSpecialAbilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ModelConditionSpecialAbilityUpdate");
	return TheModelConditionSpecialAbilityUpdatePoolKey;
}

