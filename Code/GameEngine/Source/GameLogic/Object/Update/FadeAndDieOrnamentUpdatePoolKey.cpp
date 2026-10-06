// cl: /DNDEBUG /MD /EHsc
// ?rva0003A4358@FadeAndDieOrnamentUpdate@@SA?AW4NameKeyType@@XZ @0x3a4358
// (69B): cached pool-name key for FadeAndDieOrnamentUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FadeAndDieOrnamentUpdate"); the body guards a function-local static
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

class FadeAndDieOrnamentUpdate
{
public:
	static NameKeyType rva0003A4358();
};

// ?rva0003A4358@FadeAndDieOrnamentUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType FadeAndDieOrnamentUpdate::rva0003A4358()
{
	static NameKeyType TheFadeAndDieOrnamentUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FadeAndDieOrnamentUpdate");
	return TheFadeAndDieOrnamentUpdatePoolKey;
}

