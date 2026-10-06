// cl: /DNDEBUG /MD /EHsc
// ?rva0004A812E@ToppleUpdate@@SA?AW4NameKeyType@@XZ @0x4A812E
// (69B): cached pool-name key for ToppleUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ToppleUpdate"); the body guards a function-local static
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

class ToppleUpdate
{
public:
	static NameKeyType rva0004A812E();
};

// ?rva0004A812E@ToppleUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ToppleUpdate::rva0004A812E()
{
	static NameKeyType TheToppleUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ToppleUpdate");
	return TheToppleUpdatePoolKey;
}
