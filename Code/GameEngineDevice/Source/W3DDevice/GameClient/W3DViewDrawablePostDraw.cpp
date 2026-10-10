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

private:
	unsigned char m_pad00[0xFC];
	Object *m_object;				// +0xFC
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x54];
	Int m_playerIndex;				// +0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

private:
	unsigned char m_pad00[0x10];
	Player *m_local;				// +0x10
};

class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90(); virtual void v91();
	virtual void v92(); virtual void v93(); virtual void v94(); virtual void v95();
	virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual Real getFXPitch();			// slot 108 (+0x1B0)
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// slot 6 (+0x18)
};

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

class GlobalData
{
public:
	unsigned char m_pad00[0x9B1];
	Bool m_showTerrainNormals;			// +0x9B1
};

class GameClient
{
public:
	void incrementRenderedObjectCount() { m_renderedObjectCount++; }

private:
	unsigned char m_pad00[0xC4];
	Int m_renderedObjectCount;			// +0xC4
};

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

	Object *obj = draw->getObject();
	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	CellShroudStatus ss = (!obj) ? OBJECTSHROUD_CLEAR : obj->getShroudStatusForPlayer(localPlayerIndex);
	if (ss > OBJECTSHROUD_PARTIAL_CLEAR)
		return;

	draw->drawIconUI();

	if (TheWritableGlobalData->m_showTerrainNormals)
		drawTerrainNormal(draw, userData);

	TheGameClient->incrementRenderedObjectCount();
}
