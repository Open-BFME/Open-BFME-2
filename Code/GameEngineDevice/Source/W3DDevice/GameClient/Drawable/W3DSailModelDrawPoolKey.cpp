// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000D07CB@W3DSailModelDraw@@SA?AW4NameKeyType@@XZ @0xD07CB
// (69B): cached pool-name key for W3DSailModelDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DSailModelDraw"); the body guards a function-local static
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

class W3DSailModelDraw
{
public:
	static NameKeyType rva0000D07CB();
};

// ?rva0000D07CB@W3DSailModelDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DSailModelDraw::rva0000D07CB()
{
	static NameKeyType TheW3DSailModelDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DSailModelDraw");
	return TheW3DSailModelDrawPoolKey;
}
