// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DTornadoDraw@@UBE?AW4NameKeyType@@XZ @0xD1866
// (69B): cached pool-name key for W3DTornadoDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTornadoDraw"); the body guards a function-local static
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

class W3DTornadoDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DTornadoDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DTornadoDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DTornadoDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTornadoDraw");
	return TheW3DTornadoDrawPoolKey;
}
