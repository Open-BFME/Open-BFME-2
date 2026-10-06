// cl: /DNDEBUG /MD /EHsc
// ?rva0004BB0EB@HordeTransportContainDamage@@SA?AW4NameKeyType@@XZ @0x4BB0EB
// (69B): cached pool-name key for HordeTransportContainDamage. The class
// identity comes from the pool-name string the body pushes
// ("HordeTransportContainDamage"); the body guards a function-local static
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

class HordeTransportContainDamage
{
public:
	static NameKeyType rva0004BB0EB();
};

// ?rva0004BB0EB@HordeTransportContainDamage@@SA?AW4NameKeyType@@XZ
NameKeyType HordeTransportContainDamage::rva0004BB0EB()
{
	static NameKeyType TheHordeTransportContainDamagePoolKey =
		TheNameKeyGenerator->nameToKey("HordeTransportContainDamage");
	return TheHordeTransportContainDamagePoolKey;
}
