// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?drawTerrainNormal@@YAXPAVDrawable@@PAX@Z
// retail 0x00085A03..0x00085AB7 (180 bytes).
// ?drawablePostDraw@@YAXPAVDrawable@@PAX@Z
// retail 0x00085AB7..0x00085B36 (127 bytes) cdecl RET 0.
//
// Zero Hour's W3DView.cpp drawTerrainNormal / drawablePostDraw pair as
// BFME 2 builds them (Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/
// GameClient/W3DView.cpp carries the same statements). They sit next to
// each other in retail in the donor's order.
#include "Coord3D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CellShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;	// 0x0028D2A2
};

class Rva00270260
{
public:
	bool rva00270260();				// 0x00270260
};

#include "../../../../GameEngine/Include/Common/Player.h"

#include "../../../../GameEngine/Include/Common/PlayerList.h"

#include "../../../../GameEngine/Include/GameClient/View.h"

#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

// Keep View after Player and before Drawable: Snapshot must retain the
// lowercase slot spelling used by View (getFXPitch is at +0x1B0).
#include "../../../../GameEngine/Include/GameClient/Drawable.h"

class DebugLineDrawer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void drawLine(const Coord3D *start, const Coord3D *end,
		UnsignedInt color, Int a, Int b);	// slot 11 (+0x2C)
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

// Display keeps +0x2C as opaque protected storage; drawTerrainNormal reads it
// as the debug line drawer.
class W3DViewDrawablePostDrawDisplayAccess : public Display
{
public:
	__forceinline DebugLineDrawer *getLineDrawer() { return (DebugLineDrawer *)field2C; }
};

#include "../../../../GameEngine/Include/Common/GlobalData.h"

#include "../../../../GameEngine/Include/GameClient/GameClientClass.h"

extern TerrainLogic *TheTerrainLogic;
extern Display *TheDisplay;
extern View *TheTacticalView;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;
extern GameClient *TheGameClient;

static void drawTerrainNormal(Drawable *draw, void *userData)
{
	UnsignedInt color = 0xFFFFFF00;
	if (TheTerrainLogic)
	{
		const Coord3D *drawPos = draw->getPosition();
		Coord3D pos;
		pos.x = drawPos->x;
		pos.y = drawPos->y;
		pos.z = drawPos->z;
		Coord3D normal;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, &normal);
		const Real NORMLEN = 20;
		normal.x = pos.x + normal.x * NORMLEN;
		normal.y = pos.y + normal.y * NORMLEN;
		normal.z = pos.z + normal.z * NORMLEN;
		static_cast<W3DViewDrawablePostDrawDisplayAccess *>(TheDisplay)->getLineDrawer()->drawLine(&pos, &normal, color, 0, 0);
	}
}

void drawablePostDraw(Drawable *draw, void *userData)
{
	Real FXPitch = TheTacticalView->getFXPitch();
	if (reinterpret_cast<Rva00270260 *>(draw)->rva00270260() || FXPitch < 0.0f)
		return;

	Object *obj = draw->m_object;
	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	CellShroudStatus ss = (!obj) ? OBJECTSHROUD_CLEAR : obj->getShroudStatusForPlayer(localPlayerIndex);
	if (ss > OBJECTSHROUD_PARTIAL_CLEAR)
		return;

	draw->drawIconUI();

	if (TheWritableGlobalData->m_showTerrainNormals)
		drawTerrainNormal(draw, userData);

	TheGameClient->incrementRenderedObjectCount();
}
