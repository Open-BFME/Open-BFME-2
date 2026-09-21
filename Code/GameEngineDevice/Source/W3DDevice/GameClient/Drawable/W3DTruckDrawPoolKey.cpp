// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0000CB578@W3DTruckDraw@@SA?AW4NameKeyType@@XZ @0xCB578
// (69B): cached pool-name key for W3DTruckDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTruckDraw"); the body guards a function-local static
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

class W3DTruckDraw
{
public:
	static NameKeyType rva0000CB578();
};

// ?rva0000CB578@W3DTruckDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DTruckDraw::rva0000CB578()
{
	static NameKeyType TheW3DTruckDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTruckDraw");
	return TheW3DTruckDrawPoolKey;
}
