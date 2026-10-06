// cl: /DNDEBUG /MD /EHsc
// ?rva000CF161@W3DFloorDraw@@SA?AW4NameKeyType@@XZ @0xCF161
// (69B): cached pool-name key for W3DFloorDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DFloorDraw"); the body guards a function-local static
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

class W3DFloorDraw
{
public:
	static NameKeyType rva000CF161();
};

// ?rva000CF161@W3DFloorDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DFloorDraw::rva000CF161()
{
	static NameKeyType TheW3DFloorDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DFloorDraw");
	return TheW3DFloorDrawPoolKey;
}
