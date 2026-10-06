// cl: /DNDEBUG /MD /EHsc
// ?rva000CEEE6@W3DPropDraw@@SA?AW4NameKeyType@@XZ @0xCEEE6
// (69B): cached pool-name key for W3DPropDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DPropDraw"); the body guards a function-local static
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

class W3DPropDraw
{
public:
	static NameKeyType rva000CEEE6();
};

// ?rva000CEEE6@W3DPropDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DPropDraw::rva000CEEE6()
{
	static NameKeyType TheW3DPropDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DPropDraw");
	return TheW3DPropDrawPoolKey;
}
