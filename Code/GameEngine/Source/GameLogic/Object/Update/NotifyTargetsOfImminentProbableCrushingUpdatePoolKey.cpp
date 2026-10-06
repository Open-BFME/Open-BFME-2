// cl: /DNDEBUG /MD /EHsc
// ?rva000253E8E@NotifyTargetsOfImminentProbableCrushingUpdate@@SA?AW4NameKeyType@@XZ @0x253E8E
// (69B): cached pool-name key for NotifyTargetsOfImminentProbableCrushingUpdate.
// The class identity comes from the pool-name string the body pushes
// ("NotifyTargetsOfImminentProbableCrushingUpdate"); the body guards a
// function-local static key fetched once through TheNameKeyGenerator. It is NOT
// getClassMemoryPool: retail stores nameToKey's return (a key, not a pool
// pointer) and returns it, and the address carries no getClassMemoryPool row
// anywhere. /EHsc for the static-guard EH prologue; globals are TU-local
// externs (DIR32 slots patch from retail, no pins; nameToKey resolves via its
// matched row).

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

class NotifyTargetsOfImminentProbableCrushingUpdate
{
public:
	static NameKeyType rva000253E8E();
};

// ?rva000253E8E@NotifyTargetsOfImminentProbableCrushingUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType NotifyTargetsOfImminentProbableCrushingUpdate::rva000253E8E()
{
	static NameKeyType TheNotifyTargetsOfImminentProbableCrushingUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("NotifyTargetsOfImminentProbableCrushingUpdate");
	return TheNotifyTargetsOfImminentProbableCrushingUpdatePoolKey;
}
