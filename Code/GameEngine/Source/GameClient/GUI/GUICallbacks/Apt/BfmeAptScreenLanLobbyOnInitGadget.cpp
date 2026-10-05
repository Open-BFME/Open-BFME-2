// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
// +0x6AC (destroyed by ??1Rva0031455E) attaches through its vslot 1 and
// keeps the window at its +0x08 (+0x6B4), and the screen clears +0x6C0.

#include "unicode_string.h"
#include <list>

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

// The custom games list tooltip, unrowed 0x00445BAA (507 bytes; BFME1's is
// Rva00518150LanLobbyTooltip), pinned by address.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

// The name entry's link helper (BFME1's Gen_00479A60): it keeps the
// attached window at +0x08.
class Rva0031455E
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);

	void *m_04;
	GameWindow *m_owner; // +0x08
};

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};

extern LanguageFilter *TheLanguageFilter;

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of line.
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// The LAN preferences at +0x684 (ledger spelling of its setUserName); vslot 3
// writes the file.
class LanLobbyUserNamePrefs
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	void setUserName(UnicodeString name);

	unsigned char m_pad04[0x1C - 0x04];
};

// Other units' views of this same screen object, called by address name.
class Rva00580316
{
public:
	void rva00580316(void *prefs);

	unsigned char m_pad00[0x1C];
};

class Rva004442FD
{
public:
	void rva004442FD();
};

class Rva00444165
{
public:
	int rva00444165();
};

// Enables (rva00444083) or disables (rva004440F4) the create (1) and join
// (2) buttons.
class Rva00444083
{
public:
	void rva00444083(int flags);
	void rva004440F4(int flags);
};

class GameInfo
{
public:
	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
};

// TheLAN's game list: eight 0x1D0-byte slots from +0xDC end at +0xF5C, where
// the next game is linked.
class LANGameInfo : public GameInfo
{
public:
	unsigned char m_pad000[0x5C];
	int m_5c; // +0x5C
	unsigned char m_pad060[0xF5C - 0x60];
	LANGameInfo *m_next; // +0xF5C
};

class ModuleData;

// More views of the +0x668 object (rva00601941 resets it, rva00580B40 adds
// an entry) and of the +0x288 panel (enable).
class Rva00601941
{
public:
	void rva00601941();
};

class Rva00580B40
{
public:
	void rva00580B40(const ModuleData *entry);
};

class Rva0043DB66ByteOneSetter
{
public:
	void enable();
};

// The +0x288 panel (destroyed by ??1Rva004421E1); 0x0043DE19 (265 bytes) is
// unrowed and pinned by address.
class Rva004421E1
{
public:
	void rva0043DE19();
	// Unrowed 0x0043FFCF (8 bytes), pinned by address.
	void rva0043FFCF();
};

class GameModePreferences
{
public:
	UnicodeString rva0044D330();
};

class EnumeratedIP
{
public:
	void *m_next;
	unsigned int m_ip; // +0x04
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses();

private:
	void *m_addresses;
	int m_isWinsockInitialized;
};

// The two GlobalData fields read here (TheWritableGlobalData, 0x00DFE758).
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva004452A8GlobalData
{
	unsigned char m_pad000[0x26];
	unsigned char m_26; // +0x26
	unsigned char m_pad027[0xA48 - 0x27];
	unsigned int m_defaultIP; // +0xA48
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

// Unrowed 0x00437421 (482 bytes, no arguments), pinned by address.
void Rva00437421();

// Window manager vslots 44 and 45 are registerTabList and clearTabList
// (GameWindowManager_registerTabList.cpp; vtable 0x007C7C90). Retail copies
// the window into a temporary before the push_back, so the list is spelled
// here with int elements: its out-of-line bodies are the int list's
// (ICF-identical to the GameWindow * list) and already pinned.
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
	virtual void registerTabList(_STL::list<int> tabList);
	virtual void clearTabList();
};

extern GameWindowManager *TheWindowManager;

class LANAPI
{
public:
	LANAPI();
	virtual void v00();
	virtual void init();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void reset();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14();
	virtual void RequestLocations();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28();
	virtual void RequestSetName(UnicodeString name);
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52();
	virtual bool SetLocalIP(unsigned int ip);
	virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
	virtual void v58();

	unsigned char m_pad04[0x5D - 0x04];
	unsigned char m_isInLANMenu; // +0x5D
	unsigned char m_pad5e[0x60 - 0x5E];
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);
	void rva00446386(bool enable);
	void submitNameRva00444760();
	void rva00446772();
	void rva0044469C();
	void rva00445E3E(LANGameInfo *games);
	bool initLanRva004452A8();

	// Unrowed 0x004457BC (1006 bytes; rebuilds the games list box), pinned by
	// address.
	void rva004457BC();

private:
	unsigned char m_pad000[0x288];
	Rva004421E1 m_panel; // +0x288
	unsigned char m_pad289[0x304 - 0x289];
	int m_304; // +0x304
	unsigned char m_pad308[0x668 - 0x308];
	Rva00580316 m_668; // +0x668
	LanLobbyUserNamePrefs m_prefs; // +0x684
	UnicodeString m_userName; // +0x6A0
	int m_6a4; // +0x6A4
	GameWindow *m_customGamesList; // +0x6A8
	Rva0031455E m_nameEntry; // +0x6AC
	unsigned char m_pad6b8[0x6B9 - 0x6B8];
	unsigned char m_6b9; // +0x6B9
	unsigned char m_socketError; // +0x6BA
	bool m_6bb; // +0x6BB
	unsigned char m_pad6bc[0x6C0 - 0x6BC];
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
			m_nameEntry.attach(window);
			m_6c0 = 0;
		}
	}
}

// Retail 0x00446386, 183 bytes. Name unknown. Tracks the flag at +0x6BB;
// when it turns on (and the window at +0x6B4 exists) it replaces the window
// manager's tab list with a one-entry list holding that window; when it
// turns off it only clears the tab list. /GX (not /EHsc) keeps retail's
// state reset before the list's destructor, as for registerTabList.
void BfmeAptScreenLanLobby::rva00446386(bool enable)
{
	if (enable == m_6bb)
		return;
	GameWindow *window = m_nameEntry.m_owner;
	if (!window)
		return;
	m_6bb = enable;
	if (enable)
	{
		_STL::list<int> tabList;
		tabList.push_back((int)m_nameEntry.m_owner);
		TheWindowManager->clearTabList();
		TheWindowManager->registerTabList(tabList);
	}
	else
		TheWindowManager->clearTabList();
}

// Retail 0x00444760, 198 bytes. Donor Open-BFME-1
// BfmeAptScreenLanLobby_submitName.cpp (submitNameRva00516C50, BFME1
// 0x00516C50), whose address-name pattern it keeps. BFME2 keeps the last
// user name at +0x6A0 and the preferences at +0x684; LANAPI vslot 29 is the
// donor's RequestSetName.
void BfmeAptScreenLanLobby::submitNameRva00444760()
{
	GameWindow *entry = m_nameEntry.m_owner;
	UnicodeString text = GadgetTextEntryGetText(entry);
	UnicodeString trimmed(text);
	trimmed.trim();
	if (unicodeIsEmpty(trimmed))
		text.set(m_userName);
	if (TheLanguageFilter)
		TheLanguageFilter->filterLine(text);
	TheLAN->RequestSetName(text);
	m_prefs.setUserName(text);
}

// Retail 0x00446772, 58 bytes: slot 13 of the screen's vftable 0x00C3E0F8.
// Name unknown. Hands the preferences to the +0x668 object, writes them,
// clears the tab list (rva00446386), runs the screen's rowed 0x004442FD and
// tail-calls the +0x288 panel's 0x0043DE19.
void BfmeAptScreenLanLobby::rva00446772()
{
	m_668.rva00580316(&m_prefs);
	m_prefs.write();
	rva00446386(false);
	reinterpret_cast<Rva004442FD *>(this)->rva004442FD();
	m_panel.rva0043DE19();
}

// Retail 0x0044469C, 196 bytes. Name unknown. In state 1 with a non-blank
// name entered, the join button follows whether the game from 0x00444165 has
// a free slot and the create button is enabled; otherwise both are disabled.
void BfmeAptScreenLanLobby::rva0044469C()
{
	bool hasName = false;
	bool canJoin = false;
	if (m_6a4 == 1)
	{
		bool notBlank = false;
		if (m_nameEntry.m_owner)
		{
			UnicodeString name = GadgetTextEntryGetText(m_nameEntry.m_owner);
			name.trim();
			if (!unicodeIsEmpty(name))
				notBlank = true;
		}
		if (notBlank)
		{
			hasName = true;
			GameInfo *game = (GameInfo *)reinterpret_cast<Rva00444165 *>(this)->rva00444165();
			if (game)
			{
				int players = game->getNumPlayers();
				if (players < game->getNumOpenOrOccupiedSlots())
					canJoin = true;
			}
		}
	}
	if (canJoin)
		reinterpret_cast<Rva00444083 *>(this)->rva00444083(2);
	else
		reinterpret_cast<Rva00444083 *>(this)->rva004440F4(2);
	if (hasName)
		reinterpret_cast<Rva00444083 *>(this)->rva00444083(1);
	else
		reinterpret_cast<Rva00444083 *>(this)->rva004440F4(1);
}

// Retail 0x00445E3E, 77 bytes. Name unknown. Rebuilds the +0x668 object from
// the games in TheLAN's list whose +0x5C matches the screen's +0x304, then
// refreshes the games list box (0x004457BC) and enables the +0x288 panel.
void BfmeAptScreenLanLobby::rva00445E3E(LANGameInfo *games)
{
	reinterpret_cast<Rva00601941 *>(&m_668)->rva00601941();
	for (LANGameInfo *game = games; game; game = game->m_next)
	{
		if (game->m_5c == m_304)
			reinterpret_cast<Rva00580B40 *>(&m_668)->rva00580B40((const ModuleData *)game);
	}
	rva004457BC();
	reinterpret_cast<Rva0043DB66ByteOneSetter *>(&m_panel)->enable();
}

// Retail 0x004452A8, 505 bytes. Donor Open-BFME-1 GUICallbacks/Apt/
// AptLanLobby.cpp (initLanRva00517D00, BFME1 0x00517D00, the BFME
// counterpart of Zero Hour's LanLobbyMenuInit), whose address-name pattern it
// keeps. BFME2 target evidence: it needs the games list and the name entry,
// creates a 0x60-byte LANAPI, keeps GlobalData +0x26 at +0x6B9, no longer
// hands the list windows to TheLAN, clamps the name to ten characters, stores
// it at +0x6A0, and finishes with LANAPI vslots 15 and 58 and 0x00437421.
bool BfmeAptScreenLanLobby::initLanRva004452A8()
{
	if (m_customGamesList == 0)
		return false;
	if (m_nameEntry.m_owner != 0)
	{
		m_panel.rva0043FFCF();
		GadgetListBoxReset(m_customGamesList);

		if (!TheLAN)
		{
			TheLAN = new LANAPI();
			m_6b9 = ((Rva004452A8GlobalData *)TheWritableGlobalData)->m_26;
		}
		else
		{
			TheLAN->reset();
		}

		unsigned int ip = ((Rva004452A8GlobalData *)TheWritableGlobalData)->m_defaultIP;
		IPEnumeration IPs;

		if (!ip)
		{
			EnumeratedIP *IPlist = IPs.getAddresses();
			if (!IPlist)
				return false;
			ip = IPlist->m_ip;
		}

		TheLAN->init();
		TheLAN->m_isInLANMenu = 1;
		if (TheLAN->SetLocalIP(ip) == false)
			m_socketError = 1;

		UnicodeString defaultName;
		defaultName.set(reinterpret_cast<GameModePreferences *>(&m_prefs)->rva0044D330());
		while (defaultName.getLength() > 10)
			defaultName.removeLastChar();

		UnicodeString *slot = &m_userName;
		slot->set(defaultName);
		if (TheLanguageFilter)
			TheLanguageFilter->filterLine(defaultName);
		m_prefs.setUserName(defaultName);

		if (m_nameEntry.m_owner)
			GadgetTextEntrySetText(m_nameEntry.m_owner, defaultName);

		TheLAN->RequestSetName(defaultName);
		TheLAN->RequestLocations();
		TheLAN->v58();
		Rva00437421();
		return true;
	}
	return false;
}
