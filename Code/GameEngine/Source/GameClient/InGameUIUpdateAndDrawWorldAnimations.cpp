// cl: /Ireference/shims/bfmelist /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ @0x0029D44E 452B.
// Update all world animations and draw the visible ones. Direct port of the
// BFME1 donor (game/GameEngine/Source/GameClient/InGameUI.cpp) with deltas
// proven by retail: no null check on wad, world list at +0x8CC as list<int>,
// GameLogic frame at +0x40, PlayerList local at +0x10 Player index at +0x54,
// shroud via TheShroudManager, z-rise divided by g_Va00DBA4E4 vs BfmeZeroRange,
// fade threshold from g_00DFEE08 with unsigned float conversion storing alpha
// inline at Anim2D+0x1C, projection at tactical slot 0x160 failing to 0 draws,
// zoom via slots 0x140/0x124, erase via rowed list<int>::erase. Evidence:
// pinned name, donor InGameUI::updateAndDrawWorldAnimations, caller preDraw
// 0x002A326E, rowed callees isGamePaused getShroudStatus getCurrentFrame
// draw erase operator delete ftol2.
#include <list>

typedef int Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct ICoord2D
{
	Int x;
	Int y;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

class GameLogic
{
public:
	unsigned char isGamePaused();
	unsigned char m_padAfterPaused[0x3F];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
extern UnsignedInt g_00DFEE08;

class Player
{
public:
	unsigned char m_pad[0x54];
	Int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	unsigned char m_pad[0x10];
	Player *m_localPlayer; // +0x10
};

extern PlayerList *ThePlayerList;

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *pos) const;
};

extern PartitionManager *TheShroudManager;

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
	virtual Real getZoom();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual Real getMaxZoom();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen);
};

extern TacticalView *TheTacticalView;

class Anim2D
{
public:
	virtual void *slot00(int flag);
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
	void draw(Int x, Int y, Int width, Int height);
	unsigned char getStatus() { return m_status; }
	void setAlpha(Real alpha) { m_alpha = alpha; }

private:
	char m_beforeStatus[0x0C];
	unsigned char m_status; // +0x10
	char m_beforeAlpha[0x0B];
	Real m_alpha; // +0x1C
};

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0x00000000,
	WORLD_ANIM_FADE_ON_EXPIRE = 0x00000001,
	WORLD_ANIM_PLAY_ONCE_AND_DESTROY = 0x00000002
};

struct WorldAnimationData
{
	Anim2D *m_anim; // +0x00
	Coord3D m_worldPos; // +0x04
	UnsignedInt m_expireFrame; // +0x10
	UnsignedInt m_options; // +0x14
	Real m_zRisePerSecond; // +0x18
};

void __cdecl operator delete(void *p);

class InGameUI
{
protected:
	void updateAndDrawWorldAnimations();

private:
	unsigned char m_pad[0x8CC];
	_STL::list<int> m_worldAnimationList; // +0x8CC
};

void InGameUI::updateAndDrawWorldAnimations()
{
	for (_STL::list<int>::iterator it = m_worldAnimationList.begin(); it != m_worldAnimationList.end(); )
	{
		WorldAnimationData *wad = (WorldAnimationData *)(int)*it;

		if (TheGameLogic->isGamePaused() == 0)
		{
			if (TheGameLogic->m_frame >= wad->m_expireFrame ||
				((wad->m_options & WORLD_ANIM_PLAY_ONCE_AND_DESTROY) &&
				 (wad->m_anim->getStatus() & 4)))
			{
				Anim2D *anim = wad->m_anim;
				void *q;
				if (anim != 0)
					q = anim->slot00(0);
				else
					q = 0;
				::operator delete(q);
				::operator delete(wad);
				it = m_worldAnimationList.erase(it);
				continue;
			}

			if (wad->m_zRisePerSecond != 0.0f)
				wad->m_worldPos.z += wad->m_zRisePerSecond / (Real)g_Va00DBA4E4;
		}

		Int playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;
		if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &wad->m_worldPos) != CELLSHROUD_CLEAR)
		{
			++it;
			continue;
		}

		if (wad->m_options & WORLD_ANIM_FADE_ON_EXPIRE)
		{
			UnsignedInt framesTillExpire = wad->m_expireFrame - TheGameLogic->m_frame;
			if (framesTillExpire < g_00DFEE08)
			{
				Real alpha = (Real)framesTillExpire / (Real)g_00DFEE08;
				wad->m_anim->setAlpha(alpha);
			}
		}

		ICoord2D screen;
		if (!TheTacticalView->worldToScreen(&wad->m_worldPos, &screen))
		{
			UnsignedInt width = wad->m_anim->getCurrentFrameWidth();
			UnsignedInt height = wad->m_anim->getCurrentFrameHeight();

			Real zoomScale = TheTacticalView->getMaxZoom() / TheTacticalView->getZoom();
			width = (UnsignedInt)(width * zoomScale);
			height = (UnsignedInt)(height * zoomScale);

			screen.x -= width / 2;
			screen.y -= height / 2;

			wad->m_anim->draw(screen.x, screen.y, width, height);
		}

		++it;
	}
}
