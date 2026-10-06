// cl: /DNDEBUG /MD /EHsc
// ?rva000D004C@W3DStreakDraw@@SA?AW4NameKeyType@@XZ @0xD004C
// (69B): cached pool-name key for W3DStreakDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DStreakDraw"); the body guards a function-local static
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

class W3DStreakDraw
{
public:
	static NameKeyType rva000D004C();
};

// ?rva000D004C@W3DStreakDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DStreakDraw::rva000D004C()
{
	static NameKeyType TheW3DStreakDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DStreakDraw");
	return TheW3DStreakDrawPoolKey;
}
