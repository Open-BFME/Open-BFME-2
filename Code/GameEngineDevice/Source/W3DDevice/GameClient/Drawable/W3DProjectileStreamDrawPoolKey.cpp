// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000D140A@W3DProjectileStreamDraw@@SA?AW4NameKeyType@@XZ @0xD140A
// (69B): cached pool-name key for W3DProjectileStreamDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DProjectileStreamDraw"); the body guards a function-local static
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

class W3DProjectileStreamDraw
{
public:
	static NameKeyType rva0000D140A();
};

// ?rva0000D140A@W3DProjectileStreamDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DProjectileStreamDraw::rva0000D140A()
{
	static NameKeyType TheW3DProjectileStreamDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DProjectileStreamDraw");
	return TheW3DProjectileStreamDrawPoolKey;
}
