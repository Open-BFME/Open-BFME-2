// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// InGameUI::drawFloatingText, retail 0x0029D200 (266 bytes).
//
// Direct port of the Battle for Middle-earth reference reconstruction
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/InGameUI.cpp,
// matched 274 bytes there): every floating text whose world-to-screen
// projection succeeds and whose location is unshrouded is drawn with a
// fading drop shadow. Deltas proven by the retail body: the texts hang on
// a circular singly-linked list through a dummy head pointer at +0x8A0
// (node links at +0, payload at +8) with the rise speed right after it at
// +0x8A8, the terrain rate reads from TheGameEngine+0x38, and the
// projection sits at tactical vtable slot 0x160. The shroud query reuses
// the PartitionManager pin from handleRadiusCursor, and the color
// unpacking is the reference GameGetColorComponents.

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

class Player
{
public:
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
	virtual int worldToScreen(const Coord3D *world, ICoord2D *screen);
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

class GameEngine
{
public:
	unsigned char m_pad[0x38];
	int m_logicFrameRate; // +0x38
};

extern GameEngine *TheGameEngine;

void GameGetColorComponents(int color, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a);

class DisplayString
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
	virtual void setColors(int fillColor, int dropColor);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void draw(int x, int y, int w, int h);
	virtual void getSize(int *width, int *height);
};

class FloatingTextData
{
public:
	void *m_vptr; // +0x00 MemoryPoolObject
	int m_color; // +0x04
	void *m_text; // +0x08 UnicodeString stand-in
	DisplayString *m_dString; // +0x0C
	Coord3D m_pos3D; // +0x10
	int m_frameTimeOut; // +0x1C
	int m_frameCount; // +0x20
};

struct FloatingTextNode
{
	FloatingTextNode *m_next; // +0x00, circular through the dummy head
	void *m_link; // +0x04
	FloatingTextData *m_text; // +0x08
};

class InGameUI
{
protected:
	void drawFloatingText();

private:
	unsigned char m_pad[0x8A0];
	FloatingTextNode *m_floatingTextHead; // +0x8A0, dummy head pointer
	void *m_floatingTextPad; // +0x8A4
	float m_floatingTextMoveUpSpeed; // +0x8A8
};

// ?drawFloatingText@InGameUI@@IAEXXZ
void InGameUI::drawFloatingText()
{
	for (FloatingTextNode *node = m_floatingTextHead->m_next; node != m_floatingTextHead; node = node->m_next)
	{
		FloatingTextData *ftd = node->m_text;
		ICoord2D pos;

		int playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;

		if (!TheTacticalView->worldToScreen(&ftd->m_pos3D, &pos) &&
			ftd->m_dString &&
			TheShroudManager->getShroudStatusForPlayer(playerIndex, &ftd->m_pos3D) == CELLSHROUD_CLEAR)
		{
			pos.y -= ftd->m_frameCount * m_floatingTextMoveUpSpeed / TheGameEngine->m_logicFrameRate;

			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
			int width;

			GameGetColorComponents(ftd->m_color, &r, &g, &b, &a);
			int dropColor = (a << 24);
			ftd->m_dString->getSize(&width, 0);
			ftd->m_dString->setColors(ftd->m_color, dropColor);
			ftd->m_dString->draw(pos.x - (width / 2), pos.y, 1, 1);
		}
	}
}
