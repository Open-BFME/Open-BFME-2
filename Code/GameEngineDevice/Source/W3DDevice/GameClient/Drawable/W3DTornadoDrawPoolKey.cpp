// cl: /DNDEBUG /MD /EHsc
// ?rva000D1866@W3DTornadoDraw@@SA?AW4NameKeyType@@XZ @0xD1866
// (69B): cached pool-name key for W3DTornadoDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTornadoDraw"); the body guards a function-local static
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

class W3DTornadoDraw
{
public:
	static NameKeyType rva000D1866();
};

// ?rva000D1866@W3DTornadoDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DTornadoDraw::rva000D1866()
{
	static NameKeyType TheW3DTornadoDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTornadoDraw");
	return TheW3DTornadoDrawPoolKey;
}
