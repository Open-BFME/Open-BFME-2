// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000CAE7B@W3DSupplyDraw@@SA?AW4NameKeyType@@XZ @0xCAE7B
// (69B): cached pool-name key for W3DSupplyDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DSupplyDraw"); the body guards a function-local static
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

class W3DSupplyDraw
{
public:
	static NameKeyType rva0000CAE7B();
};

// ?rva0000CAE7B@W3DSupplyDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DSupplyDraw::rva0000CAE7B()
{
	static NameKeyType TheW3DSupplyDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DSupplyDraw");
	return TheW3DSupplyDrawPoolKey;
}
