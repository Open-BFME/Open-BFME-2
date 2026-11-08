// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ?setActiveBoundary@TerrainLogic@@QAEXH@Z,
// retail 0x0028069E, 220 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Map/TerrainLogic_setActiveBoundary_Thunk.cpp,
// TerrainLogic::setActiveBoundary, 183B): guard on the boundary index, skip
// when unchanged or degenerate, publish one Region3D through getExtent, then
// refresh Radar, the partition side and the shroud side, walk every Object,
// and recalculate the camera. Battle for Middle-earth 2 keeps that skeleton
// (same guard order, same getExtent/newMap/setRegion calls) and adds one more
// region consumer: the grid allocator at 0x35A2DC, fed the region plus the
// float at [0xDFE758]+0xD4. The object walk reads its head through the matched
// GameLogic::getFirstObject row (0x23CAD2) and follows next links at
// Object+0x8C; the camera recalculation rides View slot +0x1B8.

#include <vector>

typedef float Real;
typedef int Int;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
#define PARTITIONMANAGER_VIEW_REGION_FACADES
#include "../../Common/PartitionRangeQueryCallView.h"

typedef _STL::vector<ICoord2D> BoundaryVector;

class Object;
class TerrainLogic;

// Battle for Middle-earth's TerrainLogic vtable puts getExtent at slot 8
// (+0x20). Battle for Middle-earth 2 carries the boundary vector at +0x30
// (begin +0x30, end +0x34, 8-byte ICoord2D elements) with the active index at
// +0x3C, all measured from the retail body.
#include "../../../Include/GameLogic/TerrainLogic.h"

// The target calls Radar slot 6 (+0x18) with TheTerrainLogic.
#include "../../../Include/Common/Radar.h"

// ThePartitionManager and TheShroudManager use the canonical PartitionManager
// view (PartitionRangeQueryCallView.h): rva00625300 is the +0x10 region
// facade (0x00625300), setRegion the shroud region thunk (0x00739740).

// Grid allocator behind [GameLogic+0x170]: consumes the active region plus a
// float (here [0xDFE758]+0xD4; the 0x2440xx/0x246Exx init paths pass +0xD8).
// Large SEH body (region math, cell-grid new[]); identity unproven, so both
// the class and the method keep the address token.
class Rva0035A2DC
{
public:
	void rva0035A2DC(Region3D *region, Real value);
};

// Global object at 0xDFE758 (floats at +0xD4/+0xD8, dword consumer at +0xBD0
// in the 0x2440xx init path); identity unproven, opaque holder.
class Rva00DFE758Holder
{
public:
	unsigned char m_pad[0xD4];
	Real m_floatD4; // +0xD4
	Real m_floatD8; // +0xD8
};

#include "../Object/object.h"

// Battle for Middle-earth View vtable slot +0x1B8 is
// forceCameraConstraintRecalc (the reference build has it at +0x1B4; the
// retail call here reads +0x1B8). The 110 preceding entries are deliberately
// unnamed: only this slot is consumed.
template <int N> class __declspec(novtable) ViewSlots : public ViewSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class __declspec(novtable) ViewSlots<0> {};
#include "../../../Include/GameClient/View.h"

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern class GlobalData *TheWritableGlobalData;
// Matched DIR32 sites establish TheTerrainLogic at VA 0x00DFEC50. This is in
// the PE .data zero-fill tail, so the retail startup value is null.
TerrainLogic *TheTerrainLogic = 0;
extern GameLogic *TheGameLogic;
extern View *TheTacticalView;

// ?setActiveBoundary@TerrainLogic@@QAEXH@Z
void TerrainLogic::setActiveBoundary(Int newActiveBoundary)
{
	if (newActiveBoundary < 0 ||
		newActiveBoundary >= field30.size())
		return;

	if (newActiveBoundary == field3C)
		return;

	if (field30[newActiveBoundary].x == 0 ||
		field30[newActiveBoundary].y == 0)
		return;

	Region3D region;
	field3C = newActiveBoundary;
	getExtent(&region);
	TheRadar->vslot06(TheTerrainLogic);
	ThePartitionManager->rva00625300(&region);
	TheShroudManager->setRegion(&region, 0.0f);
	((Rva0035A2DC *)TheGameLogic->getTerrainResourceManager())->rva0035A2DC(&region, (*(Rva00DFE758Holder **)&TheWritableGlobalData)->m_floatD4);

	Object *object = TheGameLogic->getFirstObject();
	while (object != 0)
	{
		object->friend_notifyOfNewMapBoundary();
		object = *(Object **)((char *)object + 0x8C);
	}

	TheTacticalView->forceCameraConstraintRecalc();
}
