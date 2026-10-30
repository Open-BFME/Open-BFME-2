// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
// ?getModuleNameKey@SiegeDockingBehavior@@UBE?AW4NameKeyType@@XZ @0x4599E5
// (69B): cached pool-name key for SiegeDockingBehavior. The class
// identity comes from the pool-name string the body pushes
// ("SiegeDockingBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

#include "SiegeDockingBehaviorView.h"

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@SiegeDockingBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeDockingBehavior::getModuleNameKey() const
{
	static NameKeyType TheSiegeDockingBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	return TheSiegeDockingBehaviorPoolKey;
}
