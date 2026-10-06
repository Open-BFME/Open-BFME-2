// cl: /DNDEBUG /MD /EHsc
// ?rva0004A34C6@BroadcastStealthUpdate@@SA?AW4NameKeyType@@XZ @0x4A34C6
// (69B): cached pool-name key for BroadcastStealthUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BroadcastStealthUpdate"); the body guards a function-local static
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

class BroadcastStealthUpdate
{
public:
	static NameKeyType rva0004A34C6();
};

// ?rva0004A34C6@BroadcastStealthUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType BroadcastStealthUpdate::rva0004A34C6()
{
	static NameKeyType TheBroadcastStealthUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BroadcastStealthUpdate");
	return TheBroadcastStealthUpdatePoolKey;
}
