// cl: /DNDEBUG /MD /EHsc
// ?rva0004BAB55@ReflectDamage@@SA?AW4NameKeyType@@XZ @0x4BAB55
// (69B): cached pool-name key for ReflectDamage. The class
// identity comes from the pool-name string the body pushes
// ("ReflectDamage"); the body guards a function-local static
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

class ReflectDamage
{
public:
	static NameKeyType rva0004BAB55();
};

// ?rva0004BAB55@ReflectDamage@@SA?AW4NameKeyType@@XZ
NameKeyType ReflectDamage::rva0004BAB55()
{
	static NameKeyType TheReflectDamagePoolKey =
		TheNameKeyGenerator->nameToKey("ReflectDamage");
	return TheReflectDamagePoolKey;
}
