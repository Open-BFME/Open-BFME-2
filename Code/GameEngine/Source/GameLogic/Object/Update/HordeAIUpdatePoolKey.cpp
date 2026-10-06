// cl: /DNDEBUG /MD /EHsc
// ?rva00049A67C@HordeAIUpdate@@SA?AW4NameKeyType@@XZ @0x49a67c
// (69B): cached pool-name key for HordeAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HordeAIUpdate"); the body guards a function-local static
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

class HordeAIUpdate
{
public:
	static NameKeyType rva00049A67C();
};

// ?rva00049A67C@HordeAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HordeAIUpdate::rva00049A67C()
{
	static NameKeyType TheHordeAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HordeAIUpdate");
	return TheHordeAIUpdatePoolKey;
}

