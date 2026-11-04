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

class Drawable
{
public:
	const Coord3D *getPosition() const;		// 0x002763E6
	void drawIconUI();				// 0x00278DFE
	Bool isDrawableEffectivelyHidden()
	{
		return reinterpret_cast<Rva00270260 *>(this)->rva00270260();
	}
	Object *getObject() { return m_object; }
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's getObject copy loses to the first-in-order copy (no
	// retail address); the call below inlines it but still emits the loser
	// COMDAT. Rebinding there emits only this unique (trivially kept) copy.
	// No flags touched.
	Object *bfme_object() { return m_object; }

private:
	unsigned char m_pad00[0xFC];
	Object *m_object;				// +0xFC
};

#include "../../../../GameEngine/Include/Common/Player.h"

#include "../../../../GameEngine/Include/Common/PlayerList.h"

#include "../../../../GameEngine/Include/GameClient/View.h"

#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

class DebugLineDrawer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void drawLine(const Coord3D *start, const Coord3D *end,
		UnsignedInt color, Int a, Int b);	// slot 11 (+0x2C)
};

class Display
{
public:
	DebugLineDrawer *getLineDrawer() { return m_lineDrawer; }

private:
	unsigned char m_pad00[0x2C];
	DebugLineDrawer *m_lineDrawer;			// +0x2C
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
		TheDisplay->getLineDrawer()->drawLine(&pos, &normal, color, 0, 0);
	}
}

void drawablePostDraw(Drawable *draw, void *userData)
{
	Real FXPitch = TheTacticalView->getFXPitch();
	if (draw->isDrawableEffectivelyHidden() || FXPitch < 0.0f)
		return;

	Object *obj = draw->bfme_object();
	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	CellShroudStatus ss = (!obj) ? OBJECTSHROUD_CLEAR : obj->getShroudStatusForPlayer(localPlayerIndex);
	if (ss > OBJECTSHROUD_PARTIAL_CLEAR)
		return;

	draw->drawIconUI();

	if (TheWritableGlobalData->m_showTerrainNormals)
		drawTerrainNormal(draw, userData);

	TheGameClient->incrementRenderedObjectCount();
}
