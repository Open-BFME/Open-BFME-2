// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /GX
//
// ?rva004457BC@AptLanLobby@@QAEXXZ, retail 0x004457BC..0x00445BAA (1006
// bytes, plain ret). Name unknown (address name, already pinned). Rebuilds
// the LAN lobby's custom games list box (+0x6A8): unless the list box owns
// the window manager's grab window (vslot 51 through the rowed
// Rva003140AB::rva003140AB) it remembers the selected row's game, resets the
// box, sets six column widths by the game mode at +0x304 (0 open play, 1
// strategic, anything else returns), then walks the +0x668 game list
// (0x0058113D) adding three icons (GameInfo vslot 6), the bracketed host name
// (vslot 22), the map's display name (open play only; AptMapPreview at
// +0x2E8 looks it up), the "%d/%d" player count and item data, in the colour
// TheVersion's 0x00237E63 picks; it reselects the remembered game or, when it
// is gone, clears the +0x288 setup panel's game (0x0043FA68) and refreshes
// the buttons (0x0044469C).
//
// Evidence: sole caller AptLanLobby::rva00445E3E (call at 0x00445E75 with
// ECX=screen); the WorldBuilder twin 0x01413900 has the same callees and
// the same `for (index = 0; ; ++index) { game = get(index); if (!game)
// break; ... }` loop. That loop shape is what places retail's shared EH
// epilogue right after the in-loop default-return cleanup (a condition
// loop puts it at the end of the function). Callees resolve through rows
// and the existing pins for 0x0058113D and 0x00237E63. Wide literals L""
// L"[" L"]" L"%d/%d" checked against retail 0x00BBB5C4 0x00BEE884
// 0x00C3E28C 0x00C380FC.

#include "unicode_string.h"
#include "ascii_string.h"

class Image;
class WinInstanceData;

class GameWindow
{
};

void GadgetListBoxReset(GameWindow *window);
void GadgetListBoxGetSelected(GameWindow *listbox, int *selected);
int Rva003253BEGet(GameWindow *listbox, int row, int column);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count, int *widths);
int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, int row, int column, int width, int height, bool overwrite, int color);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
void __cdecl Rva00325388Send(GameWindow *listbox, int data, int row, int column);
void GadgetListBoxSetSelected(GameWindow *listbox, int index);

// Rowed 0x003140AB: is the given window this window or one of its children.
class Rva003140AB
{
public:
	bool rva003140AB(Rva003140AB *other);
};

// Only vslot 51 (the grab window, vtable+0xCC) is called here.
class GameWindowManager
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
	virtual void v48(); virtual void v49(); virtual void v50();
	virtual GameWindow *v51();
};

extern GameWindowManager *TheWindowManager;

// GameInfo vslots 6 (icon by index, vtable+0x18) and 22 (host name,
// vtable+0x58) and its rowed slot counters.
class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual const Image *v06(int index);
	virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21();
	virtual UnicodeString v22();

	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
	AsciiString getMap() const;
};

class LANGameInfo : public GameInfo
{
public:
	unsigned char m_pad004[0x11 - 0x04];
	unsigned char m_11; // +0x11 (in progress: the name is bracketed)
	unsigned char m_pad012[0x90 - 0x12];
	unsigned char m_version[0x10]; // +0x90
};

class MapMetaData
{
public:
	UnicodeString bfme_getBaseDisplayName();
};

// The +0x668 game list; 0x0058113D (87 bytes) is pinned by this name.
class Rva0058113D
{
public:
	LANGameInfo *rva0058113D(unsigned int index);
};

class AptMapPreview
{
public:
	MapMetaData *rva0057D922(const AsciiString &mapName);
};

// TheVersion's 0x00237E63 (text colour for another build's version block),
// pinned by this name.
class Version
{
public:
	int rva00237E63(const void *other, bool force);
};

extern Version *TheVersion;

class AptMpGameSetup
{
public:
	void rva0043FA68(GameInfo *game);
};

class AptLanLobby
{
public:
	void rva0044469C();
	void rva004457BC();

private:
	unsigned char m_pad000[0x288];
	AptMpGameSetup m_panel; // +0x288
	unsigned char m_pad289[0x2E8 - 0x289];
	AptMapPreview m_panelMaps; // +0x2E8 (the panel's +0x60)
	unsigned char m_pad2e9[0x304 - 0x2E9];
	int m_304; // +0x304
	unsigned char m_pad308[0x668 - 0x308];
	Rva0058113D m_668; // +0x668
	unsigned char m_pad669[0x6A8 - 0x669];
	GameWindow *m_customGamesList; // +0x6A8
};

void AptLanLobby::rva004457BC()
{
	if (!m_customGamesList)
		return;
	if (reinterpret_cast<Rva003140AB *>(m_customGamesList)->rva003140AB(reinterpret_cast<Rva003140AB *>(TheWindowManager->v51())))
		return;

	int selected = -1;
	int reselect = -1;
	int selectedGame = 0;
	GadgetListBoxGetSelected(m_customGamesList, &selected);
	if (selected != -1)
		selectedGame = Rva003253BEGet(m_customGamesList, selected, 3);
	GadgetListBoxReset(m_customGamesList);

	int widths[6];
	switch (m_304)
	{
	case 0:
		widths[3] = 0x23;
		widths[4] = 0x2B;
		break;
	case 1:
		widths[3] = 0x25;
		widths[4] = 0x29;
		break;
	default:
		return;
	}
	widths[0] = widths[1] = widths[2] = 5;
	widths[5] = 7;
	GadgetListBoxSetColumnWidths(m_customGamesList, 6, widths);

	for (int index = 0; ; ++index)
	{
		LANGameInfo *game = m_668.rva0058113D(index);
		if (!game)
			break;

		UnicodeString name;
		name = (const unsigned short *)L"";
		if (game->m_11)
			name += (const unsigned short *)L"[";
		name += game->v22();
		if (game->m_11)
			name += (const unsigned short *)L"]";

		UnicodeString players;
		players.format((const unsigned short *)L"%d/%d", game->getNumPlayers(), game->getNumOpenOrOccupiedSlots());
		int color = TheVersion->rva00237E63(game->m_version, false);
		const Image *icon0 = game->v06(0);
		const Image *icon1 = game->v06(1);
		const Image *icon2 = game->v06(2);

		UnicodeString mapName;
		switch (m_304)
		{
		case 0:
		{
			MapMetaData *map = m_panelMaps.rva0057D922(game->getMap());
			mapName = map->bfme_getBaseDisplayName();
			break;
		}
		case 1:
			break;
		default:
			return;
		}

		int row = GadgetListBoxAddEntryImage(m_customGamesList, icon0, -1, 0, 0x14, 0x14, true, -1);
		GadgetListBoxAddEntryImage(m_customGamesList, icon1, row, 1, 0x14, 0x14, true, -1);
		GadgetListBoxAddEntryImage(m_customGamesList, icon2, row, 2, 0x14, 0x14, true, -1);
		GadgetListBoxAddEntryText(m_customGamesList, name, color, row, 3, true);
		GadgetListBoxAddEntryText(m_customGamesList, mapName, color, row, 4, true);
		GadgetListBoxAddEntryText(m_customGamesList, players, color, row, 5, true);
		Rva00325388Send(m_customGamesList, (int)game, row, 3);
		Rva00325388Send(m_customGamesList, icon0 != 0, row, 0);
		Rva00325388Send(m_customGamesList, icon1 != 0, row, 1);
		Rva00325388Send(m_customGamesList, icon2 != 0, row, 2);
		if (selectedGame == (int)game)
			reselect = row;
	}

	if (reselect >= 0)
		GadgetListBoxSetSelected(m_customGamesList, reselect);
	else if (selectedGame)
	{
		m_panel.rva0043FA68(0);
		rva0044469C();
	}
}
