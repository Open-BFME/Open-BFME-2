// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000B21CF@W3DDefaultDraw@@SA?AW4NameKeyType@@XZ @0xB21CF
// (69B): cached pool-name key for W3DDefaultDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DDefaultDraw"); the body guards a function-local static
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

class W3DDefaultDraw
{
public:
	static NameKeyType rva0000B21CF();
};

// ?rva0000B21CF@W3DDefaultDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DDefaultDraw::rva0000B21CF()
{
	static NameKeyType TheW3DDefaultDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DDefaultDraw");
	return TheW3DDefaultDrawPoolKey;
}
