// cl: /DNDEBUG /MD /EHsc
// ?rva000496A1E@BannerCarrierUpdate@@SA?AW4NameKeyType@@XZ @0x496a1e
// (69B): cached pool-name key for BannerCarrierUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BannerCarrierUpdate"); the body guards a function-local static
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

class BannerCarrierUpdate
{
public:
	static NameKeyType rva000496A1E();
};

// ?rva000496A1E@BannerCarrierUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType BannerCarrierUpdate::rva000496A1E()
{
	static NameKeyType TheBannerCarrierUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BannerCarrierUpdate");
	return TheBannerCarrierUpdatePoolKey;
}

