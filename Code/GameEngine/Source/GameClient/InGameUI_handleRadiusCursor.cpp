// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// InGameUI::handleRadiusCursor, retail 0x0029A661 (203 bytes).
//
// Direct port of the Battle for Middle-earth reference reconstruction
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/InGameUIBodies.cpp,
// matched 210 bytes there): while the radius cursor is live it follows the
// mouse through the radar pixel-to-world when the radar is up, otherwise
// through the tactical view with a shroud-clamped second pass, then the
// decal is repositioned and updated. Callees are pinned from the reference
// identities (hasRadar, screenPixelToWorld, RadiusDecal setPosition/update,
// PartitionManager getShroudStatusForPlayer); the tactical-view terrain
// projection goes through vtable slot 0x168. Layout from the retail body:
// the cursor object at +0x88C (empty flag at +0x894, matching the landed
// RadiusDecal::clear), the mouse position at TheMouse+0x4F0C, radar flags
// at +0x10/+0x11, local player at PlayerList+0x10 with the index at +0x54.

#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/GameClient/Mouse.h"

extern Mouse *TheMouse;

#include "../../Include/Common/Radar.h"

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

class TacticalView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
};

extern class View *TheTacticalView;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

#include "../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *TheShroudManager;

class RadiusDecal
{
public:
	void setPosition(const Coord3D &pos);
	void update();
	void clear();

	void *m_unused0;
	void *m_object;
	bool m_empty;
};

class InGameUI
{
protected:
	void handleRadiusCursor();

public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(001) SLOT(002) SLOT(003) SLOT(004) SLOT(005) SLOT(006) SLOT(007) SLOT(008)
	SLOT(009) SLOT(010) SLOT(011) SLOT(012) SLOT(013) SLOT(014) SLOT(015) SLOT(016)
	SLOT(017) SLOT(018) SLOT(019) SLOT(020) SLOT(021) SLOT(022) SLOT(023) SLOT(024)
	SLOT(025) SLOT(026) SLOT(027) SLOT(028) SLOT(029) SLOT(030) SLOT(031) SLOT(032)
	SLOT(033) SLOT(034) SLOT(035) SLOT(036) SLOT(037) SLOT(038) SLOT(039) SLOT(040)
	SLOT(041) SLOT(042) SLOT(043) SLOT(044) SLOT(045) SLOT(046) SLOT(047) SLOT(048)
	SLOT(049) SLOT(050) SLOT(051) SLOT(052) SLOT(053) SLOT(054) SLOT(055) SLOT(056)
	SLOT(057) SLOT(058) SLOT(059) SLOT(060) SLOT(061) SLOT(062) SLOT(063) SLOT(064)
	SLOT(065) SLOT(066) SLOT(067) SLOT(068) SLOT(069) SLOT(070) SLOT(071) SLOT(072)
	SLOT(073) SLOT(074) SLOT(075) SLOT(076) SLOT(077) SLOT(078) SLOT(079) SLOT(080)
#undef SLOT
	virtual void setRadiusCursorNone();

private:
	unsigned char m_pad[0x888 - 4];
	int m_888;
	RadiusDecal m_curRadiusCursor; // +0x88C
};

// ?handleRadiusCursor@InGameUI@@IAEXXZ
void InGameUI::handleRadiusCursor()
{
	if (m_curRadiusCursor.m_empty)
		return;

	const ICoord2D *mousePos = (const ICoord2D *)((const unsigned char *)TheMouse + 0x4F0C);
	Coord3D pos;

	bool radarOn = TheRadar->m_radarForceOn ||
		(!TheRadar->m_radarHidden && ThePlayerList->m_local &&
			ThePlayerList->m_local->hasRadar());

	if (!radarOn || !TheRadar->screenPixelToWorld(mousePos, &pos))
	{
		((TacticalView *)TheTacticalView)->screenToTerrain(mousePos, &pos, false);

		if (TheShroudManager && ThePlayerList)
		{
			int playerIndex = ThePlayerList->m_local->m_playerIndex;
			if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &pos) != CELLSHROUD_CLEAR)
				((TacticalView *)TheTacticalView)->screenToTerrain(mousePos, &pos, true);
		}
	}

	m_curRadiusCursor.setPosition(pos);
	m_curRadiusCursor.update();
}

void InGameUI::setRadiusCursorNone()
{
	m_curRadiusCursor.clear();
	m_888 = 0;
}
