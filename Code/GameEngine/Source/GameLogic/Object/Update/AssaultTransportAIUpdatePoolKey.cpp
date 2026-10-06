// cl: /DNDEBUG /MD /EHsc
// ?rva00048F411@AssaultTransportAIUpdate@@SA?AW4NameKeyType@@XZ @0x48f411
// (69B): cached pool-name key for AssaultTransportAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AssaultTransportAIUpdate"); the body guards a function-local static
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

class AssaultTransportAIUpdate
{
public:
	static NameKeyType rva00048F411();
};

// ?rva00048F411@AssaultTransportAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType AssaultTransportAIUpdate::rva00048F411()
{
	static NameKeyType TheAssaultTransportAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AssaultTransportAIUpdate");
	return TheAssaultTransportAIUpdatePoolKey;
}

