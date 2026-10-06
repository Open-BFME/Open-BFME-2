// cl: /DNDEBUG /MD /EHsc
// ?rva004A9B06@WorkerAIUpdate@@SA?AW4NameKeyType@@XZ @0x4A9B06
// (68B): cached pool-name key for WorkerAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("WorkerAIUpdate"); the body guards a function-local static
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

class WorkerAIUpdate
{
public:
	static NameKeyType rva004A9B06();
};

// ?rva004A9B06@WorkerAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType WorkerAIUpdate::rva004A9B06()
{
	static NameKeyType TheWorkerAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("WorkerAIUpdate");
	return TheWorkerAIUpdatePoolKey;
}
