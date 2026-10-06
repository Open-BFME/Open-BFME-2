// cl: /DNDEBUG /MD /EHsc
// ?rva0004A4010@HijackerUpdate@@SA?AW4NameKeyType@@XZ @0x4a4010
// (69B): cached pool-name key for HijackerUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HijackerUpdate"); the body guards a function-local static
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

class HijackerUpdate
{
public:
	static NameKeyType rva0004A4010();
};

// ?rva0004A4010@HijackerUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HijackerUpdate::rva0004A4010()
{
	static NameKeyType TheHijackerUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HijackerUpdate");
	return TheHijackerUpdatePoolKey;
}

