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

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Mouse
{
public:
	unsigned char m_pad[0x4F0C];
};

extern Mouse *TheMouse;

class Radar
{
public:
	bool screenPixelToWorld(const ICoord2D *pixel, Coord3D *world);

	unsigned char m_pad[0x10];
	bool m_hidden; // +0x10
	bool m_radarForceOn; // +0x11
};

extern Radar *TheRadar;

class Player
{
public:
	bool hasRadar() const;

	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	unsigned char m_pad[0x10];
	Player *m_localPlayer; // +0x10
};

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

extern TacticalView *TheTacticalView;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};

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
	void rva0029A64A();

private:
	unsigned char m_pad[0x888];
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
		(!TheRadar->m_hidden && ThePlayerList->m_localPlayer &&
			ThePlayerList->m_localPlayer->hasRadar());

	if (!radarOn || !TheRadar->screenPixelToWorld(mousePos, &pos))
	{
		TheTacticalView->screenToTerrain(mousePos, &pos, false);

		if (TheShroudManager && ThePlayerList)
		{
			int playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;
			if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &pos) != CELLSHROUD_CLEAR)
				TheTacticalView->screenToTerrain(mousePos, &pos, true);
		}
	}

	m_curRadiusCursor.setPosition(pos);
	m_curRadiusCursor.update();
}

void InGameUI::rva0029A64A()
{
	m_curRadiusCursor.clear();
	m_888 = 0;
}
