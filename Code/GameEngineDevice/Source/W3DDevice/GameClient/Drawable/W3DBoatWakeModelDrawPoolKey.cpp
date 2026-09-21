// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000D0C93@W3DBoatWakeModelDraw@@SA?AW4NameKeyType@@XZ @0xD0C93
// (69B): cached pool-name key for W3DBoatWakeModelDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DBoatWakeModelDraw"); the body guards a function-local static
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

class W3DBoatWakeModelDraw
{
public:
	static NameKeyType rva0000D0C93();
};

// ?rva0000D0C93@W3DBoatWakeModelDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DBoatWakeModelDraw::rva0000D0C93()
{
	static NameKeyType TheW3DBoatWakeModelDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DBoatWakeModelDraw");
	return TheW3DBoatWakeModelDrawPoolKey;
}
