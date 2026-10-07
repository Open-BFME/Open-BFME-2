// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's LAN lobby gadget initialization callback, retail 0x00445DA5
// (153 bytes). The screen's constructor 0x00445EE3 binds it as a member
// function pointer on the whole screen object (vftable 0x00C3E0F8; the
// callback interface BfmeAptScreenLanLobby.cpp views sits at +0x27C).
//
// Donor: Open-BFME-1 GUICallbacks/Apt/BfmeAptScreenLanLobby_onInitGadget.cpp
// (donor BfmeAptScreenLanLobby::_bfme_onInitGadget, BFME1 0x005187F0); the name is
// the donor's identity for the same role and "LanLobby::" gadget names.
// BFME2 name: WorldBuilder's AptLanLobby.cpp:1419-1442 asserts in
// AptLanLobby::InitGadgets with this body, and retail holds the
// "AptLanLobby::InitGadgets" callback string.
// BFME2 target evidence: only CustomGamesList (stored at +0x6A8, games
// tooltip 0x00445BAA) and NameEntry remain; NameEntry's link helper at
// +0x6AC (destroyed by ??1Rva0031455E) attaches through its vslot 1 and
// keeps the window at its +0x08 (+0x6B4), and the screen clears +0x6C0.

#include "unicode_string.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


extern "C" int __cdecl strcmp(const char *left, const char *right);

class LANGameInfo;

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

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int mouse));
};

class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *window);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void __cdecl GadgetTextEntrySetValidationFlags(GameWindow *window, int value);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *key, unsigned short value);

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

	unsigned char m_pad04[0x14 - 0x04];
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
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum() const;

	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
};

// TheLAN's game list: eight 0x1D0-byte slots from +0xDC end at +0xF5C, where
// the next game is linked.
class LANGameInfo : public GameInfo
{
public:
	unsigned char m_pad004[0x5C - 0x04];
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
	// Unrowed panel methods, pinned by address: 0x0043FFCF (8 bytes),
	// 0x00440BDF (1693 bytes), 0x0044127C (544 bytes), 0x00443EA8 (358 bytes).
	void rva0043FFCF();
	bool rva00440BDF(bool flag);
	bool rva0044127C();
	void rva00443EA8();
	// And its message handler 0x00442CB3 (690 bytes) and 0x0043FA68 (244
	// bytes), likewise unrowed and pinned.
	int rva00442CB3(int msg, unsigned int data1, unsigned int data2);
	void rva0043FA68(int game);
	// MpGameSetupSlots.cpp's rva004422B4 (the game mode), pinned by address.
	void rva004422B4(int mode);
};

// The screen's base class (destroyed by 0x005126F5); its message handler
// 0x0051274F (136 bytes, vftable 0x00C659E8 slot 2) is unrowed and pinned.
class _bfme_AptGameWindow
{
public:
	int rva0051274F(int msg, unsigned int data1, unsigned int data2);
};

class Rva00444362
{
public:
	void rva00444362(void *unused);
};

class Rva00580172
{
public:
	bool rva00580172();
};

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The two GameLogic fields read by the update (TheGameLogic, 0x00DFE78C).
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva00446443GameLogic
{
	unsigned char m_pad000[0x40];
	int m_40; // +0x40
	unsigned char m_pad044[0x110 - 0x44];
	int m_110; // +0x110
};

void __cdecl Rva005118F3Show(int mode, bool show);
void __cdecl Rva00434160Init(int a, int b, bool c);
void __cdecl Rva003B3371Call(int value);
void Rva00444040Enable();
void __cdecl Rva005185D8Init(bool a, bool b, bool c, bool d);
void GadgetListBoxGetSelected(GameWindow *listbox, int *selected);

// Unrowed 0x0044C0A8 (message box with title, text and callback), pinned.
void Rva0044C0A8(UnicodeString title, UnicodeString text, void *callback);

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

struct TransportAddress
{
	TransportAddress() : m_ip(0), m_port(0) {}

	unsigned int m_ip;
	unsigned short m_port;
};

class LANAPI
{
public:
	LANAPI();
	virtual void v00();
	virtual void init();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void reset();
	virtual void update();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void RequestLocations();
	virtual void v16(LANGameInfo *game, TransportAddress *address);
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(UnicodeString text, int value);
	virtual void v28();
	virtual void RequestSetName(UnicodeString name);
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50();
	virtual LANGameInfo *v51();
	virtual void v52();
	virtual bool SetLocalIP(unsigned int ip);
	virtual void v54(); virtual void v55();
	virtual LANGameInfo *GetMyGame();
	virtual void v57();
	virtual void v58();

	unsigned char m_pad04[0x5D - 0x04];
	unsigned char m_isInLANMenu; // +0x5D
	unsigned char m_pad5e[0x60 - 0x5E];
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

class AptLanLobby
{
public:
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva00446386(bool enable);
	void submitNameRva00444760();
	void rva00446772();
	void rva0044469C();
	void rva00445E3E(LANGameInfo *games);
	bool InitTheLan();
	int OnUpdateData();
	int GetValidSelectedGameInfo();
	void rva004443E7();
	int rva00444826(int msg, unsigned int data1, unsigned int data2);

	// Unrowed 0x004457BC (1006 bytes; rebuilds the games list box), pinned by
	// address.
	void rva004457BC();

	// Apt callbacks the constructor 0x00445EE3 binds by these names
	// ("AptLanLobby::OnOptionsBttn" ...).
	void OnOptionsBttn(const char *unused);
	void OnExitBttn(const char *unused);
	void OnStartGameBttn(const char *unused);
	void OnLoadGameBttn(const char *unused);
	void OnLoadScreen(const char *mode);
	void OnCreateGameBttn(const char *unused);

private:
	unsigned char m_pad000[0x274];
	void *m_owner; // +0x274
	unsigned char m_pad278[0x288 - 0x278];
	Rva004421E1 m_panel; // +0x288
	unsigned char m_pad289[0x304 - 0x289];
	int m_304; // +0x304
	unsigned char m_pad308[0x538 - 0x308];
	int m_538; // +0x538
	unsigned char m_pad53c[0x668 - 0x53C];
	Rva00580316 m_668; // +0x668
	LanLobbyUserNamePrefs m_prefs; // +0x684
	int m_gameMode; // +0x698 (0 LanOpenPlay, 1 LanStrategic, else -1)
	unsigned char m_pad69c[0x6A0 - 0x69C];
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

void AptLanLobby::InitGadgets(const char *name, void *, GameWindow *window)
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
			GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 0x0c);
			GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
			GadgetTextEntrySetValidationFlags(window, 0x80);
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
void AptLanLobby::rva00446386(bool enable)
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
void AptLanLobby::submitNameRva00444760()
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
void AptLanLobby::rva00446772()
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
void AptLanLobby::rva0044469C()
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
			GameInfo *game = (GameInfo *)GetValidSelectedGameInfo();
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
void AptLanLobby::rva00445E3E(LANGameInfo *games)
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
bool AptLanLobby::InitTheLan()
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

// Retail 0x00446443, 815 bytes: slot 5 of the screen's vftable 0x00C3E0F8,
// the lobby's per-frame update. Name unknown. Unless +0x6C0 holds it back it
// updates TheLAN and steps the +0x6A4 state machine (0 start-up, 1 game
// list, 2 leave, 5/6 panel checks, 7 join the selected game, 9 kicked, 11
// back out), refreshes the buttons, reports a socket error once and returns
// 1; the +0x288 panel always gets its 0x00443EA8 (retail merges both
// returns' panel calls).
int AptLanLobby::OnUpdateData()
{
	if (m_6c0)
	{
		m_panel.rva00443EA8();
		return 0;
	}
	{
		if (TheLAN)
			TheLAN->update();

		switch (m_6a4)
		{
		case 0:
			if (InitTheLan())
			{
				Rva005118F3Show(0, false);
				if (m_538)
					m_6a4 = 2;
				else
				{
					{
					void *owner = m_owner;
					TheRva00222A8BTarget->invoke(owner, "StartLobby", 0, 0, 0, 0, 0, 0);
				}
					m_6a4 = 1;
					rva00446386(true);
					m_6c0 = 0;
				}
			}
			break;
		case 1:
			if (reinterpret_cast<Rva00580172 *>(&m_668)->rva00580172() && TheLAN)
				rva00445E3E(TheLAN->v51());
			break;
		case 2:
			rva00446386(false);
			m_6a4 = 3;
			Rva005118F3Show(1, true);
			TheLAN->v27(UnicodeString((const unsigned short *)L""), 0);
			break;
		case 5:
			if (m_panel.rva00440BDF(true))
				m_6a4 = 6;
			else
			{
				m_6a4 = 4;
				{
					void *owner = m_owner;
					TheRva00222A8BTarget->invoke(owner, "EnablePlayGame", 0, 0, 0, 0, 0, 0);
				}
			}
			break;
		case 6:
			if (!m_panel.rva0044127C())
			{
				m_6a4 = 4;
				{
					void *owner = m_owner;
					TheRva00222A8BTarget->invoke(owner, "EnablePlayGame", 0, 0, 0, 0, 0, 0);
				}
			}
			break;
		case 7:
		{
			rva00446386(false);
			int selected = -1;
			m_6a4 = 1;
			GadgetListBoxGetSelected(m_customGamesList, &selected);
			LANGameInfo *game = (LANGameInfo *)GetValidSelectedGameInfo();
			if (game)
			{
				m_6a4 = 8;
				Rva005118F3Show(1, true);
				TransportAddress address;
				TheLAN->v16(game, &address);
			}
			break;
		}
		case 9:
		{
			LANGameInfo *game = TheLAN->GetMyGame();
			if (!game || game->getLocalSlotNum() == -1)
			{
				Rva0044C0A8(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSKicked"), 0);
				rva004443E7();
				m_6a4 = 0;
			}
			break;
		}
		case 11:
			reinterpret_cast<Rva004442FD *>(this)->rva004442FD();
			Rva00434160Init(2, 0x10, false);
			break;
		}

		rva0044469C();
		Rva00446443GameLogic *logic = (Rva00446443GameLogic *)TheGameLogic;
		if (logic->m_110 == 4 && logic->m_40 == 1)
			Rva003B3371Call(0x1C);
		if (m_socketError == 1)
		{
			m_socketError = 0;
			Rva0044C0A8(TheGameText->fetch("GUI:NetworkError"), TheGameText->fetch("GUI:SocketError"), 0);
			Rva00444040Enable();
		}
	}
	m_panel.rva00443EA8();
	return 1;
}

// Retail 0x00444826, 191 bytes: slot 2 of the screen's vftable 0x00C3E0F8,
// its message handler. Name unknown. Unless held back by +0x6C0 it offers
// the message to the base class and the +0x288 panel, then handles 1 and 2
// (sound events 0x1A and 0x1B), the games list's 0x4014 and 0x4015 (select
// and activate) and the name entry's 0x4032 (submitName); anything else
// returns what the base (or else the panel) returned.
int AptLanLobby::rva00444826(int msg, unsigned int data1, unsigned int data2)
{
	if (m_6c0)
		return 0;

	int result = reinterpret_cast<_bfme_AptGameWindow *>(this)->rva0051274F(msg, data1, data2);
	int panelResult = m_panel.rva00442CB3(msg, data1, data2);
	if (!result)
		result = panelResult;

	switch (msg)
	{
	case 1:
		Rva003B3371Call(0x1A);
		break;
	case 2:
		Rva003B3371Call(0x1B);
		break;
	case 0x4014:
		if ((GameWindow *)data1 == m_customGamesList)
			m_panel.rva0043FA68(GetValidSelectedGameInfo());
		break;
	case 0x4015:
		if ((GameWindow *)data1 == m_customGamesList && GetValidSelectedGameInfo())
			reinterpret_cast<Rva00444362 *>(this)->rva00444362((void *)"");
		break;
	case 0x4032:
		submitNameRva00444760();
		break;
	default:
		return result;
	}
	return 1;
}

// Retail 0x0044432B, 23 bytes: "AptLanLobby::OnOptionsBttn". Leaves the
// lobby (0x004442FD) and opens the options screen through 0x005185D8.
void AptLanLobby::OnOptionsBttn(const char *unused)
{
	reinterpret_cast<Rva004442FD *>(this)->rva004442FD();
	Rva005185D8Init(false, false, true, false);
}

// Retail 0x00444342, 8 bytes: "AptLanLobby::OnExitBttn".
void AptLanLobby::OnExitBttn(const char *unused)
{
	Rva00444040Enable();
}

// Retail 0x0044434A, 13 bytes: "AptLanLobby::OnStartGameBttn" moves the
// update's state machine (+0x6A4) to 5.
void AptLanLobby::OnStartGameBttn(const char *unused)
{
	m_6a4 = 5;
}

// Retail 0x00444376, 20 bytes: "AptLanLobby::OnLoadGameBttn", state 1 to 11.
void AptLanLobby::OnLoadGameBttn(const char *unused)
{
	if (m_6a4 == 1)
		m_6a4 = 11;
}

// Retail 0x0044438A, 93 bytes: "AptLanLobby::OnLoadScreen" resets the
// state and hands the panel (0x004422B4) the game mode named by the screen.
void AptLanLobby::OnLoadScreen(const char *mode)
{
	m_6a4 = 0;
	if (strcmp(mode, "LanOpenPlay") == 0)
	{
		m_gameMode = 0;
		m_panel.rva004422B4(0);
	}
	else if (strcmp(mode, "LanStrategic") == 0)
	{
		m_gameMode = 1;
		m_panel.rva004422B4(1);
	}
	else
	{
		m_gameMode = -1;
		m_panel.rva004422B4(-1);
	}
}

// Retail 0x00444F5D, 63 bytes: "AptLanLobby::OnCreateGameBttn", state 1
// to 2, and the name entry's text saved as the user name.
void AptLanLobby::OnCreateGameBttn(const char *unused)
{
	if (m_6a4 == 1)
		m_6a4 = 2;
	if (m_nameEntry.m_owner)
		m_prefs.setUserName(GadgetTextEntryGetText(m_nameEntry.m_owner));
}
