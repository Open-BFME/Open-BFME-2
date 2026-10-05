// cl: /O1 /DNDEBUG /MD
//
// BFME2's palantir (in-game command bar) Apt callbacks, 0x002D2FD4 onward,
// bound by these names ("AptPalantir::OnInitialized" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix.

extern "C" char *__cdecl strcpy(char *destination, const char *source);

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
	void rva0022277D(void *movie);
};

extern class Rva00222A8BTarget *TheRva00222A8BTarget;

class GameLogic;
extern GameLogic *TheGameLogic;

// TheGameLogic's rowed byte query 0x0023C6FD (BfmeConv939Call939D.cpp).
class BfmeGlob939D
{
public:
	char bfmeCall939D();
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
	void OnHelpBoxUnloaded(const char *unused);
	void OnHeroSelectUnloaded(const char *unused);
	void OnPlanningModeUIUnloaded(const char *unused);
	void PalantirMinLOD(int query, char *result, bool skip);

private:
	unsigned char m_pad000[0x58];
	RadarWindowOverrideSource *m_radar; // +0x58
	void *m_movie; // +0x5C
	unsigned char m_flags; // +0x60
	unsigned char m_pad061[0xC4 - 0x61];
	Rva002D3894 m_heroSelect; // +0xC4
	Rva002D38D1 m_helpBox; // +0xC8
	Rva002D3931 m_planningModeUI; // +0xCC
	unsigned char m_pad0d0[0xE5 - 0xD0];
	bool m_e5; // +0xE5
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
	TheRva00222A8BTarget->rva0022277D(m_movie);
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

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
