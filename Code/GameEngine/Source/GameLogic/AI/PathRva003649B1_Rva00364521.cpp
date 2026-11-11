// cl: /DNDEBUG /MD
// Split from PathRva003649B1.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ?rva003649B1@Path@@QAEXPBVPathNode@@@Z @0x003649B1 134B via Path append donor
// Evidence: duplicate-position guard via ucomiss on +0xc/+0x10 vs tail; pool g_pathNodePool allocate plus rowed PathNode ctor with arg+0xc/layer+0x18 plus waypoint+0x20; linking head+4 tail+8 optimized+0xc matches PathAppendNode.
#include <new>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003642DFNode;
#include "../../../Include/GameLogic/Rva003642DFResult.h"

#include "../../../Include/GameLogic/Rva0008BB38FloatField.h"

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../Include/GameLogic/Rva00065964ObjectPool.h"

// g_pathNodePool: matched references place it at VA 0xe01e94 (zero-filled; a plain-data view).
extern Rva00065964ObjectPool g_pathNodePool;

#include "../../../Include/GameLogic/PathfindPath.h"

Rva003642DFResult Path::rva00364521(const Rva0008BB38FloatField *arg)
{
	if (arg)
		return rva003642DF(arg->get());
	return rva003642DF(40.0f);
}

void *rva0026547E();

