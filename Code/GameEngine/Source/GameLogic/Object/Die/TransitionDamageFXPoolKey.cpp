// cl: /DNDEBUG /MD /EHsc
// ?rva0004BA437@TransitionDamageFX@@SA?AW4NameKeyType@@XZ @0x4BA437
// (69B): cached pool-name key for TransitionDamageFX. The class
// identity comes from the pool-name string the body pushes
// ("TransitionDamageFX"); the body guards a function-local static
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

class TransitionDamageFX
{
public:
	static NameKeyType rva0004BA437();
};

// ?rva0004BA437@TransitionDamageFX@@SA?AW4NameKeyType@@XZ
NameKeyType TransitionDamageFX::rva0004BA437()
{
	static NameKeyType TheTransitionDamageFXPoolKey =
		TheNameKeyGenerator->nameToKey("TransitionDamageFX");
	return TheTransitionDamageFXPoolKey;
}
