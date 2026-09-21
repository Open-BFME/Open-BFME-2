// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000C1201@W3DScriptedModelDraw@@SA?AW4NameKeyType@@XZ @0xC1201
// (69B): cached pool-name key for W3DScriptedModelDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DScriptedModelDraw"); the body guards a function-local static
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

class W3DScriptedModelDraw
{
public:
	static NameKeyType rva0000C1201();
};

// ?rva0000C1201@W3DScriptedModelDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DScriptedModelDraw::rva0000C1201()
{
	static NameKeyType TheW3DScriptedModelDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DScriptedModelDraw");
	return TheW3DScriptedModelDrawPoolKey;
}
