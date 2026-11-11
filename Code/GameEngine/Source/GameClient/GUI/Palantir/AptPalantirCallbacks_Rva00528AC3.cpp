// Split from AptPalantirCallbacks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's palantir (in-game command bar) Apt callbacks, 0x002D2FD4 onward,
// bound by these names ("AptPalantir::OnInitialized" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix.

#include "ascii_string.h"

#include <string.h>

// AptUtils.cpp's path helpers.
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

// The three sub-movie panels; their unrowed constructors take the movie's
// level and name, pinned by address. The sizes are the allocations'.
#include "../../../../Include/GameClient/Rva0052710C.h"

// The help-box pointee is built by the 0x00527C04 constructor rowed under
// its class Rva00527827 (same 0x20 bytes); the owning-pointer reset row
// spells the pointee Rva00527CCE, so the new pointer is cast for it.
#include "../../../../Include/Common/Rva00527CCE.h"
class Rva00527827
{
public:
	Rva00527827(int level, const AsciiString &name);

private:
	unsigned char m_pad00[0x20];
};

#include "../../../../Include/Common/Rva00527FA2.h"

// Rva00527FA2's constructor allocates 0x18 bytes and calls this constructor
// with its level and name arguments. The allocation extent is target evidence;
// the payload's field layout and semantics remain unknown.
// Rva0052710C allocates this payload and forwards its owner and four
// constructor arguments. The 0x1E0 extent comes from the target allocation;
// payload fields and behavior remain unknown.
// The next three wrappers allocate these payloads and forward their own
// address plus one caller argument. Allocation sizes are target evidence.
// 0x005288C4 is rowed as AptInGameSideCommandBar::Impl's constructor
// (AptInGameSideCommandBar.cpp) and 0x00529FC5 as Rva0052936C's
// (PalantirCommandInterface.cpp); field layouts stay opaque here.
class AptInGameSideCommandBar
{
public:
	class Impl
	{
	public:
		Impl(AptInGameSideCommandBar *owner, int argument);

	private:
		unsigned char m_pad00[0xDC];
	};
};

class Rva0052936C
{
public:
	Rva0052936C(void *owner, int argument);

private:
	unsigned char m_pad00[0xDC];
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

// The holders' rowed resets (OwnedPointerResets.cpp's views; the same
// holders' clears are rowed under other names below).
class Rva002D38EB
{
public:
	void reset(Rva00527CCE *panel);
};

// TheControlBar's rowed findCommandButton 0x0031BE3C and the rowed
// 0x00405DBC that executes a command button.
class GameWindow;
class CommandButton;

#include "../../../../Include/GameClient/ControlBar.h"

extern ControlBar *TheControlBar;

// TheLivingWorldCampaignManager (Rva002B256EThunk.cpp's g_00E02D6C); +0x2C
// is set for the evil side.
class LivingWorldCampaignManager;
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

struct AptPalantirCampaign
{
	unsigned char m_pad00[0x2C];
	bool m_evil; // +0x2C
};

// The global at 0x00DFE144 (Rva00202BB2Parse.cpp's TheGameLODManager); its
// +0x1778 level picks the palantir's minimum LOD.
struct Rva00DFE144Globals;
extern class GameLODManager *TheGameLODManager;

struct AptPalantirLODView
{
	unsigned char m_pad0000[0x1778];
	int m_level; // +0x1778
};

// The radar window override at +0x58 (RadarWindowOverride.cpp's class);
// vslot 14 refreshes it.
#include "../../../../Include/Common/RadarWindowOverrideSource.h"

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

#include "../../../../Include/Common/Rva00222A8BTarget.h"

// Zero Hour's NameKeyGenerator, TheWindowManager (winGetWindowFromId is
// vslot 60, winSendSystemMsg vslot 58) and the window's instance data,
// reached through the rowed getters 0x00314046 (+0x30) and 0x005C4AE9 (the
// id at +0x34).
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/GameClient/Bfme2WinInstanceData.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

extern class Rva00222A8BTarget *TheRva00222A8BTarget;

class GameLogic;
extern GameLogic *TheGameLogic;

// TheGameLogic's rowed byte query 0x0023C6FD (BfmeConv939Call939D.cpp).
// TheGameLogic's rowed bool query 0x00200084 (Rva0023C6A4Check.cpp's
// class) and its game mode at +0x110.
struct AptPalantirGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

#include "../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

// Unrowed screen openers, pinned by address: 0x0051B8EA (a jump to
// 0x0051B4F7), 0x0050EC24 and 0x004E41AB (objectives), 0x005117DF
// (messenger, rowed as AptMessenger::OnMessengerBttn; its argument is unused).
void Rva0051B8EA();
void Rva004E41AB();
class AptMessenger { public: static void OnMessengerBttn(const char *unused); };

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
	void HandleOverSpellStoreButton(const char *unused);
	void HandleOverObjectivesButton(const char *unused);
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
	AptMessenger::OnMessengerBttn(value);
}












// Retail 0x002D3EEA, 146 bytes: "AptPalantir::OnHelpBoxLoaded" builds the
// help box panel for the loaded movie.
void AptPalantir::OnHelpBoxLoaded(const char *path)
{
	((Rva002D38EB *)&m_helpBox)->reset((Rva00527CCE *)new Rva00527827(AptUtils::LevelIndexFromTarget(path), AsciiString(AptUtils::SkipLevelN(path))));
}




// Retail 0x00528AC3, 67 bytes: called at 0x002D5835 for the four-byte slot
// at caller this+0x90. It allocates 0xDC bytes and forwards this plus the
// caller's EDI argument to 0x005288C4. Payload semantics are unknown.
Rva00528AC3::Rva00528AC3(void *argument)
	: m_0(new AptInGameSideCommandBar::Impl((AptInGameSideCommandBar *)this, (int)argument))
{
}

// Retail 0x0052A244, 67 bytes: called at 0x002D5825 for the four-byte slot
// at caller this+0x8C. It allocates 0xDC bytes and forwards this plus the
// caller's EDI argument to 0x00529FC5. Payload semantics are unknown.
Rva0052A244::Rva0052A244(void *argument)
	: m_0(new Rva0052936C(this, (int)argument))
{
}



// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
