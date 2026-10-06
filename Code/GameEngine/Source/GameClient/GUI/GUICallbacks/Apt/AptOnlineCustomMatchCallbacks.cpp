// cl: /DNDEBUG /MD
//
// BFME2's online custom match screen Apt callbacks, 0x0059EC65 onward,
// bound by these names ("AptOnline::CustomMatch::PlayGame" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The scope and class are named for the strings. +0x488 is the
// screen's state.

class GameWindow;

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
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
void __cdecl Rva00434160Init(int a, int b, bool c);

// The screen's owner at +0x58 keeps its Apt movie at +0x274.
struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
};

namespace AptOnline
{
class CustomMatch
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	// vslot 10: the screen's Apt path for its callbacks.
	virtual const char *v10();

	void PlayGame(const char *unused);
	void LoadGame(const char *unused);
	void CancelPopUpCreate(const char *unused);
	void CancelPopUpHost(const char *unused);
	void OnOpenConnectionsScreen(const char *unused);
	void OnClosingConnectionsScreen(const char *unused);
	void Refresh(const char *unused);
	// Bound as "AptOnline::OnOpenCreateDialog" on this screen.
	void OnOpenCreateDialog(const char *unused);

	// Unrowed 0x005A0DC2 (339 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0DC2(bool flag);

	// Unrowed 0x005A0D61 (97 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0D61(bool force);

private:
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x488 - 0x5C];
	int m_state; // +0x488
	unsigned char m_pad48c[0x49C - 0x48C];
	GameWindow *m_createDialog; // +0x49C
	bool m_popUp; // +0x4A0
	unsigned char m_pad4a1[0x4D8 - 0x4A1];
	bool m_connectionsScreen; // +0x4D8
};
}

// Retail 0x0059EC65, 13 bytes: "AptOnline::CustomMatch::PlayGame".
void AptOnline::CustomMatch::PlayGame(const char *unused)
{
	m_state = 7;
}

// Retail 0x0059ECC1, 17 bytes: "AptOnline::CustomMatch::LoadGame".
void AptOnline::CustomMatch::LoadGame(const char *unused)
{
	Rva00434160Init(2, 16, false);
}

// Retail 0x0059ED18, 20 bytes: "AptOnline::CustomMatch::CancelPopUpCreate".
void AptOnline::CustomMatch::CancelPopUpCreate(const char *unused)
{
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED2C, 61 bytes: "AptOnline::CustomMatch::CancelPopUpHost"
// also tells the movie "ClosePassword".
void AptOnline::CustomMatch::CancelPopUpHost(const char *unused)
{
	void *movie = m_owner->m_movie;
	Rva00524EF4AptCall(TheRva00222A8BTarget, movie, v10(), "ClosePassword");
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED69, 17 bytes: "AptOnline::CustomMatch::OnOpenConnectionsScreen".
void AptOnline::CustomMatch::OnOpenConnectionsScreen(const char *unused)
{
	if (!m_connectionsScreen)
		m_connectionsScreen = true;
}

// Retail 0x0059ED7A, 17 bytes: "AptOnline::CustomMatch::OnClosingConnectionsScreen".
void AptOnline::CustomMatch::OnClosingConnectionsScreen(const char *unused)
{
	if (m_connectionsScreen)
		m_connectionsScreen = false;
}

// Retail 0x005A0F15, 10 bytes: "AptOnline::CustomMatch::Refresh".
void AptOnline::CustomMatch::Refresh(const char *unused)
{
	rva005A0D61(true);
}

// Retail 0x005A0F1F, 44 bytes: bound as "AptOnline::OnOpenCreateDialog";
// focuses the +0x49C window and moves to state 3.
void AptOnline::CustomMatch::OnOpenCreateDialog(const char *unused)
{
	rva005A0DC2(true);
	TheWindowManager->winSetFocus(m_createDialog);
	m_state = 3;
}
