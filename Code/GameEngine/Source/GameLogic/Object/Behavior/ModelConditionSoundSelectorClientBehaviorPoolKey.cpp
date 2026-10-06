// cl: /DNDEBUG /MD /EHsc
// ?rva000254BAC@ModelConditionSoundSelectorClientBehavior@@SA?AW4NameKeyType@@XZ @0x254BAC
// (69B): cached pool-name key for ModelConditionSoundSelectorClientBehavior. The class
// identity comes from the pool-name string the body pushes
// ("ModelConditionSoundSelectorClientBehavior"); the body guards a function-local static
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

class ModelConditionSoundSelectorClientBehavior
{
public:
	static NameKeyType rva000254BAC();
};

// ?rva000254BAC@ModelConditionSoundSelectorClientBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType ModelConditionSoundSelectorClientBehavior::rva000254BAC()
{
	static NameKeyType TheModelConditionSoundSelectorClientBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("ModelConditionSoundSelectorClientBehavior");
	return TheModelConditionSoundSelectorClientBehaviorPoolKey;
}
