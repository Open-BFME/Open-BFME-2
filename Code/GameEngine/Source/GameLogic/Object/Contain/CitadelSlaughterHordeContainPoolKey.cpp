// cl: /DNDEBUG /MD /EHsc
// ?rva000480600@CitadelSlaughterHordeContain@@SA?AW4NameKeyType@@XZ @0x480600
// (69B): cached pool-name key for CitadelSlaughterHordeContain. The class
// identity comes from the pool-name string the body pushes
// ("CitadelSlaughterHordeContain"); the body guards a function-local static
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

class CitadelSlaughterHordeContain
{
public:
	static NameKeyType rva000480600();
};

// ?rva000480600@CitadelSlaughterHordeContain@@SA?AW4NameKeyType@@XZ
NameKeyType CitadelSlaughterHordeContain::rva000480600()
{
	static NameKeyType TheCitadelSlaughterHordeContainPoolKey =
		TheNameKeyGenerator->nameToKey("CitadelSlaughterHordeContain");
	return TheCitadelSlaughterHordeContainPoolKey;
}

