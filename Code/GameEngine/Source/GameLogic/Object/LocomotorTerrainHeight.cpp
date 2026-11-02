// ?Rva001E40D9Get@@YGMMM@Z
// cl: /O1 /MD /arch:SSE
//
// ?Rva001E40D9Get@@YGMMM@Z @0x001E40D9 89B
// __stdcall terrain height at x,y via TheTerrainLogic: try isUnderwater (slot 0x4c) with out
// local then return it else getGroundHeight (slot 0x18); original helper name unresolved; callers 0x001E811F 0x001E8351 in 0x001E7ECA.
#include "../../../Include/GameLogic/TerrainLogic.h"
float __stdcall Rva001E40D9Get(float x, float y)
{
	float out;
	if (TheTerrainLogic->isUnderwater(x, y, &out, 0, 0))
	{
        // Preserve the native SSE copy to the parameter home before its x87 load.
        y = TheTerrainLogic != 0 ? *(volatile float *)&out : *(volatile float *)&out;
        return y;
	}
	return TheTerrainLogic->getGroundHeight(x, y, 0);
}
