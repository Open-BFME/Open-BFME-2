// cl: /DNDEBUG /MD /EHsc
// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ @0xCA7F6
// (68B): cached pool-name key for W3DRopeDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DRopeDraw"); the body guards a function-local static
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

class W3DRopeDraw
{
public:
	static NameKeyType rva000CA7F6();
};

// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DRopeDraw::rva000CA7F6()
{
	static NameKeyType TheW3DRopeDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DRopeDraw");
	return TheW3DRopeDrawPoolKey;
}
