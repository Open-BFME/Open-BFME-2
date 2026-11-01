// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DDebrisDraw@@UBE?AW4NameKeyType@@XZ @0xB1C97
// (69B): cached pool-name key for W3DDebrisDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DDebrisDraw"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../../GameEngine/Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class W3DDebrisDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DDebrisDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DDebrisDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DDebrisDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DDebrisDraw");
	return TheW3DDebrisDrawPoolKey;
}
