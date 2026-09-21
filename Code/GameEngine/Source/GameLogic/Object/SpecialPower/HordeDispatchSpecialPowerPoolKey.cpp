// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C8A34@HordeDispatchSpecialPower@@SA?AW4NameKeyType@@XZ @0x004C8A34
// (69B): cached pool-name key for HordeDispatchSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("HordeDispatchSpecialPower"); the body guards a function-local static
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

class HordeDispatchSpecialPower
{
public:
	static NameKeyType rva004C8A34();
};

// ?rva004C8A34@HordeDispatchSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType HordeDispatchSpecialPower::rva004C8A34()
{
	static NameKeyType TheHordeDispatchSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("HordeDispatchSpecialPower");
	return TheHordeDispatchSpecialPowerPoolKey;
}
