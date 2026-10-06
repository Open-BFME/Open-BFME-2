// cl: /DNDEBUG /MD /EHsc
// ?rva0004950B4@AutoFindHealingUpdate@@SA?AW4NameKeyType@@XZ @0x4950b4
// (69B): cached pool-name key for AutoFindHealingUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AutoFindHealingUpdate"); the body guards a function-local static
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

class AutoFindHealingUpdate
{
public:
	static NameKeyType rva0004950B4();
};

// ?rva0004950B4@AutoFindHealingUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType AutoFindHealingUpdate::rva0004950B4()
{
	static NameKeyType TheAutoFindHealingUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AutoFindHealingUpdate");
	return TheAutoFindHealingUpdatePoolKey;
}

