// cl: /DNDEBUG /MD /EHsc
// ?rva0003955DA@CastleBehavior@@SA?AW4NameKeyType@@XZ @0x3955DA
// (69B): second cached pool-name key for CastleBehavior (retail holds two
// function-local statics over the same "CastleBehavior" string; the landed
// 0x398538 body guards 0xE02818, this one guards 0xE027CC). It is NOT
// getClassMemoryPool: retail stores nameToKey's return (a key, not a pool
// pointer) and returns it. /EHsc for the static-guard EH prologue; globals
// are TU-local externs (DIR32 slots patch from retail, no pins; nameToKey
// resolves via its matched row).

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

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

// ?rva0003955DA@CastleBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType CastleBehavior::rva0003955DA()
{
	static NameKeyType TheCastleBehaviorPoolKey2 =
		TheNameKeyGenerator->nameToKey("CastleBehavior");
	return TheCastleBehaviorPoolKey2;
}
