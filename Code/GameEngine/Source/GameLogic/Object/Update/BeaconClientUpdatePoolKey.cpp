// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C9607@BeaconClientUpdate@@SA?AW4NameKeyType@@XZ @0x004C9607
// (69B): cached pool-name key for BeaconClientUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BeaconClientUpdate"); the body guards a function-local static
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

class BeaconClientUpdate
{
public:
	static NameKeyType rva004C9607();
};

// ?rva004C9607@BeaconClientUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType BeaconClientUpdate::rva004C9607()
{
	static NameKeyType TheBeaconClientUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BeaconClientUpdate");
	return TheBeaconClientUpdatePoolKey;
}
