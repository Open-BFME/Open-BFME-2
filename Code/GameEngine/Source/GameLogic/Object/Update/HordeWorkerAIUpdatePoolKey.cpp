// cl: /DNDEBUG /MD /EHsc
// ?rva00049ACD0@HordeWorkerAIUpdate@@SA?AW4NameKeyType@@XZ @0x49acd0
// (69B): cached pool-name key for HordeWorkerAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HordeWorkerAIUpdate"); the body guards a function-local static
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

class HordeWorkerAIUpdate
{
public:
	static NameKeyType rva00049ACD0();
};

// ?rva00049ACD0@HordeWorkerAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HordeWorkerAIUpdate::rva00049ACD0()
{
	static NameKeyType TheHordeWorkerAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HordeWorkerAIUpdate");
	return TheHordeWorkerAIUpdatePoolKey;
}

