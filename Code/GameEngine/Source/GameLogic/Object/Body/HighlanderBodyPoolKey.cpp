// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C07CA@HighlanderBody@@SA?AW4NameKeyType@@XZ @0x004C07CA
// (69B): cached pool-name key for HighlanderBody. The class
// identity comes from the pool-name string the body pushes
// ("HighlanderBody"); the body guards a function-local static
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

class HighlanderBody
{
public:
	static NameKeyType rva004C07CA();
};

// ?rva004C07CA@HighlanderBody@@SA?AW4NameKeyType@@XZ
NameKeyType HighlanderBody::rva004C07CA()
{
	static NameKeyType TheHighlanderBodyPoolKey =
		TheNameKeyGenerator->nameToKey("HighlanderBody");
	return TheHighlanderBodyPoolKey;
}
