// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva000078B38@W3DHordeModelDraw@@SA?AW4NameKeyType@@XZ @0x78B38
// (69B): cached pool-name key for W3DHordeModelDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DHordeModelDraw"); the body guards a function-local static
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

class W3DHordeModelDraw
{
public:
	static NameKeyType rva000078B38();
};

// ?rva000078B38@W3DHordeModelDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DHordeModelDraw::rva000078B38()
{
	static NameKeyType TheW3DHordeModelDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DHordeModelDraw");
	return TheW3DHordeModelDrawPoolKey;
}
