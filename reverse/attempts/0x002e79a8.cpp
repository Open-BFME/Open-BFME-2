// ?Rva002E79A8CellToWorld@@YAPAUCoord3D@@PAU1@_NHHH@Z
// partial score=0.974624 date=2026-10-10
// ?Rva002E79A8CellToWorld@@YAPAUCoord3D@@PAU1@_NHHH@Z
// partial score=0.974624 date=2026-10-10
// ?Rva002E79A8CellToWorld@@YAPAUCoord3D@@PAU1@_NHHH@Z
// partial score=0.974624 date=2026-10-10
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// ?Rva002E79A8CellToWorld@@YAPAUCoord3D@@PAU1@_NHHH@Z @0x002E79A8 186B
// Cell-to-world converter beside Pathfinder clamp callers 0x002E7B29 0x002E7BF0 0x002E7ED6.
// Scale 10.0 at 0xBC2428, half 0.5 at 0xBC26F0, corner at 0xBC7838. Layer 1 (ground)
// tries TerrainLogic slot 0x4c water check then falls back to slot 0x1c getLayerHeight.

#include "../../Code/Libraries/Include/Lib/Coord3D.h"

class TerrainLogic
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual float s06(float x, float y, int dummy);
	virtual float getLayerHeight(float x, float y, int layer, void *normal, int clip);
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual bool waterCheck(float x, float y, float *a, float *b, bool *c);
};

#define TheTerrainLogic (*(TerrainLogic **)0x00DFEC50)
#define CellScale (*(const float *)0x00BC2428)
#define CellHalf (*(const float *)0x00BC26F0)
#define CellBase (*(const float *)0x00BC7838)

Coord3D *__cdecl Rva002E79A8CellToWorld(Coord3D *out, bool center, int cellX, int cellY, int layer)
{
Coord3D position;
float scale=CellScale;
float offset=CellHalf;
if(!center) offset=CellBase;
position.x=((float)cellX+offset)*scale;
position.y=((float)cellY+offset)*scale;
if(layer!=1 || !TheTerrainLogic->waterCheck(position.x,position.y,&position.z,0,0))
position.z=TheTerrainLogic->getLayerHeight(position.x,position.y,layer,0,1);
out->x=position.x;out->y=position.y;out->z=position.z;
return out;
}
