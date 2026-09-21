// cl: /O1 /DNDEBUG /MD /EHsc
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

struct ICoord2D
{
	Int x;
	Int y;
};

struct Region3D
{
	Real lo[3];
	Real hi[3];
};

typedef _STL::vector<ICoord2D> BoundaryVector;

class Object;
class TerrainLogic;

// Battle for Middle-earth's TerrainLogic vtable puts getExtent at slot 8
// (+0x20). Battle for Middle-earth 2 carries the boundary vector at +0x30
// (begin +0x30, end +0x34, 8-byte ICoord2D elements) with the active index at
// +0x3C, all measured from the retail body.
class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void getExtent(Region3D *extent) const = 0;

	void setActiveBoundary(Int newActiveBoundary);

private:
	char m_unmodelled04[0x2C];
	BoundaryVector m_boundaries; // +0x30
	Int m_activeBoundary; // +0x3C
};

// The target calls Radar::newMap through vtable slot 6 (+0x18).
class __declspec(novtable) Radar
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void newMap(TerrainLogic *terrain);
};

class PartitionManager
{
public:
	// 0x625300: 8-byte this-adjusting thunk (mov ecx,[ecx+0x10], jmp 0x6276E0),
	// the first region call in this body and in the 0x246Dxx init path; the
	// Battle for Middle-earth reference routes the same call through its
	// partition facade, so the class is PartitionManager while the method
	// itself keeps its address token.
	void rva00625300(const Region3D *region);
	void setRegion(const Region3D *region, Real value);
};

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

class GameLogic
{
public:
	Object *getFirstObject();

public:
	// Padding is retail-measured only at the two consumed offsets (+0xAC in
	// the matched getFirstObject TU, +0x170 here); the member name is opaque.
	unsigned char m_pad[0x170];
	Rva0035A2DC *m_opaque170; // +0x170
};

class Object
{
public:
	void friend_notifyOfNewMapBoundary();
};

// Battle for Middle-earth View vtable slot +0x1B8 is
// forceCameraConstraintRecalc (the reference build has it at +0x1B4; the
// retail call here reads +0x1B8). The 110 preceding entries are deliberately
// unnamed: only this slot is consumed.
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
class __declspec(novtable) View
{
public:
	BFME_VIEW_SLOT(000) BFME_VIEW_SLOT(001) BFME_VIEW_SLOT(002) BFME_VIEW_SLOT(003)
	BFME_VIEW_SLOT(004) BFME_VIEW_SLOT(005) BFME_VIEW_SLOT(006) BFME_VIEW_SLOT(007)
	BFME_VIEW_SLOT(008) BFME_VIEW_SLOT(009) BFME_VIEW_SLOT(010) BFME_VIEW_SLOT(011)
	BFME_VIEW_SLOT(012) BFME_VIEW_SLOT(013) BFME_VIEW_SLOT(014) BFME_VIEW_SLOT(015)
	BFME_VIEW_SLOT(016) BFME_VIEW_SLOT(017) BFME_VIEW_SLOT(018) BFME_VIEW_SLOT(019)
	BFME_VIEW_SLOT(020) BFME_VIEW_SLOT(021) BFME_VIEW_SLOT(022) BFME_VIEW_SLOT(023)
	BFME_VIEW_SLOT(024) BFME_VIEW_SLOT(025) BFME_VIEW_SLOT(026) BFME_VIEW_SLOT(027)
	BFME_VIEW_SLOT(028) BFME_VIEW_SLOT(029) BFME_VIEW_SLOT(030) BFME_VIEW_SLOT(031)
	BFME_VIEW_SLOT(032) BFME_VIEW_SLOT(033) BFME_VIEW_SLOT(034) BFME_VIEW_SLOT(035)
	BFME_VIEW_SLOT(036) BFME_VIEW_SLOT(037) BFME_VIEW_SLOT(038) BFME_VIEW_SLOT(039)
	BFME_VIEW_SLOT(040) BFME_VIEW_SLOT(041) BFME_VIEW_SLOT(042) BFME_VIEW_SLOT(043)
	BFME_VIEW_SLOT(044) BFME_VIEW_SLOT(045) BFME_VIEW_SLOT(046) BFME_VIEW_SLOT(047)
	BFME_VIEW_SLOT(048) BFME_VIEW_SLOT(049) BFME_VIEW_SLOT(050) BFME_VIEW_SLOT(051)
	BFME_VIEW_SLOT(052) BFME_VIEW_SLOT(053) BFME_VIEW_SLOT(054) BFME_VIEW_SLOT(055)
	BFME_VIEW_SLOT(056) BFME_VIEW_SLOT(057) BFME_VIEW_SLOT(058) BFME_VIEW_SLOT(059)
	BFME_VIEW_SLOT(060) BFME_VIEW_SLOT(061) BFME_VIEW_SLOT(062) BFME_VIEW_SLOT(063)
	BFME_VIEW_SLOT(064) BFME_VIEW_SLOT(065) BFME_VIEW_SLOT(066) BFME_VIEW_SLOT(067)
	BFME_VIEW_SLOT(068) BFME_VIEW_SLOT(069) BFME_VIEW_SLOT(070) BFME_VIEW_SLOT(071)
	BFME_VIEW_SLOT(072) BFME_VIEW_SLOT(073) BFME_VIEW_SLOT(074) BFME_VIEW_SLOT(075)
	BFME_VIEW_SLOT(076) BFME_VIEW_SLOT(077) BFME_VIEW_SLOT(078) BFME_VIEW_SLOT(079)
	BFME_VIEW_SLOT(080) BFME_VIEW_SLOT(081) BFME_VIEW_SLOT(082) BFME_VIEW_SLOT(083)
	BFME_VIEW_SLOT(084) BFME_VIEW_SLOT(085) BFME_VIEW_SLOT(086) BFME_VIEW_SLOT(087)
	BFME_VIEW_SLOT(088) BFME_VIEW_SLOT(089) BFME_VIEW_SLOT(090) BFME_VIEW_SLOT(091)
	BFME_VIEW_SLOT(092) BFME_VIEW_SLOT(093) BFME_VIEW_SLOT(094) BFME_VIEW_SLOT(095)
	BFME_VIEW_SLOT(096) BFME_VIEW_SLOT(097) BFME_VIEW_SLOT(098) BFME_VIEW_SLOT(099)
	BFME_VIEW_SLOT(100) BFME_VIEW_SLOT(101) BFME_VIEW_SLOT(102) BFME_VIEW_SLOT(103)
	BFME_VIEW_SLOT(104) BFME_VIEW_SLOT(105) BFME_VIEW_SLOT(106) BFME_VIEW_SLOT(107)
	BFME_VIEW_SLOT(108) BFME_VIEW_SLOT(109)
	virtual void forceCameraConstraintRecalc() = 0;
};
#undef BFME_VIEW_SLOT

extern Radar *TheRadar;
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern Rva00DFE758Holder *TheRva00DFE758;
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern View *TheTacticalView;

// ?setActiveBoundary@TerrainLogic@@QAEXH@Z
void TerrainLogic::setActiveBoundary(Int newActiveBoundary)
{
	if (newActiveBoundary < 0 ||
		newActiveBoundary >= m_boundaries.size())
		return;

	if (newActiveBoundary == m_activeBoundary)
		return;

	if (m_boundaries[newActiveBoundary].x == 0 ||
		m_boundaries[newActiveBoundary].y == 0)
		return;

	Region3D region;
	m_activeBoundary = newActiveBoundary;
	getExtent(&region);
	TheRadar->newMap(TheTerrainLogic);
	ThePartitionManager->rva00625300(&region);
	TheShroudManager->setRegion(&region, 0.0f);
	TheGameLogic->m_opaque170->rva0035A2DC(&region, TheRva00DFE758->m_floatD4);

	Object *object = TheGameLogic->getFirstObject();
	while (object != 0)
	{
		object->friend_notifyOfNewMapBoundary();
		object = *(Object **)((char *)object + 0x8C);
	}

	TheTacticalView->forceCameraConstraintRecalc();
}
