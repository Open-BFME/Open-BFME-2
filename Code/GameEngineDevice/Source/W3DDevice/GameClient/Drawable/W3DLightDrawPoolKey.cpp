// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DLightDraw@@UBE?AW4NameKeyType@@XZ @0xCFAF9
// (69B): cached pool-name key for W3DLightDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DLightDraw"); the body guards a function-local static
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

#include "../../../../Include/W3DDevice/GameClient/Module/W3DLightDraw.h"

// ?getModuleNameKey@W3DLightDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DLightDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DLightDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DLightDraw");
	return TheW3DLightDrawPoolKey;
}
