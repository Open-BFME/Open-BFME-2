// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's palantir (in-game command bar) Apt callbacks, 0x002D2FD4 onward,
// bound by these names ("AptPalantir::OnInitialized" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix.

#include "ascii_string.h"

extern "C" char *__cdecl strcpy(char *destination, const char *source);

// BfmePathLeafAfterMarker.cpp's path helpers.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The three sub-movie panels; their unrowed constructors take the movie's
// level and name, pinned by address. The sizes are the allocations'.
class Rva0052710C
{
public:
	// It also takes the screen's +0xC0 and +0xF8 members (types unknown).
	Rva0052710C(int level, const AsciiString &name, void *c0, void *f8);

private:
	void *m_0;
};

class Rva00527CCE
{
public:
	Rva00527CCE(int level, const AsciiString &name);

private:
	unsigned char m_pad00[0x20];
};

class Rva00527FA2
{
public:
	Rva00527FA2(int level, const AsciiString &name);

private:
	void *m_0;
};

// Rva00527FA2's constructor allocates 0x18 bytes and calls this constructor
// with its level and name arguments. The allocation extent is target evidence;
// the payload's field layout and semantics remain unknown.
class Rva00527FA7
{
public:
	Rva00527FA7(int level, const AsciiString &name);

private:
	unsigned char m_pad00[0x18];
};

// Rva0052710C allocates this payload and forwards its owner and four
// constructor arguments. The 0x1E0 extent comes from the target allocation;
// payload fields and behavior remain unknown.
class Rva00527378Payload
{
public:
	Rva00527378Payload(void *owner, int level, const AsciiString &name, void *c0, void *f8);

private:
	unsigned char m_pad00[0x1E0];
};

// The next three wrappers allocate these payloads and forward their own
// address plus one caller argument. Allocation sizes are target evidence;
// payload field layouts and meanings remain unknown.
class Rva005288C4Payload
{
public:
	Rva005288C4Payload(void *owner, void *argument);

private:
	unsigned char m_pad00[0xDC];
};

class Rva00529FC5Payload
{
public:
	Rva00529FC5Payload(void *owner, void *argument);

private:
	unsigned char m_pad00[0xDC];
};

class Rva0052AD30Payload
{
public:
	Rva0052AD30Payload(void *owner, void *argument);

private:
	unsigned char m_pad00[0x230];
};

class Rva00528AC3
{
public:
	Rva00528AC3(void *argument);

private:
	void *m_0;
};

class Rva0052A244
{
public:
	Rva0052A244(void *argument);

private:
	void *m_0;
};

class Rva0052AF1C
{
public:
	Rva0052AF1C(void *argument);

private:
	void *m_0;
};

// The holders' rowed resets (OwnedPointerResets.cpp's views; the same
// holders' clears are rowed under other names below).
class Rva002D38AE
{
public:
	void reset(Rva0052710C *panel);
};

class Rva002D38EB
{
public:
	void reset(Rva00527CCE *panel);
};

class Rva002D390E
{
public:
	void reset(Rva00527FA2 *panel);
};

// TheControlBar's rowed findCommandButton 0x0031BE3C and the rowed
// 0x00405DBC that executes a command button.
class GameWindow;
class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva004C1B60(GameWindow *window, void *button);
};

extern ControlBar *TheControlBar;

// TheLivingWorldCampaignManager (Rva002B256EThunk.cpp's g_00E02D6C); +0x2C
// is set for the evil side.
class Rva003B8BAA;
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

struct AptPalantirCampaign
{
	unsigned char m_pad00[0x2C];
	bool m_evil; // +0x2C
};

// The global at 0x00DFE144 (Rva00202BB2Parse.cpp's TheRva00DFE144); its
// +0x1778 level picks the palantir's minimum LOD.
struct Rva00DFE144Globals;
extern Rva00DFE144Globals *TheRva00DFE144;

struct AptPalantirLODView
{
	unsigned char m_pad0000[0x1778];
	int m_level; // +0x1778
};

// The radar window override at +0x58 (RadarWindowOverride.cpp's class);
// vslot 14 refreshes it.
class RadarWindowOverrideSource
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	virtual void v14();

	void rva002D35F2();
};

// The three Apt sub-movie holders at +0xC4, +0xC8 and +0xCC (each rowed
// with its own clear).
class Rva002D3894
{
public:
	void clear();

	void *m_movie;
};

class Rva002D38D1
{
public:
	void clear();

	void *m_movie;
};

class Rva002D3931
{
public:
	void clear();

	void *m_movie;
};

class Rva00222A8BTarget
{
public:
	// Unrowed 0x0022277D (98 bytes; ret 4), pinned by address.
	bool rva0022277D(int level);	// 0x0022277D, WB AptPlayer::HideLevel

	unsigned char m_pad000[0x318];
	int m_318; // +0x318, 2 for the right mouse button
};

// Zero Hour's NameKeyGenerator, TheWindowManager (winGetWindowFromId is
// vslot 60, winSendSystemMsg vslot 58) and the window's instance data,
// reached through the rowed getters 0x00314046 (+0x30) and 0x005C4AE9 (the
// id at +0x34).
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct WinInstanceData
{
	unsigned char m_pad00[0x14];
	GameWindow *m_owner; // +0x14
};

class Rva00314046LeaField
{
public:
	void *get() const;
};

class Rva005C4AE9DwordField
{
public:
	int get() const;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual int winSendSystemMsg(GameWindow *window, unsigned int message, int data1, int data2) = 0;
	virtual void pad59() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id) = 0;
};

extern GameWindowManager *TheWindowManager;

extern class Rva00222A8BTarget *TheRva00222A8BTarget;

class GameLogic;
extern GameLogic *TheGameLogic;

// TheGameLogic's rowed byte query 0x0023C6FD (BfmeConv939Call939D.cpp).
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

// TheGameLogic's rowed bool query 0x00200084 (Rva0023C6A4Check.cpp's
// class) and its game mode at +0x110.
class Rva0023C6A4
{
public:
	bool rva00200084();
};

struct AptPalantirGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

class PlayerList
{
public:
	// Unrowed 0x002A8306 (535 bytes; ret 4: the next or prior observed
	// player), pinned by address.
	void rva002A8306(bool next);
};

extern PlayerList *ThePlayerList;

// Unrowed screen openers, pinned by address: 0x0051B8EA (a jump to
// 0x0051B4F7), 0x0050EC24 and 0x004E41AB (objectives), 0x005117DF
// (messenger; its argument is unused).
void Rva0051B8EA();
void Rva0050EC24();
void Rva004E41AB();
void __cdecl Rva005117DF(const char *unused);

class AptPalantir
{
public:
	void OnInitialized(const char *unused);
	void OnClosed(const char *unused);
	void OnBttnOptions(const char *unused);
	void OnBttnObjectives(const char *unused);
	void OnBttnObserveNextPlayer(const char *unused);
	void OnBttnObservePriorPlayer(const char *unused);
	void OnBttnMessenger(const char *value);
	void OnBttnMovie(const char *unused);
	void OnBttnSpellStore(const char *unused);
	void OnHelpBoxUnloaded(const char *unused);
	void OnHeroSelectUnloaded(const char *unused);
	void OnPlanningModeUIUnloaded(const char *unused);
	void OnHelpBoxLoaded(const char *path);
	void OnHeroSelectLoaded(const char *path);
	void OnPlanningModeUILoaded(const char *path);
	void PalantirMinLOD(int query, char *result, bool skip);

	// Bound under the button clips' paths
	// ("PalantirButtons/Buttons/PlayerPowerCap/",
	// "ObserverStuff/PriorPlayerBttn", "messengerButton/") rather than
	// method names, so they keep their addresses.
	void rva002D3D61(const char *unused);
	void rva002D4DD0(const char *unused);
	void rva002D4E71(const char *unused);
	void rva002D3E29(const char *unused);
	void rva002D3E84(const char *unused);

private:
	unsigned char m_pad000[0x58];
	RadarWindowOverrideSource *m_radar; // +0x58
	void *m_movie; // +0x5C
	unsigned char m_flags; // +0x60
	unsigned char m_pad061[0x7E - 0x61];
	unsigned char m_7e; // +0x7E, 4 for the evil side
	unsigned char m_pad07f[0xC0 - 0x7F];
	int m_c0; // +0xC0
	Rva002D3894 m_heroSelect; // +0xC4
	Rva002D38D1 m_helpBox; // +0xC8
	Rva002D3931 m_planningModeUI; // +0xCC
	unsigned char m_pad0d0[0xE4 - 0xD0];
	bool m_e4; // +0xE4
	bool m_e5; // +0xE5
	unsigned char m_pad0e6[0xF8 - 0xE6];
	int m_f8; // +0xF8
};

// Retail 0x002D2FD4, 15 bytes: "AptPalantir::OnInitialized".
void AptPalantir::OnInitialized(const char *unused)
{
	m_flags &= ~5;
	m_radar->v14();
}

// Retail 0x002D2FE3, 31 bytes: "AptPalantir::OnClosed".
void AptPalantir::OnClosed(const char *unused)
{
	TheRva00222A8BTarget->rva0022277D((int)m_movie);
	m_flags = (m_flags & ~2) | 4;
}

// Retail 0x002D30C7, 8 bytes: "AptPalantir::OnBttnOptions".
void AptPalantir::OnBttnOptions(const char *unused)
{
	Rva0051B8EA();
}

// Retail 0x002D30CF, 41 bytes: "AptPalantir::OnBttnObjectives".
void AptPalantir::OnBttnObjectives(const char *unused)
{
	if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D())
		Rva0050EC24();
	else
		Rva004E41AB();
	m_e5 = false;
}

// Retail 0x002D30F8, 16 bytes: "AptPalantir::OnBttnObserveNextPlayer".
void AptPalantir::OnBttnObserveNextPlayer(const char *unused)
{
	ThePlayerList->rva002A8306(true);
}

// Retail 0x002D3108, 16 bytes: "AptPalantir::OnBttnObservePriorPlayer".
void AptPalantir::OnBttnObservePriorPlayer(const char *unused)
{
	ThePlayerList->rva002A8306(false);
}

// Retail 0x002D3118, 13 bytes: "AptPalantir::OnBttnMessenger".
void AptPalantir::OnBttnMessenger(const char *value)
{
	Rva005117DF(value);
}

// Retail 0x002D3002, 197 bytes: "AptPalantir::OnBttnSpellStore" clicks the
// control bar's general button for the player: the button's owner gets
// the selected message (0x4008, or 0x4009 for the right mouse button), as
// Zero Hour's push buttons send GBM_SELECTED.
void AptPalantir::OnBttnSpellStore(const char *unused)
{
	static NameKeyType buttonID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral");
	GameWindow *button = TheWindowManager->winGetWindowFromId(0, buttonID);
	if (!button)
		return;
	WinInstanceData *instData = (WinInstanceData *)((Rva00314046LeaField *)button)->get();
	if (!instData)
		return;
	int mouse = TheRva00222A8BTarget->m_318;
	GameWindow *owner = instData->m_owner;
	TheWindowManager->winSendSystemMsg(owner, 0x4008 + (mouse == 2), (int)button, ((Rva005C4AE9DwordField *)button)->get());
	m_e4 = false;
}

// Retail 0x002D4DD0, 161 bytes: bound under the clip path
// "PalantirButtons/Buttons/PlayerMagic/ButtonClip/", so it keeps its
// address. Runs the side's player experience command button (evil when
// +0x7E has 4).
void AptPalantir::rva002D4DD0(const char *unused)
{
	const AsciiString *name;
	if (m_7e & 4)
	{
		static AsciiString evil("NonCommand_EvilPlayerExperience");
		name = &evil;
	}
	else
	{
		static AsciiString good("NonCommand_GoodPlayerExperience");
		name = &good;
	}
	const CommandButton *button = TheControlBar->findCommandButton(*name);
	if (button)
		TheControlBar->rva004C1B60(0, (void *)button);
}

// Retail 0x002D4E71, 188 bytes: bound under the clip path
// "PalantirButtons/Buttons/Objectives/ButtonClip/", so it keeps its
// address. Runs the objectives command button when TheGameLogic's
// 0x00200084 holds or the game mode is 6, else the player status one.
void AptPalantir::rva002D4E71(const char *unused)
{
	const AsciiString *name;
	if (TheGameLogic && (((Rva0023C6A4 *)TheGameLogic)->rva00200084()
		|| ((AptPalantirGameLogic *)TheGameLogic)->m_mode == 6))
	{
		static AsciiString objectives("NonCommand_Objectives");
		name = &objectives;
	}
	else
	{
		static AsciiString status("NonCommand_PlayerStatus");
		name = &status;
	}
	const CommandButton *button = TheControlBar->findCommandButton(*name);
	if (button)
		TheControlBar->rva004C1B60(0, (void *)button);
}

// Retail 0x002D3EDF, 11 bytes: "AptPalantir::OnBttnMovie".
void AptPalantir::OnBttnMovie(const char *unused)
{
	m_radar->rva002D35F2();
}

// Retail 0x002D3F7C, 14 bytes: "AptPalantir::OnHelpBoxUnloaded".
void AptPalantir::OnHelpBoxUnloaded(const char *unused)
{
	m_helpBox.clear();
}

// Retail 0x002D402A, 14 bytes: "AptPalantir::OnHeroSelectUnloaded".
void AptPalantir::OnHeroSelectUnloaded(const char *unused)
{
	m_heroSelect.clear();
}

// Retail 0x002D40CA, 14 bytes: "AptPalantir::OnPlanningModeUIUnloaded".
void AptPalantir::OnPlanningModeUIUnloaded(const char *unused)
{
	m_planningModeUI.clear();
}

// Retail 0x002D2F9F, 53 bytes: "PalantirMinLOD", an Apt query answering
// "1" at level 1 or below, else "0".
void AptPalantir::PalantirMinLOD(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
		strcpy(result, ((AptPalantirLODView *)TheRva00DFE144)->m_level <= 1 ? "1" : "0");
}

// Retail 0x002D3D61, 109 bytes. Name unknown. Executes the side's ring or
// Evenstar power-cap command button.
void AptPalantir::rva002D3D61(const char *unused)
{
	bool evil = ((AptPalantirCampaign *)((Rva003B8BAA *)TheCampaignManager))->m_evil;
	const CommandButton *button = TheControlBar->findCommandButton(
		AsciiString(evil ? "NonCommand_MaxRingPower" : "NonCommand_MaxEvenstarPower"));
	if (button)
		TheControlBar->rva004C1B60(0, (void *)button);
}

// Retail 0x002D3E29, 91 bytes. Name unknown. Executes the observe prior
// player command button.
void AptPalantir::rva002D3E29(const char *unused)
{
	const CommandButton *button = TheControlBar->findCommandButton(AsciiString("NonCommand_ObservePriorPlayer"));
	if (button)
		TheControlBar->rva004C1B60(0, (void *)button);
}

// Retail 0x002D3E84, 91 bytes. Name unknown. Executes the messenger
// command button.
void AptPalantir::rva002D3E84(const char *unused)
{
	const CommandButton *button = TheControlBar->findCommandButton(AsciiString("NonCommand_Messenger"));
	if (button)
		TheControlBar->rva004C1B60(0, (void *)button);
}

// Retail 0x002D3EEA, 146 bytes: "AptPalantir::OnHelpBoxLoaded" builds the
// help box panel for the loaded movie.
void AptPalantir::OnHelpBoxLoaded(const char *path)
{
	((Rva002D38EB *)&m_helpBox)->reset(new Rva00527CCE(Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path))));
}

// Retail 0x002D3F8A, 160 bytes: "AptPalantir::OnHeroSelectLoaded".
void AptPalantir::OnHeroSelectLoaded(const char *path)
{
	((Rva002D38AE *)&m_heroSelect)->reset(new Rva0052710C(Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path)), &m_c0, &m_f8));
}

// Retail 0x005281F0, 66 bytes: the call site at 0x002D408D constructs the
// four-byte owner block here; this constructor allocates the 0x18-byte
// address-derived payload and forwards level/name to its constructor at
// 0x00527FA7. Payload layout and semantics are not established.
Rva00527FA2::Rva00527FA2(int level, const AsciiString &name)
	: m_0(new Rva00527FA7(level, name))
{
}

// Retail 0x00527767, 76 bytes: OnHeroSelectLoaded's call at 0x002D3FED
// constructs the four-byte owner block with level/name and the +0xC0/+0xF8
// member addresses. This allocates 0x1E0 bytes and forwards those arguments
// with its owner to 0x00527378. Payload semantics are unknown.
Rva0052710C::Rva0052710C(int level, const AsciiString &name, void *c0, void *f8)
	: m_0(new Rva00527378Payload(this, level, name, c0, f8))
{
}

// Retail 0x00528AC3, 67 bytes: called at 0x002D5835 for the four-byte slot
// at caller this+0x90. It allocates 0xDC bytes and forwards this plus the
// caller's EDI argument to 0x005288C4. Payload semantics are unknown.
Rva00528AC3::Rva00528AC3(void *argument)
	: m_0(new Rva005288C4Payload(this, argument))
{
}

// Retail 0x0052A244, 67 bytes: called at 0x002D5825 for the four-byte slot
// at caller this+0x8C. It allocates 0xDC bytes and forwards this plus the
// caller's EDI argument to 0x00529FC5. Payload semantics are unknown.
Rva0052A244::Rva0052A244(void *argument)
	: m_0(new Rva00529FC5Payload(this, argument))
{
}

// Retail 0x0052AF1C, 67 bytes: called at 0x002D5845 for the four-byte slot
// at caller this+0x94. It allocates 0x230 bytes and forwards this plus the
// caller's EDI argument to 0x0052AD30. Payload semantics are unknown.
Rva0052AF1C::Rva0052AF1C(void *argument)
	: m_0(new Rva0052AD30Payload(this, argument))
{
}

// Retail 0x002D4038, 146 bytes: "AptPalantir::OnPlanningModeUILoaded".
void AptPalantir::OnPlanningModeUILoaded(const char *path)
{
	((Rva002D390E *)&m_planningModeUI)->reset(new Rva00527FA2(Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path))));
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
