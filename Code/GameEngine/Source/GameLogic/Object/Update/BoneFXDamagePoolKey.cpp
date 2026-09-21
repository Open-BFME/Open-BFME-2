// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B9757@BoneFXDamage@@SA?AW4NameKeyType@@XZ @0x004B9757
// (69B): cached pool-name key for BoneFXDamage. The class
// identity comes from the pool-name string the body pushes
// ("BoneFXDamage"); the body guards a function-local static
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

class BoneFXDamage
{
public:
	static NameKeyType rva004B9757();
};

// ?rva004B9757@BoneFXDamage@@SA?AW4NameKeyType@@XZ
NameKeyType BoneFXDamage::rva004B9757()
{
	static NameKeyType TheBoneFXDamagePoolKey =
		TheNameKeyGenerator->nameToKey("BoneFXDamage");
	return TheBoneFXDamagePoolKey;
}
