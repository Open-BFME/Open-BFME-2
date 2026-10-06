// cl: /DNDEBUG /MD /EHsc
// ?rva000CE9EE@W3DTankDraw@@SA?AW4NameKeyType@@XZ @0xCE9EE
// (69B): cached pool-name key for W3DTankDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTankDraw"); the body guards a function-local static
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

class W3DTankDraw
{
public:
	static NameKeyType rva000CE9EE();
};

// ?rva000CE9EE@W3DTankDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DTankDraw::rva000CE9EE()
{
	static NameKeyType TheW3DTankDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTankDraw");
	return TheW3DTankDrawPoolKey;
}
