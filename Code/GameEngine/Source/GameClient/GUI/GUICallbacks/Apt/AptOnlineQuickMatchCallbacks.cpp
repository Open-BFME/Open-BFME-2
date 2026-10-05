// cl: /O1 /DNDEBUG /MD
//
// BFME2's online quick match screen Apt callbacks, 0x005BA344 onward, and
// the login screen's CancelLogin, bound by these names
// ("AptOnline::OnlineQuickMatch::StartSimple" ...) as member pointers by
// the screens' registrations; that binding is their only reference. The
// scope and classes are named for the strings. "AptOnlineQuickMatch::
// InitGadgets" is bound by the same registration on the same object as
// the "AptOnline::OnlineQuickMatch::" callbacks, so it joins that class.

// Rva00516E92Enable.cpp's 0x00516E92.
void Rva00516E92Enable();

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow;
void GadgetComboBoxReset(GameWindow *comboBox);

// The window kept at +0x80: rebound through the one-pointer store
// returning this at 0x0007B719 (an ICF-folded body, as MpGameSetupSlots.cpp's
// MpGameSetupComboRef), pinned by address.
class OnlineQuickMatchWindowRef
{
public:
	OnlineQuickMatchWindowRef &operator=(GameWindow *window);

	GameWindow *m_window;
};

// TheWindowManager; its rowed 0x002C5761 (rowed as a stdcall
// Rva002C5761Sort) is called with the manager in ECX, so it is declared as
// a member and pinned under that name.
class GameWindowManager
{
public:
	void rva002C5761(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

namespace AptOnline
{
class OnlineQuickMatch
{
public:
	void StartSimple(const char *unused);
	void PlayGame(const char *unused);
	void OnFoundMovieDone(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

	// Unrowed 0x005BA803, pinned by address.
	void rva005BA803();

private:
	unsigned char m_pad00[0x58];
	GameWindow *m_window; // +0x58
	unsigned char m_pad5c[0x60 - 0x5C];
	int m_state; // +0x60
	unsigned char m_pad64[0x79 - 0x64];
	bool m_simple; // +0x79
	bool m_foundMovie; // +0x7A
	unsigned char m_pad7b[0x7C - 0x7B];
	unsigned int m_gadgets; // +0x7C, which gadgets are linked
	OnlineQuickMatchWindowRef m_color; // +0x80
	GameWindow *m_numPlayers; // +0x84
	GameWindow *m_side; // +0x88
	GameWindow *m_connectionSpeed; // +0x8C
	GameWindow *m_ladder; // +0x90
};

class Login
{
public:
	void CancelLogin(const char *unused);
};
}

// Retail 0x005BA344, 7 bytes: "AptOnline::OnlineQuickMatch::StartSimple".
void AptOnline::OnlineQuickMatch::StartSimple(const char *unused)
{
	m_simple = true;
}

// Retail 0x005BA34B, 14 bytes: "AptOnline::OnlineQuickMatch::PlayGame".
void AptOnline::OnlineQuickMatch::PlayGame(const char *unused)
{
	m_simple = true;
	m_state = 1;
}

// Retail 0x005BA359, 20 bytes: "AptOnline::OnlineQuickMatch::OnFoundMovieDone".
void AptOnline::OnlineQuickMatch::OnFoundMovieDone(const char *unused)
{
	m_state = 2;
	if (m_foundMovie)
		m_foundMovie = false;
}

// Retail 0x005BA94A, 225 bytes: "AptOnlineQuickMatch::InitGadgets" keeps
// the screen's gadgets (emptying its combo boxes), records each as linked,
// and has the window manager rework the screen's window.
void AptOnline::OnlineQuickMatch::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "OnlineQuickMatch::Color") == 0)
	{
		m_color = window;
		rva005BA803();
		m_gadgets |= 0x01;
	}
	else if (strcmp(name, "OnlineQuickMatch::NumOfPlayers") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x04;
		m_numPlayers = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::Side") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x20;
		m_side = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::ConnectionSpeed") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x40;
		m_connectionSpeed = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::Ladder") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x80;
		m_ladder = window;
	}
	TheWindowManager->rva002C5761(m_window);
}

// Retail 0x0056DCB7, 8 bytes: "AptOnline::Login::CancelLogin".
void AptOnline::Login::CancelLogin(const char *unused)
{
	Rva00516E92Enable();
}
