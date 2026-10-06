// cl: /DNDEBUG /MD /EHsc
// ?rva0004BAE83@EvacuateDamage@@SA?AW4NameKeyType@@XZ @0x4BAE83
// (69B): cached pool-name key for EvacuateDamage. The class
// identity comes from the pool-name string the body pushes
// ("EvacuateDamage"); the body guards a function-local static
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

class EvacuateDamage
{
public:
	static NameKeyType rva0004BAE83();
};

// ?rva0004BAE83@EvacuateDamage@@SA?AW4NameKeyType@@XZ
NameKeyType EvacuateDamage::rva0004BAE83()
{
	static NameKeyType TheEvacuateDamagePoolKey =
		TheNameKeyGenerator->nameToKey("EvacuateDamage");
	return TheEvacuateDamagePoolKey;
}
