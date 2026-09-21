// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B79E9@TooltipUpgrade@@SA?AW4NameKeyType@@XZ @0x004B79E9
// (69B): cached pool-name key for TooltipUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("TooltipUpgrade"); the body guards a function-local static
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

class TooltipUpgrade
{
public:
	static NameKeyType rva004B79E9();
};

// ?rva004B79E9@TooltipUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType TooltipUpgrade::rva004B79E9()
{
	static NameKeyType TheTooltipUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("TooltipUpgrade");
	return TheTooltipUpgradePoolKey;
}
