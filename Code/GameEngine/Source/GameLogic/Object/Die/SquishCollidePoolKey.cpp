// cl: /DNDEBUG /MD /EHsc
// ?rva0004BB98A@SquishCollide@@SA?AW4NameKeyType@@XZ @0x4BB98A
// (69B): cached pool-name key for SquishCollide. The class
// identity comes from the pool-name string the body pushes
// ("SquishCollide"); the body guards a function-local static
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

class SquishCollide
{
public:
	static NameKeyType rva0004BB98A();
};

// ?rva0004BB98A@SquishCollide@@SA?AW4NameKeyType@@XZ
NameKeyType SquishCollide::rva0004BB98A()
{
	static NameKeyType TheSquishCollidePoolKey =
		TheNameKeyGenerator->nameToKey("SquishCollide");
	return TheSquishCollidePoolKey;
}
