// cl: /DNDEBUG /MD /EHsc
// ?rva0026E93D@AIUpdateInterface@@SA?AW4NameKeyType@@XZ @0x26E93D
// (68B): cached pool-name key for AIUpdateInterface. The class
// identity comes from the pool-name string the body pushes
// ("AIUpdateInterface"); the body guards a function-local static
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

class AIUpdateInterface
{
public:
	static NameKeyType rva0026E93D();
};

// ?rva0026E93D@AIUpdateInterface@@SA?AW4NameKeyType@@XZ
NameKeyType AIUpdateInterface::rva0026E93D()
{
	static NameKeyType TheAIUpdateInterfacePoolKey =
		TheNameKeyGenerator->nameToKey("AIUpdateInterface");
	return TheAIUpdateInterfacePoolKey;
}
