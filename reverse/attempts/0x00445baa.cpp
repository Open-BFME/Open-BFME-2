// ?Rva00445BAALanLobbyTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Banked note: also needs the reverse/symbols.csv pin
// ?GadgetListBoxGetEntryBasedOnXY@@YAHPAVGameWindow@@HHAAH1@Z,0x00323F6F (9B frame-and-jump
// entry to 0x00323E95; the BFME1 donor calls GadgetListBoxGetEntryBasedOnXY at the same spot).
//
// BFME2's LAN lobby gadget initialization callback, retail 0x00445DA5
// (153 bytes). The screen's constructor 0x00445EE3 binds it as a member
// function pointer on the whole screen object (vftable 0x00C3E0F8; the
// callback interface BfmeAptScreenLanLobby.cpp views sits at +0x27C).
//
// Donor: Open-BFME-1 GUICallbacks/Apt/BfmeAptScreenLanLobby_onInitGadget.cpp
// (BfmeAptScreenLanLobby::_bfme_onInitGadget, BFME1 0x005187F0); the name is
// the donor's identity for the same role and "LanLobby::" gadget names.
// BFME2 target evidence: only CustomGamesList (stored at +0x6A8, games
// tooltip 0x00445BAA) and NameEntry remain; NameEntry's link helper at
// +0x6AC (destroyed by ??1Rva0031455E) attaches through its vslot 1, and the
// screen clears +0x6C0 afterwards.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int mouse));
};

class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *window);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void __cdecl Rva0032060D(GameWindow *window, int value);
void bfmeGo924F(BfmeKeyLC *key, unsigned short value);

int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, int x, int y, int &row, int &column);
int Rva003253BEGet(GameWindow *listbox, int row, int column);

class GameSlot
{
public:
	bool isHuman() const;

	unsigned char m_pad00[0x30];
	UnicodeString m_name; // +0x30
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int slot) const;
};

class LANGameInfo : public GameInfo
{
};

// GameInfo's 16-byte nonzero test (rowed under its address name).
class Rva003FF1C2
{
public:
	bool rva003FF1C2() const;
};

void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

class LANAPI
{
	friend void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

protected:
	bool rva00449969(LANGameInfo *game);
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

struct Outer00446A77;
extern Outer00446A77 *g_Va00A03354;

// Retail 0x00445BAA, 507 bytes: the custom games list tooltip. Donor
// Open-BFME-1 GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp
// (Rva00518150LanLobbyTooltip, BFME1 0x00518150), whose address name it
// keeps. BFME2 target evidence: it does nothing without the lobby screen
// (0x00E03354), reads the game from column 3's item data, and gives columns
// 0..2 their own TOOLTIP: strings (each only when that column's item data is
// set; column 2 picks MpSaveGame or GameStarted by the game's 16-byte
// nonzero test); other columns list the human players' names.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *, unsigned int mouse)
{
	if (!g_Va00A03354)
		return;

	int x, y, row, column;
	x = mouse & 0xffff;
	y = mouse >> 16;
	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);
	if (row != -1 && column != -1)
	{
		LANGameInfo *game = (LANGameInfo *)Rva003253BEGet(window, row, 3);
		if (!TheLAN->rva00449969(game))
			game = 0;
		if (game)
		{
			switch (column)
			{
			case 0:
				if ((void *)Rva003253BEGet(window, row, 0) != 0)
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
				return;
			case 1:
				if ((void *)Rva003253BEGet(window, row, 1) != 0)
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
				return;
			case 2:
				if ((void *)Rva003253BEGet(window, row, 2) != 0)
				{
					if (((const Rva003FF1C2 *)game)->rva003FF1C2())
						TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:MpSaveGame"), -1, 0, 1.0f);
					else
						TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:GameStarted"), -1, 0, 1.0f);
				}
				return;
			default:
			{
				UnicodeString tooltip;
				for (int i = 0; i < 8; ++i)
				{
					const GameSlot *slot = game->getConstSlot(i);
					if (slot->isHuman())
					{
						if (tooltip.getLength() != 0)
							tooltip += (const unsigned short *)L"\n";
						tooltip += slot->m_name;
					}
				}
				TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
				return;
			}
			}
		}
	}
	TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
}

class Rva0031455E
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);
};

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad000[0x6A8];
	GameWindow *m_customGamesList; // +0x6A8
	Rva0031455E m_nameEntryLink; // +0x6AC
	unsigned char m_pad6b0[0x6C0 - 0x6B0];
	unsigned char m_6c0; // +0x6C0
};

void BfmeAptScreenLanLobby::_bfme_onInitGadget(const char *name, void *, GameWindow *window)
{
	if (window != 0)
	{
		if (strcmp(name, "LanLobby::CustomGamesList") == 0)
		{
			GadgetListBoxReset(window);
			m_customGamesList = window;
			window->winSetTooltipFunc(Rva00445BAALanLobbyTooltip);
		}
		else if (strcmp(name, "LanLobby::NameEntry") == 0)
		{
			bfmeGo924F((BfmeKeyLC *)window, 0x0c);
			GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
			Rva0032060D(window, 0x80);
			m_nameEntryLink.attach(window);
			m_6c0 = 0;
		}
	}
}
