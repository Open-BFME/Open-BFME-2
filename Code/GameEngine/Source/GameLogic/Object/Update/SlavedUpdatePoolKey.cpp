// cl: /DNDEBUG /MD /EHsc
// ?rva0004A1875@SlavedUpdate@@SA?AW4NameKeyType@@XZ @0x4a1875
// (69B): cached pool-name key for SlavedUpdate. The class
// identity comes from the pool-name string the body pushes
// ("SlavedUpdate"); the body guards a function-local static
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

class SlavedUpdate
{
public:
	static NameKeyType rva0004A1875();
};

// ?rva0004A1875@SlavedUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType SlavedUpdate::rva0004A1875()
{
	static NameKeyType TheSlavedUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("SlavedUpdate");
	return TheSlavedUpdatePoolKey;
}

