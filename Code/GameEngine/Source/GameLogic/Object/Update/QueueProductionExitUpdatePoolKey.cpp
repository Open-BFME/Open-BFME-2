// cl: /DNDEBUG /MD /EHsc
// ?rva0004A00C2@QueueProductionExitUpdate@@SA?AW4NameKeyType@@XZ @0x4a00c2
// (69B): cached pool-name key for QueueProductionExitUpdate. The class
// identity comes from the pool-name string the body pushes
// ("QueueProductionExitUpdate"); the body guards a function-local static
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

class QueueProductionExitUpdate
{
public:
	static NameKeyType rva0004A00C2();
};

// ?rva0004A00C2@QueueProductionExitUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType QueueProductionExitUpdate::rva0004A00C2()
{
	static NameKeyType TheQueueProductionExitUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("QueueProductionExitUpdate");
	return TheQueueProductionExitUpdatePoolKey;
}

