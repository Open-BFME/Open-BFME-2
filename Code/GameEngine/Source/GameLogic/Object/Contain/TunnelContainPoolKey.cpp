// cl: /DNDEBUG /MD /EHsc
// ?rva00047DB43@TunnelContain@@SA?AW4NameKeyType@@XZ @0x47db43
// (69B): cached pool-name key for TunnelContain. The class
// identity comes from the pool-name string the body pushes
// ("TunnelContain"); the body guards a function-local static
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

class TunnelContain
{
public:
	static NameKeyType rva00047DB43();
};

// ?rva00047DB43@TunnelContain@@SA?AW4NameKeyType@@XZ
NameKeyType TunnelContain::rva00047DB43()
{
	static NameKeyType TheTunnelContainPoolKey =
		TheNameKeyGenerator->nameToKey("TunnelContain");
	return TheTunnelContainPoolKey;
}

