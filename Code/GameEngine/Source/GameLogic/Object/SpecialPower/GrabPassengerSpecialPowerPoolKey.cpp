// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004C4FCE@GrabPassengerSpecialPower@@SA?AW4NameKeyType@@XZ @0x004C4FCE
// (69B): cached pool-name key for GrabPassengerSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("GrabPassengerSpecialPower"); the body guards a function-local static
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

class GrabPassengerSpecialPower
{
public:
	static NameKeyType rva004C4FCE();
};

// ?rva004C4FCE@GrabPassengerSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType GrabPassengerSpecialPower::rva004C4FCE()
{
	static NameKeyType TheGrabPassengerSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("GrabPassengerSpecialPower");
	return TheGrabPassengerSpecialPowerPoolKey;
}
