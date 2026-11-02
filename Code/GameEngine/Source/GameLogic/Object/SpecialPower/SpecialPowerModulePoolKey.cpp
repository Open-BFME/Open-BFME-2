// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@SpecialPowerModule@@UBE?AW4NameKeyType@@XZ @0x493daa
// (69B): cached pool-name key for SpecialPowerModule. The class
// identity comes from the pool-name string the body pushes
// ("SpecialPowerModule"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class SpecialPowerModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpecialPowerModule@@UBE?AW4NameKeyType@@XZ
NameKeyType SpecialPowerModule::getModuleNameKey() const
{
	static NameKeyType TheSpecialPowerModulePoolKey =
		TheNameKeyGenerator->nameToKey("SpecialPowerModule");
	return TheSpecialPowerModulePoolKey;
}

