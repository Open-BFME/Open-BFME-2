// cl: /DNDEBUG /MD /EHsc
// ?rva00047A0E6@HordeGarrisonContain@@SA?AW4NameKeyType@@XZ @0x47A0E6
// (69B): cached pool-name key for HordeGarrisonContain. The class
// identity comes from the pool-name string the body pushes
// ("HordeGarrisonContain"); the body guards a function-local static
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

class HordeGarrisonContain
{
public:
	static NameKeyType rva00047A0E6();
};

// ?rva00047A0E6@HordeGarrisonContain@@SA?AW4NameKeyType@@XZ
NameKeyType HordeGarrisonContain::rva00047A0E6()
{
	static NameKeyType TheHordeGarrisonContainPoolKey =
		TheNameKeyGenerator->nameToKey("HordeGarrisonContain");
	return TheHordeGarrisonContainPoolKey;
}
