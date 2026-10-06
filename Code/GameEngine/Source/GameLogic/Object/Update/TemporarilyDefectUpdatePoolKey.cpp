// cl: /DNDEBUG /MD /EHsc
// ?rva0004CC659@TemporarilyDefectUpdate@@SA?AW4NameKeyType@@XZ @0x4CC659
// (69B): cached pool-name key for TemporarilyDefectUpdate. The class
// identity comes from the pool-name string the body pushes
// ("TemporarilyDefectUpdate"); the body guards a function-local static
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

class TemporarilyDefectUpdate
{
public:
	static NameKeyType rva0004CC659();
};

// ?rva0004CC659@TemporarilyDefectUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType TemporarilyDefectUpdate::rva0004CC659()
{
	static NameKeyType TheTemporarilyDefectUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");
	return TheTemporarilyDefectUpdatePoolKey;
}
