// cl: /DNDEBUG /MD /EHsc
// ?rva00048E8AC@DeployStyleAIUpdate@@SA?AW4NameKeyType@@XZ @0x48E8AC
// (69B): cached pool-name key for DeployStyleAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DeployStyleAIUpdate"); the body guards a function-local static
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

class DeployStyleAIUpdate
{
public:
	static NameKeyType rva00048E8AC();
};

// ?rva00048E8AC@DeployStyleAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType DeployStyleAIUpdate::rva00048E8AC()
{
	static NameKeyType TheDeployStyleAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DeployStyleAIUpdate");
	return TheDeployStyleAIUpdatePoolKey;
}
