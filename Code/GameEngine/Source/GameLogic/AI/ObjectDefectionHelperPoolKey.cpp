// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@ObjectDefectionHelper@@UBE?AW4NameKeyType@@XZ @0x28C992
// (69B): cached pool-name key for ObjectDefectionHelper. The class
// identity comes from the pool-name string the body pushes
// ("ObjectDefectionHelper"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class ObjectDefectionHelper
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ObjectDefectionHelper@@UBE?AW4NameKeyType@@XZ
NameKeyType ObjectDefectionHelper::getModuleNameKey() const
{
	static NameKeyType TheObjectDefectionHelperPoolKey =
		TheNameKeyGenerator->nameToKey("ObjectDefectionHelper");
	return TheObjectDefectionHelperPoolKey;
}
