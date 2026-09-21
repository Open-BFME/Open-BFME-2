// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000CA0CE@W3DQuadrupedDraw@@SA?AW4NameKeyType@@XZ @0xCA0CE
// (69B): cached pool-name key for W3DQuadrupedDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DQuadrupedDraw"); the body guards a function-local static
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

class W3DQuadrupedDraw
{
public:
	static NameKeyType rva0000CA0CE();
};

// ?rva0000CA0CE@W3DQuadrupedDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DQuadrupedDraw::rva0000CA0CE()
{
	static NameKeyType TheW3DQuadrupedDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DQuadrupedDraw");
	return TheW3DQuadrupedDrawPoolKey;
}
