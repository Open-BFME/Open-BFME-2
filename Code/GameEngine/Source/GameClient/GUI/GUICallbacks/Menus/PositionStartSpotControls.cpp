// Donor: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotControls.cpp.
// Target identity: existing positionStartSpots(AsciiString) RVA 0x303ED4 and
// byte-verified AptMapPreview::rva0057DA21 call RVA 0x3001CD with Player_%d_Start
// waypoint coordinates. Both use the same map/window/start-button roles as
// ZH SkirmishGameOptionsMenu.cpp. Target reads map extent at +8, calls native
// Region3D copy and findDrawPositions, and checks up to eight button overlaps.
// Donor lifetime scope and out-of-line Region3D copy fix the previously blocked
// inline-copy/stack-layout mismatch. No new pins or shared header changes.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
typedef int Int;
typedef bool Bool;
typedef float Real;

#include "Coord3D.h"

struct Region3D
{
	Region3D(const Region3D &that);
	~Region3D();

	Coord3D lo;
	Coord3D hi;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winSetPosition(Int x, Int y);
};

class MapMetaData
{
	public:
	char m_beforeExtent[8];
	Region3D m_extent;
};

void findDrawPositions(Int startX, Int startY, Int width, Int height,
	Region3D extent, ICoord2D *ul, ICoord2D *lr);

enum { MAX_SLOTS = 8 };

// ZH twin: GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp
void positionStartSpotControls(GameWindow *win, GameWindow *mapWindow,
	Coord3D *pos, MapMetaData *mmd, GameWindow *buttonMapStartPositions[])
{
	if (!win || !mmd || !mapWindow || !buttonMapStartPositions)
		return;

	ICoord2D winMapSize, winMapPos, gadgetPos;
	Int gadgetSize[2];
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);
	win->winGetSize(&gadgetSize[0], &gadgetSize[1]);
	{
		Int ul[2];
		ICoord2D *ulAddress = (ICoord2D *)ul;
		Int smallWidth, smallHeight;
		ICoord2D lr;
		findDrawPositions(0, 0, winMapSize.x, winMapSize.y,
			mmd->m_extent, ulAddress, &lr);
		smallWidth = lr.x - ul[0];
		smallHeight = lr.y - ul[1];

		Real position;
		position = (pos->x - mmd->m_extent.lo.x) /
			(mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		gadgetPos.x = (position * smallWidth) - gadgetSize[0] / 2 + ul[0];

		position = (pos->y - mmd->m_extent.lo.y) /
			(mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		gadgetPos.y = ((1 - position) * smallHeight) - gadgetSize[1] / 2 + ul[1];
	}

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (buttonMapStartPositions[i] == win)
			break;
		ICoord2D tempPos;
		buttonMapStartPositions[i]->winGetScreenPosition(&tempPos.x, &tempPos.y);
		if (gadgetPos.x > tempPos.x &&
			gadgetPos.x < tempPos.x + gadgetSize[0] &&
			gadgetPos.y > tempPos.y &&
			gadgetPos.y < tempPos.y + gadgetSize[1])
		{
			Int closerRight = tempPos.x + gadgetSize[0] - gadgetPos.x;
			Int closerBottom = tempPos.y + gadgetSize[1] - gadgetPos.y;
			if (closerRight < closerBottom)
				gadgetPos.x = tempPos.x + gadgetSize[0] + 1;
			else if (closerBottom < closerRight)
				gadgetPos.y = tempPos.y + gadgetSize[1] + 1;
			else
			{
				gadgetPos.x = tempPos.x + gadgetSize[0] + 1;
				gadgetPos.y = tempPos.y + gadgetSize[1] + 1;
			}
		}
	}
	win->winSetPosition(gadgetPos.x, gadgetPos.y);
}
