// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@InGameUI@@UAEXXZ
// retail 0x002A1582..0x002A1B07 (1413 bytes), thiscall, EH frame; slot 10 of
// InGameUI's SubsystemInterface vftable 0x007FD410.
//
// Structure from the WorldBuilder twin 0x00DAF860 (its callees are
// InGameUI::updateMilitarySubtitle, updateLocalPhantomStructureDisplay and
// updateOrderDisplayMode, its strings the two ControlBar window keys and
// GUI:ControlBarMoneyDisplay) and from Zero Hour's / BFME 1's InGameUI::update.
// Retail order: the movie stream at +0x5C4 (slot 6 frame flags & 4 then slot
// 13; stopMovie slot 88) and the cameo stream at +0x5CC; the six UI messages
// at +0x5D0 fade by (frame - timestamp) * 0.01 once older than the delay
// +0x838 / g_Va00DBA4E4 / 1000 (rowed GameGetColorComponents and the rowed
// remove-at-index 0x0029B380); rowed updateMilitarySubtitle; the subsystem at
// +0x7F4 updates; the money and power windows (function-local NameKeys behind
// guard bits 1 and 2 at 0x00DFEEDC; rowed nameToKey 0x00148E1A) show the money
// (+0x94) of the player rowed bfmePickRV 0x002A7E14 returns through the rowed
// UnicodeString::format and GadgetStaticTextSetText (lastMoney at 0x00DBBAEC
// starts at -1) and are hidden or shown through rowed winIsHidden/winHide;
// rowed updateFloatingText; TheControlBar update; updateIdleWorker (slot
// 116); every registered window layout (list at +0x18) runs its update; the
// keyboard camera rotation (+0x8BB/+0x8BC by TheGlobalData +0xC2C) zoom
// (+0x8BD/+0x8BE: view slots 77/78) and scroll (+0x8BF..+0x8C2 by
// TheGlobalData +0xAF8 * +0xA9C * 250.0 at 0x00DBBADC; Coord2D length
// estimate as rowed 0x000037D1 > 0 scrolls through view slot 23); slot 53;
// the radar override and banner subsystems update; the purchase-science
// screen (rowed 0x0043C99A test then 0x0043D15F); the GUI command reset when
// +0x53C is set and the local player is gone or flagged (+0x750);
// updateLocalPhantomStructureDisplay (0x002A1158) and rowed
// updateOrderDisplayMode; rowed 0x004E7277 on +0x9CC; and every
// g_009BA4E8-th client frame the selected drawables whose object is
// shrouded for the local player (rowed Object::getShroudStatusForPlayer
// statuses 3 and 4) are deselected through TheInGameUI.
// Facts from retail: offsets slots globals and callees; names from the
// WorldBuilder twin and the Zero Hour donor.

#include <math.h>
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Color;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR = 0 };

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);

// Coord2D::GetLengthEstimate (out of line at 0x000037D1, coord2d.cpp),
// expanded here: the canonical Coord2D header does not declare it.
__forceinline Real Coord2DGetLengthEstimate(const Coord2D *c)
{
	if (fabs(c->x) > fabs(c->y))
		return (Real)(fabs(c->x) + fabs(c->y) * 0.25f);
	return (Real)(fabs(c->y) + fabs(c->x) * 0.25f);
}

#define V(n) virtual void v##n();

class SubsystemUpdate
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	virtual void update();		// +0x28
};

class GameClient
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30)
	virtual UnsignedInt getFrame();	// +0x7C
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameWindow
{
public:
	Bool winIsHidden();
	Int winHide(Bool hide);
};

class GameWindowManager
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);	// +0xF0
};

class GameTextInterface
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16)
	virtual const UnicodeString *fetchFormat(const char *label, Bool *exists = 0);	// +0x44
};

void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class BfmeMemberRV
{
public:
	char m_pad00[0x94];
	Int m_money;			// +0x94
};

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	char m_pad000[0x54];
	Int m_playerIndex;		// +0x54
	char m_pad058[0x750 - 0x58];
	Int m_750;			// +0x750
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

	char m_pad00[0x10];
	Player *m_local;		// +0x10
};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }

	char m_pad000[0xfc];
	Object *m_object;		// +0xFC
};

struct DrawableListNode
{
	DrawableListNode *next;
	DrawableListNode *prev;
	Drawable *drawable;
};

// The selection list's const iterator: the loop takes the drawable through
// a postfix increment, whose copy retail keeps in eax.
struct DrawableListIt
{
	DrawableListNode *node;

	DrawableListIt operator++(int)
	{
		DrawableListIt tmp = *this;
		node = node->next;
		return tmp;
	}
	Drawable *operator*() const { return node->drawable; }
	bool operator!=(const DrawableListIt &that) const { return node != that.node; }
};

struct DrawableList
{
	DrawableListIt begin() const { DrawableListIt it; it.node = head->next; return it; }
	DrawableListIt end() const { DrawableListIt it; it.node = head; return it; }

	DrawableListNode *head;
};

class WindowLayout
{
public:
	V(0) V(1)
	virtual void runUpdate(void *userData);	// +0x08
};

struct WindowLayoutNode
{
	WindowLayoutNode *next;
	WindowLayoutNode *prev;
	WindowLayout *layout;
};

class View
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22)
	virtual void scroll(Coord2D *delta);	// +0x5C
	V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62)
	virtual void setAngle(Real angle);	// +0xFC
	virtual Real getAngle();		// +0x100
	V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76)
	virtual void zoomIn();			// +0x134
	virtual void zoomOut();			// +0x138
};

class GlobalData
{
public:
	char m_pad000[0xa9c];
	Real m_horizontalScrollSpeedFactor;	// +0xA9C
	char m_padAA0[0xaf8 - 0xaa0];
	Real m_keyboardScrollFactor;		// +0xAF8
	char m_padAFC[0xc2c - 0xafc];
	Real m_keyboardCameraRotateSpeed;	// +0xC2C
};

class VideoStreamInterface
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5)
	virtual Int frameFlags(Int arg);	// +0x18
	V(7) V(8) V(9) V(10) V(11) V(12)
	virtual Bool frameReady();		// +0x34
};

class Rva004E7277
{
public:
	void rva004E7277();
};

class Rva0029B380
{
public:
	void rva0029B380(Int index);
};

class ControlBar;
class RadarWindowOverrideSource;
class BannerUI;

// The purchase-science screen at 0x00E03314: 0x0043C99A reports it up (its
// row spells int but retail tests al) and 0x0043D15F updates it. The latter
// is rowed as a thiscall placeholder but ignores ecx and is called without
// one, so it is declared here as the free function it is.
int Rva0043C99AGet(void);
void Rva0043D15FUpdate(void);

class InGameUI;

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern PlayerList *ThePlayerList;
extern GameTextInterface *TheGameText;
extern ControlBar *TheControlBar;
extern View *TheTacticalView;
extern GlobalData *TheWritableGlobalData;
extern float g_00DBBADC;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern BannerUI *g_00DFE32C;
extern GameClient *TheGameClient;
extern int g_009BA4E8;
extern InGameUI *TheInGameUI;

struct UIMessage
{
	UnicodeString fullText;
	void *displayString;
	UnsignedInt timestamp;
	Color color;
};

class InGameUI
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	virtual void update();					// +0x28
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46)
	virtual void setGUICommand(const void *command);	// +0xBC
	V(48) V(49)
	V(50) V(51) V(52)
	virtual void v53handler();				// +0xD4
	V(54)
	virtual void placeBuildAvailable(const void *build, Drawable *buildDrawable);	// +0xDC
	V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66)
	virtual void deselectDrawable(Drawable *draw);		// +0x10C
	V(68) V(69)
	V(70) V(71) V(72)
	virtual const DrawableList *getAllSelectedDrawables();	// +0x124
	V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	virtual void stopMovie();				// +0x160
	V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114) V(115)
	virtual void updateIdleWorker();			// +0x1D0

	void updateLocalPhantomStructureDisplay();
	void updateOrderDisplayMode();

protected:
	void updateMilitarySubtitle();
	void updateFloatingText();

public:
	char m_pad004[0x18 - 0x04];
	WindowLayoutNode *m_windowLayouts;			// +0x18
	char m_pad01C[0x53c - 0x1c];
	void *m_53c;						// +0x53C
	char m_pad540[0x5c4 - 0x540];
	VideoStreamInterface *m_videoStream;			// +0x5C4
	char m_pad5C8[0x5cc - 0x5c8];
	VideoStreamInterface *m_cameoVideoStream;		// +0x5CC
	UIMessage m_uiMessages[6];				// +0x5D0
	char m_pad630[0x7f4 - 0x630];
	SubsystemUpdate *m_7f4;					// +0x7F4
	char m_pad7F8[0x838 - 0x7f8];
	Int m_messageDelayMS;					// +0x838
	char m_pad83C[0x8bb - 0x83c];
	Bool m_cameraRotatingLeft;				// +0x8BB
	Bool m_cameraRotatingRight;				// +0x8BC
	Bool m_cameraZoomingIn;					// +0x8BD
	Bool m_cameraZoomingOut;				// +0x8BE
	Bool m_scrollLeft;					// +0x8BF
	Bool m_scrollRight;					// +0x8C0
	Bool m_scrollUp;					// +0x8C1
	Bool m_scrollDown;					// +0x8C2
	char m_pad8C3[0x9cc - 0x8c3];
	Rva004E7277 *m_9cc;					// +0x9CC
};

#undef V

void InGameUI::update()
{
	Int i;

	if (m_videoStream && (m_videoStream->frameFlags(0) & 4) && m_videoStream->frameReady())
		stopMovie();

	if (m_cameoVideoStream)
		m_cameoVideoStream->frameFlags(0);

	UnsignedInt currLogicFrame = TheGameLogic->getFrame();
	const int messageTimeout = m_messageDelayMS / g_Va00DBA4E4 / 1000;
	UnsignedByte r, g, b, a;
	Int amount;
	for (i = 6 - 1; i >= 0; i--)
	{
		if (currLogicFrame - m_uiMessages[i].timestamp > messageTimeout)
		{
			GameGetColorComponents(m_uiMessages[i].color, &r, &g, &b, &a);

			amount = (Int)((currLogicFrame - m_uiMessages[i].timestamp) * 0.01f);
			if (a - amount < 0)
				a = 0;
			else
				a -= amount;

			m_uiMessages[i].color = GameMakeColor(r, g, b, a);

			if (a == 0)
				((Rva0029B380 *)this)->rva0029B380(i);
		}
	}

	updateMilitarySubtitle();

	m_7f4->update();

	static Int lastMoney = -1;
	static NameKeyType moneyWindowKey = TheNameKeyGenerator->nameToKey("ControlBar.wnd:MoneyDisplay");
	static NameKeyType powerWindowKey = TheNameKeyGenerator->nameToKey("ControlBar.wnd:PowerWindow");

	GameWindow *moneyWin = TheWindowManager->winGetWindowFromId(0, moneyWindowKey);
	GameWindow *powerWin = TheWindowManager->winGetWindowFromId(0, powerWindowKey);

	BfmeMemberRV *moneyPlayer = ((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	if (moneyPlayer)
	{
		Int currentMoney = moneyPlayer->m_money;
		if (lastMoney != currentMoney)
		{
			UnicodeString buffer;

			buffer.format(TheGameText->fetchFormat("GUI:ControlBarMoneyDisplay"), currentMoney);
			GadgetStaticTextSetText(moneyWin, buffer);
			lastMoney = currentMoney;
		}
		if (moneyWin->winIsHidden())
		{
			moneyWin->winHide(false);
			powerWin->winHide(false);
		}
	}
	else
	{
		if (!moneyWin->winIsHidden())
		{
			moneyWin->winHide(true);
			powerWin->winHide(true);
		}
	}

	updateFloatingText();

	((SubsystemUpdate *)TheControlBar)->update();

	updateIdleWorker();

	for (WindowLayoutNode *it = m_windowLayouts->next; it != m_windowLayouts; it = it->next)
		it->layout->runUpdate(0);

	if (m_cameraRotatingLeft && !m_cameraRotatingRight)
		TheTacticalView->setAngle(TheTacticalView->getAngle() - TheWritableGlobalData->m_keyboardCameraRotateSpeed);
	else if (m_cameraRotatingRight && !m_cameraRotatingLeft)
		TheTacticalView->setAngle(TheTacticalView->getAngle() + TheWritableGlobalData->m_keyboardCameraRotateSpeed);

	if (m_cameraZoomingIn && !m_cameraZoomingOut)
		TheTacticalView->zoomIn();
	else if (m_cameraZoomingOut && !m_cameraZoomingIn)
		TheTacticalView->zoomOut();

	Coord2D scroll;
	scroll.x = 0.0f;
	scroll.y = 0.0f;
	if (m_scrollLeft && !m_scrollRight)
		scroll.x = -(TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * g_00DBBADC);
	else if (m_scrollRight && !m_scrollLeft)
		scroll.x = TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * g_00DBBADC;
	if (m_scrollUp && !m_scrollDown)
		scroll.y = -(TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * g_00DBBADC);
	else if (m_scrollDown && !m_scrollUp)
		scroll.y = TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * g_00DBBADC;

	if (Coord2DGetLengthEstimate(&scroll) > 0.0f)
		TheTacticalView->scroll(&scroll);

	v53handler();

	((SubsystemUpdate *)theRadarWindowOverrideSource)->update();
	((SubsystemUpdate *)g_00DFE32C)->update();

	if ((unsigned char)Rva0043C99AGet())
		Rva0043D15FUpdate();

	if (m_53c)
	{
		Player *player = ThePlayerList->getLocalPlayer();
		if (player == 0 || player->m_750)
		{
			setGUICommand(0);
			placeBuildAvailable(0, 0);
		}
	}

	updateLocalPhantomStructureDisplay();
	updateOrderDisplayMode();
	m_9cc->rva004E7277();

	if (TheGameClient->getFrame() % g_009BA4E8 == 0)
	{
		const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
		for (DrawableListIt it = selected->begin(); it != selected->end(); )
		{
			Drawable *draw = *it++;
			if (draw && draw->getObject())
			{
				CellShroudStatus ss = draw->getObject()->getShroudStatusForPlayer(
					ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0);
				if (ss == 3 || ss == 4)
					TheInGameUI->deselectDrawable(draw);
			}
		}
	}
}
