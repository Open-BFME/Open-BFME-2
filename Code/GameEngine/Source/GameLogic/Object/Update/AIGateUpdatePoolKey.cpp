// cl: /DNDEBUG /MD /EHsc
// ?rva0004B087C@AIGateUpdate@@SA?AW4NameKeyType@@XZ @0x4B087C
// (69B): cached pool-name key for AIGateUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AIGateUpdate"); the body guards a function-local static
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

class AIGateUpdate
{
public:
	static NameKeyType rva0004B087C();
};

// ?rva0004B087C@AIGateUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType AIGateUpdate::rva0004B087C()
{
	static NameKeyType TheAIGateUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AIGateUpdate");
	return TheAIGateUpdatePoolKey;
}
