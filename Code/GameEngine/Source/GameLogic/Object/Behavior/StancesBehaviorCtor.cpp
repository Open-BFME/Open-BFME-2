// cl: /DNDEBUG /MD
//
// ??0StancesBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045EF80, 54 bytes.
// Behavior-side ctor completing the StancesBehavior file-unit (poolkey rowed at
// 0x45EFBC; proc rowed at 0x45ED8C; ModuleData factory rowed at 0x24B3B4;
// instance factory rowed at 0x24B37C news 0x34 with this pinned 2-arg ctor).
//
// Retail shape: UpdateModule base (rowed 0x253390) + member at +0x20 via the
// pinned 0x330757 ctor + trailing zero at +0x30 + primary vtable 0xC424DC +
// secondaries 0xBEFF90/+0x0C and 0xC424D0/+0x10. The +0x20 member spans 0x10
// bytes (next explicit store is +0x30); its 23B body (Vector_base 0x211E58 +
// or -1 at +0x0C) fits a vector plus flag word.

#include "../../../../Include/GameLogic/StancesBehavior.h"

// ??0StancesBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045EF80
StancesBehavior::StancesBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_stance = 0;
}
