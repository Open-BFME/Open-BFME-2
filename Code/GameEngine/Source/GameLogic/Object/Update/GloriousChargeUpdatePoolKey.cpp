// cl: /DNDEBUG /MD /EHsc
// ?rva0004AD5CE@GloriousChargeUpdate@@SA?AW4NameKeyType@@XZ @0x4AD5CE
// (69B): cached pool-name key for GloriousChargeUpdate. The class
// identity comes from the pool-name string the body pushes
// ("GloriousChargeUpdate"); the body guards a function-local static
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

class GloriousChargeUpdate
{
public:
	static NameKeyType rva0004AD5CE();
};

// ?rva0004AD5CE@GloriousChargeUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType GloriousChargeUpdate::rva0004AD5CE()
{
	static NameKeyType TheGloriousChargeUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("GloriousChargeUpdate");
	return TheGloriousChargeUpdatePoolKey;
}
