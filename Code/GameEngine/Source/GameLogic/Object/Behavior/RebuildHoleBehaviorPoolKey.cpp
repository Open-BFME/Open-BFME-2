// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@RebuildHoleBehavior@@UBE?AW4NameKeyType@@XZ @0x4832d7
// (69B): cached pool-name key for RebuildHoleBehavior. The class
// identity comes from the pool-name string the body pushes
// ("RebuildHoleBehavior"); the body guards a function-local static
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

class ModuleData;
class Object;

// newWorkerRespawnProcess's callees: the module data's worker respawn delay
// (+0x08), TheGameLogic's destroyObject, the Object mask/status/selection
// members and TheAI's pathfinder (+0x10).
struct RebuildHoleBehaviorModuleData
{
	unsigned char m_pad00[0x8];
	float m_workerRespawnDelay;				// +0x08
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// The 128-bit status mask the rowed 0x00391F4E builds from bit indices.
class Rva00346BC0;
struct Rva00391F4E
{
	Rva00391F4E(int bit0, int bit1, int bit2);		// 0x00391F4E
	unsigned int m_bits[4];
};

#include "../object.h"

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"

extern AI *TheAI;

#include "../../../../Include/GameLogic/Module/RebuildHoleBehaviorClass.h"

// ?getModuleNameKey@RebuildHoleBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType RebuildHoleBehavior::getModuleNameKey() const
{
	static NameKeyType TheRebuildHoleBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("RebuildHoleBehavior");
	return TheRebuildHoleBehaviorPoolKey;
}

// RebuildHoleBehavior::newWorkerRespawnProcess, retail 0x0048337A (114
// bytes): Zero Hour's RebuildHoleBehavior.cpp body (WB names it): any
// existing worker is destroyed, the respawn wait restarts from the module
// data and the hole is unmasked. BFME 2 then clears three status bits
// (0, 3, 0x3C), makes the hole selectable and puts it back on the pathfind
// map. Unlike the class's SSE units this body converts with x87 _ftol2.
void RebuildHoleBehavior::newWorkerRespawnProcess(Object *existingWorker)
{
	const RebuildHoleBehaviorModuleData *modData = (const RebuildHoleBehaviorModuleData *)m_moduleData;
	Object *hole = m_object;

	// if we have an existing worker, get rid of it
	if (existingWorker)
		TheGameLogic->destroyObject(existingWorker);
	m_workerID = INVALID_OBJECT_ID;

	// set the timer for the next worker respawn
	m_workerWaitCounter = (unsigned int)modData->m_workerRespawnDelay;

	hole->maskObject(false);
	hole->rva0028CDEB((const Rva00346BC0 &)Rva00391F4E(0, 3, 0x3c), false);
	hole->setSelectable(true);
	TheAI->m_pathfinder->AddObjectToPathfindMap(hole);
}
