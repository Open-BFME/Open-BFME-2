// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DTruckDraw@@UBE?AW4NameKeyType@@XZ @0xCB578
// (69B): cached pool-name key for W3DTruckDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTruckDraw"); the body guards a function-local static
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

class W3DTruckDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DTruckDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DTruckDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DTruckDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTruckDraw");
	return TheW3DTruckDrawPoolKey;
}
