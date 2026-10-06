// cl: /DNDEBUG /MD /EHsc
// ?rva0004966B9@BoredUpdate@@SA?AW4NameKeyType@@XZ @0x4966b9
// (69B): cached pool-name key for BoredUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BoredUpdate"); the body guards a function-local static
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

class BoredUpdate
{
public:
	static NameKeyType rva0004966B9();
};

// ?rva0004966B9@BoredUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType BoredUpdate::rva0004966B9()
{
	static NameKeyType TheBoredUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BoredUpdate");
	return TheBoredUpdatePoolKey;
}

